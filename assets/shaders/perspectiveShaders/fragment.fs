#version 330 core

out vec4 FragColor;

//uniform vec4 u_color;

uniform vec3 u_Color;

void main() 

{
	
	FragColor = vec4(u_Color, 1.0);	
	//FragColor = u_Color;

    
}