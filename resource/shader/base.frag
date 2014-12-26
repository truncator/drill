#version 330

uniform vec2 light_position;
uniform float light_intensity;

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
	// Light influence.
	float dist = distance(v_position.xy, light_position);
	float brightness = attenuate(dist - 1.5, 0.0, 0.08);

	// Metallic contribution.
	brightness += 1.0 * v_metallic * brightness;

	// Depth falloff.
	const float DEPTH_FALLOFF_RATE = 20.0;
	const float DEPTH_FALLOFF_HEIGHT = 10.0;
	float falloff = max(DEPTH_FALLOFF_HEIGHT + v_position.y, 0.0);
	brightness += falloff / DEPTH_FALLOFF_RATE;

	frag_color = vec4(brightness * v_color, 1.0);
}
