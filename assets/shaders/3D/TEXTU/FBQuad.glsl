#TYPE V
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aNormal;


out vec2 uvs;

void main()
{
  uvs = aUv;
  gl_Position = vec4(aPos, 1.0);
}

#TYPE F
#version 330 core

out vec4 FragColor;

in vec2 uvs;

uniform sampler2D screenTexture;

void main()
{
  FragColor = texture(screenTexture, uvs);
  //FragColor = vec4(1.0, 0.2, 0.1, 1.0);

}
