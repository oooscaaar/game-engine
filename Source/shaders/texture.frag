#version 460
layout (location = 0) uniform vec4 fragColor;
in vec2 atexCoord;
out vec4 color;
out vec2 texCoord;
void main()
{
 color = fragColor;
 texCoord = atexCoord;
}