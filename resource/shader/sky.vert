#version 330

uniform mat4 projection;

layout(location = 0) in vec3 position;

out vec3 v_position;

void main()
{
	v_position = position.xyz;

	gl_Position = projection * vec4(position.xy, 0.0, 1.0);
	gl_Position.z = position.z;
}
