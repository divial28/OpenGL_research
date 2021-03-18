#version 330 core

precision mediump float;

in vec3 Normal;
in vec3 FragPos;
in vec2 texCoords;

out vec4 color;

uniform mat4 view;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
	sampler2D emission;
    float shininess;
};

uniform Material material;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

uniform Light light;  

void main()
{
	vec3 viewLightPos = vec3 (view * vec4(light.position, 1.0f));


    float dist = distance(viewLightPos, FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb; // * lightColor 

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(viewLightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb; // * lightColor 

	// specular
	vec3 viewDir = normalize(vec3(0.0f) - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb; // * lightColor 

	vec3 result = (ambient + diffuse + specular) * attenuation; // + texture(material.emission, texCoords).rgb;// * objectColor;
	color = vec4(result, 1.0f);
}