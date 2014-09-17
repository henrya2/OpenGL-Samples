#version 330 core

layout(location=0) out vec4 outputColor;	//fragment shader output

void main()
{
	//set the interpolated colour as the shader output
	outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}