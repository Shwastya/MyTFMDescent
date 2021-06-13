#version 330 core

out vec4 FragColor;

//uniform vec4 u_color;

in vec4 v_Color;

void main() 

{
	
	//FragColor = vec4(0.8, 0.6157, 0.102, 1.0);	
	FragColor = v_Color;

    
}