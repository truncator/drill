#version 330

in vec3 v_position;

out vec4 frag_color;

void main()
{
	float y = 0.0 - v_position.y;

	vec3 color = vec3(0.3, 0.45, 0.55);
	color = mix(color, vec3(0.04, 0.08, 0.12), y / 64.0);

	frag_color = vec4(color.rgb, 1.0);
}
