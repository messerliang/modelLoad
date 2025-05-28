#version 330 core

layout(location=0) in vec4 position;


out vec4 color;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * position;

	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
};
