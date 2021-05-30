#Shader Vertex
#version 330 core


layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aUV;
layout (location=2) in vec3 aNormal;

out vec2 UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	UV = aUV;
	gl_Position = proj * view * model * vec4(aPos, 1.0);
	// gl_Position = vec4(aPos, 1.0);
}


#Shader Fragment
#version 330 core

out vec4 FragColor;

uniform vec4 u_color;
uniform sampler2D tex;

void main() 

{
	
	//FragColor = vec4(0.8, 0.6, 0.1, 1.0);	
	FragColor = u_color;
}
