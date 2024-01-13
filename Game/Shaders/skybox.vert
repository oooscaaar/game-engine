#version 460
layout(location=0) in vec3 position;
layout(location = 0)uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 proj;
out	vec3 texcoords;
void main()
{
texcoords = position;
 gl_Position = proj*view*model*vec4(position,1.0);
}
