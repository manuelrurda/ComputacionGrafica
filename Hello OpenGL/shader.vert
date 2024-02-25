#version 330
layout (location =0) in vec3 pos;
out vec4 vColor;
uniform mat4 model;
uniform mat4 projection;
uniform vec3 color; // Definimos una variable uniforme para el color
void main()
{
    gl_Position=projection*model*vec4(pos,1.0f);
    vColor=vec4(color,1.0f);
}
