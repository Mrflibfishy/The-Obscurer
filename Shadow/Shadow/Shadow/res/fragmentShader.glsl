#version 430

in vec3 fragColor;
layout(location = 0) out vec4 color;


void main()
{
	color = vec4(fragColor, 1.0);
}