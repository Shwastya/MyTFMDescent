#TYPE V
#version 330 core

layout (location=0) in vec3 a_Pos;


uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;




void main()
{
    gl_Position = u_proj * u_view * u_model * vec4(a_Pos, 1.0);
}


#TYPE F
#version 330 core

out vec4 FragColor;


uniform vec3 u_color;

void main()
{
  FragColor = vec4(u_color, 1.0);
}
