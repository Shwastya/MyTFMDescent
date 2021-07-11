#TYPE V
#version 330 core

layout (location=0) in vec3 a_Pos;
layout (location=1) in vec2 a_UVS;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;


out vec2 v_uvs;

void main()
{
    v_uvs = a_UVS;

    gl_Position = u_proj * u_view * u_model * vec4(a_Pos, 1.0);
}


#TYPE F
#version 330 core

out vec4 FragColor;

in vec2 v_uvs;

uniform vec4 u_color;
uniform sampler2D u_text;

void main()
{
  FragColor = texture(u_text, v_uvs);
  FragColor = texture(u_text, v_uvs * 10) * u_color;
  FragColor = texture(u_text, v_uvs) * u_color;

//  FragColor = vec4(v_uvs, 0.0, 1.0);
}
