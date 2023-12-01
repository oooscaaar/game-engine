#version 460
layout(location=0) in vec3 pos;
layout(location=1) in vec2 atexCoord;
layout(location = 1) uniform mat4 model;
layout(location = 2) uniform mat4 view;
layout(location = 3) uniform mat4 proj;
out vec2 textCoord;
void main()
{
	textCoord = atexCoord;
	gl_Position = proj*view*model*vec4(pos,1.0);
}
