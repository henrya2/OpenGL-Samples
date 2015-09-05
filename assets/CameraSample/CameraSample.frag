#version 330 core

layout(location=0) out vec4 outputColor;	//fragment shader output

in vec3 fragmentColor;

void main()
{
	//set the interpolated colour as the shader output
	outputColor = vec4(fragmentColor, 1.0f);
}