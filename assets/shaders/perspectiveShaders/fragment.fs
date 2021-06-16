#version 330 core

out vec4 FragColor;

in vec2 v_UVS;

uniform vec3 u_Color;

void main() 

{
	
	FragColor = vec4(v_UVS, 0.0, 1.0);	
	//FragColor = u_Color;

    
}