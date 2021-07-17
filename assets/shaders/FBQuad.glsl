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


const float offset = 1.0 / 600.0;

void main()
{

  vec2 offsets[9] = vec2[]
  (
      vec2(-offset, offset),
      vec2(0.0, offset),
      vec2(offset, offset),
      vec2(-offset, 0.0),
      vec2(0.0, 0.0),
      vec2(offset, 0.0),
      vec2(-offset, -offset),
      vec2(0.0, -offset),
      vec2(offset, -offset)
  );

  float Kernel[9] = float[]
  (
      1, 1, 1,
      1,  -8, 1,
      1, 1, 1
  );

  vec3 color = vec3(0.0);

  for (int i = 0; i < 9; ++i)
  {
    color += vec3(texture(screenTexture, uvs.st + offsets[i])) * Kernel[i];
  }

  FragColor = vec4(color, 1.0);
  //FragColor = texture(screenTexture, uvs);
  //FragColor = vec4(1.0, 0.2, 0.1, 1.0);

}
