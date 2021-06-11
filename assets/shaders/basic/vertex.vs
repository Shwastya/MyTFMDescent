#version 330 core

layout (location=0) in vec3 aPos;

out vec3 test_position_as_Color;

void main()
{
    test_position_as_Color = aPos;
	gl_Position = vec4(aPos, 1.0);
}