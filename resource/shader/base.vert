#version 330

uniform mat4 view_projection;
uniform mat4 model;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 v_color;
out float v_depth;

void main()
{
	v_color = color;

	gl_Position = view_projection * model * vec4(position.xy, 0.0, 1.0);
	gl_Position.z = position.z;
}
