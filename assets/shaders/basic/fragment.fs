#version 330 core

out vec4 FragColor;

//uniform vec4 u_color;

in vec3 test_position_as_Color;

void main() 

{
	
	//FragColor = vec4(0.8, 0.6, 0.1, 1.0);	
	//FragColor = u_color;

    FragColor = vec4(test_position_as_Color, 1.0);	
}