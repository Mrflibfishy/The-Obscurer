#version 430

in vec4 vertexPos;
in vec3 vertexColor;

layout(location = 1) in vec3 vertColor;
out vec3 fragColor;

void main()
{
	gl_Position = vertexPos;
	fragColor = vertColor;
}