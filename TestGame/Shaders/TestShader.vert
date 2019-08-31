#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

uniform mat4 Projection = mat4(1.0f);
//uniform mat4 Model;

out vec4 vertColor;

void main()
{
	gl_Position = Projection * vec4(position.xyz,1.0f);
	vertColor = color;
}