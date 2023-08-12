#version 410 core
layout (location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 model_cube;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * model_cube * vec4(position, 1.0f);
}
