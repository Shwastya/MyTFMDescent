#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;

out vec3 pos;
//uniform mat4 u_Model;
uniform mat4 u_View; // ViewProjection
//uniform mat4 u_Proj;

//uniform vec4 u_Color;

void main()
{
    pos = aPos;
	gl_Position = u_View * vec4(aPos, 1.0);
}