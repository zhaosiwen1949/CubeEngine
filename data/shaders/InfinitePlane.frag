//
#version 460 core

#include <data/shaders/Common/GridParameters.h>
#include <data/shaders/Common/GridCalculation.h>

layout (location=0) in vec2 uv;
layout (location=0) out vec4 out_FragColor;

void main()
{
	out_FragColor = gridColor(uv);
}
