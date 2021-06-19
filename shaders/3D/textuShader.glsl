#TYPE V
#version 330 core

layout (location=0) in vec3 a_Pos;
layout (location=1) in vec2 a_UVS;

uniform mat4 u_Model; // ModelProjection
uniform mat4 u_View;  // ViewProjection
uniform mat4 u_Proj;  // Projection

out vec2 v_UVS;

void main()
{
  	v_UVS = a_UVS;
	gl_Position = u_Proj * u_View * u_Model * vec4(a_Pos, 1.0);
}

#TYPE F
#version 330 core

out vec4 FragColor;

in vec2 v_UVS;

uniform sampler2D u_Texture;

void main() 

{	
	FragColor = texture(u_Texture, v_UVS);	    
}

