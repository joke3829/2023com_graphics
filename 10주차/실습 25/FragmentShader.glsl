#version 330 core

in vec3 PassColor;
in vec3 PassNormal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 lightPos;		// 조명 위치
uniform vec3 lightColor;	// 조명의 색

void main()
{
	vec3 ambientLight = vec3(0.1);
	vec3 ambient = ambientLight * lightColor;

	vec3 normalVector = normalize(PassNormal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuseLight = max(dot(normalVector, lightDir), 0.0);
	vec3 diffuse = diffuseLight * lightColor;
	
	vec3 result = (diffuse * PassColor) + (ambient * PassColor);
	
	FragColor = vec4(result, 1.0);
}