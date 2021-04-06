#Shader Vertex
#version 330 core


layout (location=0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos, 1.0);
}


#Shader Fragment
#version 330 core

out vec4 FragColor;

uniform vec4 u_color;

void main() 

{
	
	//FragColor = vec4(0.8, 0.6, 0.1, 1.0);	
	FragColor = u_color;
}
