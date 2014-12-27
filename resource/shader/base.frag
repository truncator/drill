#version 330

struct Light
{
	vec2 position;
	vec3 color;
	float intensity;
	float falloff;
};

const int MAX_LIGHTS = 100;
uniform Light lights[MAX_LIGHTS];
uniform int active_lights;

in vec3 v_color;
in vec3 v_position;
in float v_metallic;

out vec4 frag_color;

float attenuate(float dist, float a, float b)
{
	return 1.0 / (1.0 + a * dist + b * dist * dist);

	// http://gamedev.stackexchange.com/questions/56897/glsl-light-attenuation-color-and-intensity-formula
	//return clamp(1.0 - dist / radius, 0.0, 1.0);
	//return clamp(1.0 - dist * dist / (radius * radius), 0.0, 1.0);
}

void main()
{
	vec3 color_sum = vec3(0.0, 0.0, 0.0);

	int num_lights = min(active_lights, MAX_LIGHTS);
	for (int i = 0; i < num_lights; i++)
	{
		// Light influence.
		float dist = distance(v_position.xy, lights[i].position);
		float light_contribution = attenuate(dist - 1.5, 0.0, 1.0 / lights[i].falloff) * lights[i].intensity;

		light_contribution += light_contribution * v_metallic;

		// Depth falloff.
		const float DEPTH_FALLOFF_RATE = 20.0;
		const float DEPTH_FALLOFF_HEIGHT = 10.0;
		float falloff = max(DEPTH_FALLOFF_HEIGHT + v_position.y, 0.0);
		float sun_contribution = falloff / DEPTH_FALLOFF_RATE;
		vec3 sun_color = vec3(1.0, 1.0, 1.0);

		color_sum += light_contribution * lights[i].color * v_color;
		color_sum += sun_contribution * sun_color * v_color;
	}

	frag_color = vec4(color_sum, 1.0);
}
