#version 440

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 colorOut;

uniform mat4 transformationMatrix;
void main()
{
	gl_Position = transformationMatrix * vec4(position.xyz, 1.0f);
	colorOut = color;
}