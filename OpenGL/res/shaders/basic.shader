#shader vertex
#version 330 core

layout(location = 0) in vec4position;

void main()
{
    gl_Position = position;
}

#shader fragment
#version 330 core 

layout (location = 0) out vec4 ccompatibilityolor;

void main()
{
    color = vec4(1,0,0,)
}