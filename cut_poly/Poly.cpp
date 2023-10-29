#include "Poly.h"

Poly::Poly() 
{

}

Poly::Poly(GLuint* shaderProgram, int type) : shader(shaderProgram)		// 시작 도형
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urd_color(0.0, 1.0);	

	std::uniform_real_distribution<float> conPosTop(0.0, 0.5);

	std::uniform_real_distribution<float> conPosmidX(-0.5, 0.5);
	std::uniform_real_distribution<float> conPosmidY(0.5, 1.0);

	std::uniform_real_distribution<float> conPosBottom(-2.0, 0.0);

	r = urd_color(dre); g = urd_color(dre); b = urd_color(dre);
	t = 0;
	put_bucket = false;
	cutting = false;
	modelTrans = glm::mat4(1.0f);
	switch (type) {
	case 0:
		coor.push_back(glm::vec3(0, 0.2, 0));
		coor.push_back(glm::vec3(-0.2, -0.2, 0));
		coor.push_back(glm::vec3(0.2, -0.2, 0));
		for(int i = 0 ; i < 3; ++i)
			color.push_back(glm::vec3(r, g, b));
		break;
	case 1:
		coor.push_back(glm::vec3(-0.2, 0.2, 0));
		coor.push_back(glm::vec3(-0.2, -0.2, 0));
		coor.push_back(glm::vec3(0.2, -0.2, 0));
		coor.push_back(glm::vec3(0.2, 0.2, 0));
		for (int i = 0; i < 4; ++i)
			color.push_back(glm::vec3(r, g, b));
		break;
	case 2:
		coor.push_back(glm::vec3(-0.2, 0.1, 0));
		coor.push_back(glm::vec3(-0.1, -0.2, 0));
		coor.push_back(glm::vec3(0.1, -0.2, 0));
		coor.push_back(glm::vec3(0.2, 0.1, 0));
		coor.push_back(glm::vec3(0, 0.2, 0));
		for (int i = 0; i < 5; ++i)
			color.push_back(glm::vec3(r, g, b));
		break;
	case 3:
		coor.push_back(glm::vec3(-0.1, 0.2, 0));
		coor.push_back(glm::vec3(-0.2, 0, 0));
		coor.push_back(glm::vec3(-0.1, -0.2, 0));
		coor.push_back(glm::vec3(0.1, -0.2, 0));
		coor.push_back(glm::vec3(0.2, 0, 0));
		coor.push_back(glm::vec3(0.1, 0.2, 0));
		for (int i = 0; i < 6; ++i)
			color.push_back(glm::vec3(r, g, b));
		break;
	case 4:
		coor.push_back(glm::vec3(-0.1, 0.2, 0));
		coor.push_back(glm::vec3(-0.2, 0.1, 0));
		coor.push_back(glm::vec3(-0.2, -0.1, 0));
		coor.push_back(glm::vec3(-0.1, -0.2, 0));
		coor.push_back(glm::vec3(0.1, -0.2, 0));
		coor.push_back(glm::vec3(0.2, -0.1, 0));
		coor.push_back(glm::vec3(0.2, 0.1, 0));
		coor.push_back(glm::vec3(0.1, 0.2, 0));
		for (int i = 0; i < 8; ++i)
			color.push_back(glm::vec3(r, g, b));
		break;
	}
	if (urd_color(dre) > 0.5) {		// 왼쪽에서 날라오자
		controlPos[0] = glm::vec2(-1.2, conPosTop(dre));
		cur_loc = controlPos[0];
		controlPos[1] = glm::vec2(conPosmidX(dre), conPosmidY(dre));
		controlPos[2] = glm::vec2(1.2, conPosBottom(dre));
	}
	else {							// 오른쪽에서 날라오자
		controlPos[0] = glm::vec2(1.2, conPosTop(dre));
		cur_loc = controlPos[0];
		controlPos[1] = glm::vec2(conPosmidX(dre), conPosmidY(dre));
		controlPos[2] = glm::vec2(-1.2, conPosBottom(dre));
	}
	glm::mat4 m_temp(1.0f);
	modelTrans = glm::translate(m_temp, glm::vec3(cur_loc, 0)) * modelTrans;
	init_check = false;
}

Poly::Poly(GLuint* shaderProgram, std::vector<glm::vec3> new_pos) : shader(shaderProgram)	// 잘리고 새로만들어진 도형
{
	t = 0;
	put_bucket = false;
	cutting = true;
	modelTrans = glm::mat4(1.0f);
	coor = new_pos;


	glGenVertexArrays(1, &VAO);

}

void Poly::deleteBuffer()
{
	if (init_check) {
		glDeleteBuffers(2, VBO);
		glDeleteVertexArrays(1, &VAO);
	}
}

void Poly::Initialize()
{
	init_check = true;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(2, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * coor.size(), &coor.front(), GL_STATIC_DRAW);
	int loc = glGetAttribLocation(*shader, "vPos");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * color.size(), &color.front(), GL_STATIC_DRAW);
	loc = glGetAttribLocation(*shader, "vColor");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);
}

void Poly::setSpeed(float new_speed)
{
	speed = new_speed;
}

void Poly::setView(bool flag)
{
	view_poly = flag;
}

void Poly::Draw()
{
	int uni = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(modelTrans));
	glBindVertexArray(VAO);
	if (view_poly)
		glDrawArrays(GL_TRIANGLE_FAN, 0, coor.size());
	else
		glDrawArrays(GL_LINE_LOOP, 0, coor.size());
}

void Poly::Move(glm::vec2 new_loc)
{
	glm::mat4 temp(1.0f);
	modelTrans = glm::translate(temp, glm::vec3(-cur_loc.x, -cur_loc.y, 0)) * modelTrans; temp = glm::mat4(1.0f);
	cur_loc = new_loc;
	modelTrans = glm::translate(temp, glm::vec3(cur_loc, 0)) * modelTrans; temp = glm::mat4(1.0f);
}

glm::vec2 Poly::move_xy()
{
	glm::vec2 c_loc(0, 0);
	if (t < 1) {
		t += speed;
		c_loc.x = ((1 - t) * (1 - t) * controlPos[0].x) + (2 * t * (1 - t) * controlPos[1].x) + (t * t * controlPos[2].x);
		c_loc.y = ((1 - t) * (1 - t) * controlPos[0].y) + (2 * t * (1 - t) * controlPos[1].y) + (t * t * controlPos[2].y);
	}
	return c_loc;
}

float Poly::return_t()
{
	return t;
}