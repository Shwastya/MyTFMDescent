#TYPE V
#version 330 core

layout (location=0) in vec3 a_Pos;
layout (location=1) in vec2 a_UVS;
layout (location=2) in vec3 a_Normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
uniform mat3 u_normalMat;

out vec3 v_normal;
out vec3 v_fragPos;

void main()
{
    v_normal = u_normalMat * a_Normal;
    v_fragPos = vec3(u_model * vec4(a_Pos, 1.0));
    gl_Position = u_proj * u_view * u_model * vec4(a_Pos, 1.0);
}

#TYPE F
#version 330 core

out vec4 FragColor;

in vec3 v_normal;
in vec3 v_fragPos;

struct Material
{
    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    int shininess;
};
uniform Material u_material;

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light u_light;

uniform vec3  u_viewPos;


void main()
{
    vec3 ambient = u_material.ambient * u_light.ambient;

    vec3 norm =     normalize(v_normal);
    vec3 lightDir = normalize(u_light.position - v_fragPos);
    float diff =    max(dot(norm, lightDir), 0.0);
    vec3 diffuse =  diff * u_material.diffuse * u_light.diffuse;

    vec3 viewDir =    normalize(u_viewPos - v_fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec =      pow(max(dot(norm, halfwayDir), 0.0), u_material.shininess);
    vec3 specular =   spec * u_material.specular * u_light.specular;

    vec3 phong = ambient + diffuse + specular;
    FragColor = vec4(phong, 1.0f);
}
