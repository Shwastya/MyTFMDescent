#version 330 core

layout (location=0) in vec3 a_Pos;
//layout (location=1) in vec4 a_Color;

uniform mat4 u_Model; // ModelProjection
uniform mat4 u_View;  // ViewProjection
uniform mat4 u_Proj;  // Projection

out vec4 v_Color;

void main()
{
    //v_Color = a_Color;
	gl_Position = u_Proj * u_View * u_Model * vec4(a_Pos, 1.0);
}