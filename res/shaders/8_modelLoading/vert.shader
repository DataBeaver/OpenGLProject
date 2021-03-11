#version 450 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 pv;

void main()
{
    gl_Position = pv * model * vec4(aPos, 1.0);
}