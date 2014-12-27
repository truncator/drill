#version 330

uniform mat4 projection;
uniform mat4 model;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 uv;
layout(location = 3) in float metallic;

out vec3 v_position;
out vec3 v_color;
out vec2 v_uv;
out float v_metallic;

void main()
{
	vec4 transformed_position = model * vec4(position.xy, 0.0, 1.0);

	v_position = transformed_position.xyz;
	v_color = color;
	v_uv = vec2(uv.x, 1.0 - uv.y);
	v_uv = uv;
	v_metallic = metallic;

	gl_Position = projection * transformed_position;
	gl_Position.z = position.z;
}
