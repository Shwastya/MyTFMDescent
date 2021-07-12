#TYPE V
#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aUv;
layout (location=2) in vec3 aNormal;
layout (location=3) in vec3 aTangent;
layout (location=4) in vec3 aBitangent;



uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normalMat;

uniform int u_IsMaterial;

out vec3 normali;
out vec3 fragPos;
out vec2 uv;
out mat3 TBN;

flat out int v_IsMaterial;

void main()
{

    v_IsMaterial = u_IsMaterial;


    if (v_IsMaterial > 0)
    {
      uv = aUv;
      normali = normalMat * aNormal;
      fragPos = vec3(model * vec4(aPos, 1.0));
      gl_Position = proj * view * model * vec4(aPos, 1.0);
    }
    else
    {
      uv = aUv;

      vec3 T = normalize(normalMat * aTangent);
      vec3 N = normalize(normalMat * aNormal);
      T = normalize(T - dot(T, N) * N);
      vec3 B = cross(N, T);

      TBN = mat3(T, B, N); // world space
     //mat3 TBN = transpose(mat3(T, B, N)); // tangent space

      fragPos = vec3(model * vec4(aPos, 1.0));
      gl_Position = proj * view * model * vec4(aPos, 1.0);
    }

}














#TYPE F
#version 330 core

out vec4 FragColor;

in vec3 normali;
in vec3 fragPos;
in vec2 uv;
in mat3 TBN;

flat in int v_IsMaterial;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    int shininess;
};
uniform Material material;


struct MaterialM
{
    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    int shininess;
};
uniform MaterialM materialM;

struct DirLight {

  //  vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;

struct PointLight {

    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
#define NUMBER_POINT_LIGHTS 10
uniform PointLight pointLight[NUMBER_POINT_LIGHTS];

struct SpotLight {

    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};
#define NUMBER_SPOT_LIGHTS 2
uniform SpotLight spotLight[NUMBER_SPOT_LIGHTS];

uniform vec3 viewPos;

vec3 calcDirectionalLight(DirLight light, vec3 normal, vec3 viewDir, vec3 albedoMap, vec3 specularMap)
{

    vec3 ambient = albedoMap * light.ambient;

    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * albedoMap * light.diffuse;

    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = spec * specularMap * light.specular;

    return ambient + diffuse + specular;
};

vec3 calcDirectionalLightM(DirLight light, vec3 normal, vec3 viewDir)
{

    vec3 ambient = materialM.ambient * light.ambient;

    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * materialM.diffuse * light.diffuse;

    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, halfwayDir), 0.0), materialM.shininess);
    vec3 specular = spec * materialM.specular * light.specular;

    return ambient + diffuse + specular;
};

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 albedoMap, vec3 specularMap)
{

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant +
    light.linear * distance +
    light.quadratic * distance * distance);

    vec3 ambient = albedoMap * light.ambient;

    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * albedoMap * light.diffuse;

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = spec * specularMap * light.specular;

    return (ambient + diffuse + specular) * attenuation;
};

vec3 calcPointLightM(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant +
    light.linear * distance +
    light.quadratic * distance * distance);

    vec3 ambient = materialM.ambient * light.ambient;

    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * materialM.diffuse * light.diffuse;

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), materialM.shininess);
    vec3 specular = spec * materialM.specular * light.specular;

    return (ambient + diffuse + specular) * attenuation;
};

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 albedoMap, vec3 specularMap)
{

    float distance = length(light.position - fragPos); // LONGITUD
    float attenuation = 1.0 / (light.constant +
    light.linear * distance +
    light.quadratic * distance * distance);

    vec3 ambient = albedoMap * light.ambient;

    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * albedoMap * light.diffuse;

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = spec * specularMap * light.specular;

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    return (ambient + (diffuse * intensity) + (specular * intensity)) * attenuation;
};

vec3 calcSpotLightM(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{

    float distance = length(light.position - fragPos); // LONGITUD
    float attenuation = 1.0 / (light.constant +
    light.linear * distance +
    light.quadratic * distance * distance);

    vec3 ambient = materialM.ambient * light.ambient;

    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * materialM.diffuse * light.diffuse;

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), materialM.shininess);
    vec3 specular = spec * materialM.specular * light.specular;

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    return (ambient + (diffuse * intensity) + (specular * intensity)) * attenuation;
};

void main() {

  if (v_IsMaterial > 0)
  {


    vec3 norm =     normalize(normali);
    vec3 viewDir =    normalize(viewPos - fragPos);

    vec3 finalColor = calcDirectionalLightM(dirLight, norm, viewDir);

    for (int i = 0; i < NUMBER_POINT_LIGHTS; i++)
    {
        finalColor += calcPointLightM(pointLight[i], norm, viewDir, fragPos);
    }

    for (int i = 0; i < NUMBER_SPOT_LIGHTS; i++)
    {
        finalColor += calcSpotLightM(spotLight[i], norm, viewDir, fragPos);
	  }

    FragColor = vec4(finalColor, 1.0f);
  }
  else
  {
    vec3 albedo = vec3(texture(material.diffuse, uv));
    vec3 specular = vec3(texture(material.specular, uv));

    vec3 norm = vec3(texture(material.normal, uv));
    norm = normalize(norm * 2.0 - 1.0);
    norm = normalize(TBN * norm);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 finalColor = calcDirectionalLight(dirLight, norm, viewDir, albedo, specular);

    for (int i = 0; i < NUMBER_POINT_LIGHTS; i++)
    {
        finalColor += calcPointLight(pointLight[i], norm, viewDir, fragPos, albedo, specular);
	  }

    for (int i = 0; i < NUMBER_SPOT_LIGHTS; i++)
    {
        finalColor += calcSpotLight(spotLight[i], norm, viewDir, fragPos, albedo, specular);
	  }

    FragColor = vec4(finalColor, 1.0);
  }
}
