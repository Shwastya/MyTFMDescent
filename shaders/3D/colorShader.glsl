#TYPE V
#version 330 core

layout (location=0) in vec3 a_Pos;

uniform mat4 u_Model; // ModelProjection
uniform mat4 u_View;  // ViewProjection
uniform mat4 u_Proj;  // Projection

void main()
{ 
	gl_Position = u_Proj * u_View * u_Model * vec4(a_Pos, 1.0);
}



#TYPE F
#version 330 core

out vec4 FragColor;

uniform vec3 u_Color;

void main() 

{	
	FragColor = vec4(u_Color, 1.0);	    
}


