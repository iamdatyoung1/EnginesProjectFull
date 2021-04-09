#version 450 core

struct Light
{
  vec3 lightPos;
  float ambientV;
  float diffuseV;
  float specularV;
  vec3 lightColour;
};
struct Material
{
 float shini; //Ns
 float trans; //d
 vec3 ambient; //ka
 vec3 diffuseMap;
 vec3 specular;
 
};



in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;

uniform sampler2D inputTexture;
uniform vec3 cameraPosition;
uniform Material material;

uniform Light light;

out vec4 fColour;



void main(){
    
	vec3 ambient = light.ambientV* material.ambient* texture(inputTexture, TexCoords).rgb* light.lightColour;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos-FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb* light.lightColour;

	vec3 viewDir = normalize(cameraPosition-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = (spec * light.specularV)* light.lightColour;

	vec3 result = ambient + diffuse + specular;

	fColour = vec4(result, 1.0f);
}