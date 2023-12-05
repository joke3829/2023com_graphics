#pragma once


#include "stdafx.h"

class ShaderProgram;
class LightObj {
public:
	LightObj();
	
	void lightButton();
	void change_color(int n);
	void OutToShader();
private:
	ShaderProgram* shader;
	glm::vec3 lightColor;
};