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
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;  

void main()
{
	vec3 viewLightDir = vec3 (view * vec4(light.direction, 0.0f));

	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb; // * lightColor 

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-viewLightDir);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb; // * lightColor 

	// specular
	vec3 viewDir = normalize(vec3(0.0f) - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb; // * lightColor 

	vec3 result = ambient + diffuse + specular; // + texture(material.emission, texCoords).rgb;// * objectColor;
	color = vec4(result, 1.0f);
}