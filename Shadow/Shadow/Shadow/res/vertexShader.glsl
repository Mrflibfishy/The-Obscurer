#version 430

layout(location = 0) in vec4 position;
//out vec2 fragPos;


void main()
{
	gl_Position = position;
}