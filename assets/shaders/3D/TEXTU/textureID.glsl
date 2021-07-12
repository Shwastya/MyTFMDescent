#TYPE V
#version 450

layout (location=0) in vec3 a_Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


uniform int IDColor;

flat out int v_IDColor;



void main()
{
  v_IDColor = IDColor;
  gl_Position = proj * view * model * vec4(a_Position, 1.0);
}

#TYPE F
#version 450

out int FragColor;

flat in int v_IDColor;

void main()
{
  FragColor = 50; // ENTITY ID
}
