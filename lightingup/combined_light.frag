#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct ProjectedLight {
    vec3  position;
    vec3  direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float cutOffOut;
    float constant;
    float linear;
    float quadratic;
};
uniform ProjectedLight projectedLight;

uniform vec3 viewPos;
uniform mat4 view;

out vec4 color;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcProjectedLight(ProjectedLight light, vec3 normal, vec3 fragPos, vec3 viewDir, mat4 view);


void main()
{
    // свойства
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // фаза 1: Направленный источник освещения
    //vec3 result = CalcDirLight(dirLight, norm, viewDir);
    //vec3 result = vec3(0.0);
    // фаза 2: Точечные источники
    //for(int i = 0; i < NR_POINT_LIGHTS; i++)
        //result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // фаза 3: фонарик
    vec3 result = CalcProjectedLight(projectedLight, norm, FragPos, viewDir, view);    
    
    color = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // диффузное освещение
    float diff = max(dot(normal, lightDir), 0.0);
    // освещение зеркальных бликов
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // комбинируем результаты
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
} 

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // диффузное освещение
    float diff = max(dot(normal, lightDir), 0.0);
    // освещение зеркальных бликов
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // затухание
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // комбинируем результаты
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

vec3 CalcProjectedLight(ProjectedLight light, vec3 normal, vec3 fragPos, vec3 viewDir, mat4 view)
{
    vec3 viewLightPos = vec3 (view * vec4(light.position, 1.0f));
    vec3 viewLightDir = vec3 (view * vec4(light.direction, 0.0f));
    vec3 lightDir = normalize(viewLightPos - FragPos);

    float theta = dot(lightDir, normalize(-viewLightDir));
    float epsilon   = light.cutOff - light.cutOffOut;
    float intensity = clamp((theta - light.cutOffOut) / epsilon, 0.0, 1.0);

    if(theta > light.cutOffOut) 
    {
               
        float dist = distance(viewLightPos, FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

        // ambient
        vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb; // * lightColor 

        // diffuse
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb; // * lightColor 

        // specular
        vec3 viewDir = normalize(vec3(0.0f) - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb; // * lightColor 

        return ambient + (diffuse + specular) * intensity * attenuation; // + texture(material.emission, texCoords).rgb;// * objectColor;
    }
    // иначе используем только фоновую компоненту, чтобы сцена не была 
    // полностью черной вне конуса прожектора
    else  
        return light.ambient * vec3(texture(material.diffuse, TexCoords));
}