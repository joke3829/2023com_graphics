#version 330 core

in vec3 PassColor;
in vec3 PassNormal; 
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 veiwPos;
//uniform vec3 lightPos;		// 조명 위치
uniform vec3 lightColor;	// 조명의 색

void main()
{
	vec3 lightPos = vec3(FragPos.x, 22.0, FragPos.z);
	vec3 lightPower = lightColor / (length(lightPos - FragPos)* 0.05);
	vec3 ambientLight = vec3(0.1);
	vec3 ambient = ambientLight * vec3(1.0);

	vec3 normalVector = normalize(PassNormal);
	//vec3 lightDir = normalize(lightPos - FragPos);
	vec3 lightDir = normalize(vec3(0, 1, 0));

	float diffuseLight = max(dot(normalVector, lightDir), 0.0);
	vec3 diffuse = diffuseLight * lightPower;

	int sh = 128;
	vec3 viewDir = normalize(veiwPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normalVector);
	float specularLight = max(dot(viewDir, reflectDir), 0.0);
	specularLight = pow(specularLight, sh);
	vec3 specular = specularLight * lightPower;
	
	vec3 result = (diffuse * PassColor) + (specular * PassColor) + (ambient * PassColor);
	
	FragColor = vec4(result, 1.0);
}