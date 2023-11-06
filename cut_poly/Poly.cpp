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
		coor.push_back(glm::vec3(-0.2, 0.1, 0));
		coor.push_back(glm::vec3(0.1, -0.2, 0));
		coor.push_back(glm::vec3(0.2, 0.2, 0));
		for(int i = 0 ; i < 3; ++i)
			color.push_back(glm::vec3(r, g, b));
		break;
	case 1:
		coor.push_back(glm::vec3(-0.2, 0.1, 0));
		coor.push_back(glm::vec3(-0.1, -0.2, 0));
		coor.push_back(glm::vec3(0.2, -0.1, 0));
		coor.push_back(glm::vec3(0.1, 0.2, 0));
		for (int i = 0; i < 4; ++i)
			color.push_back(glm::vec3(r, g, b));
		break;
	case 2:
		coor.push_back(glm::vec3(-0.17, 0.1, 0));
		coor.push_back(glm::vec3(-0.2, -0.1, 0));
		coor.push_back(glm::vec3(0.1, -0.2, 0));
		coor.push_back(glm::vec3(0.2, 0, 0));
		coor.push_back(glm::vec3(0.1, 0.2, 0));
		for (int i = 0; i < 5; ++i)
			color.push_back(glm::vec3(r, g, b));
		break;
	case 3:
		coor.push_back(glm::vec3(0.2*glm::cos(glm::radians(-10.0f)), 0.2*glm::sin(glm::radians(-10.0f)), 0));
		coor.push_back(glm::vec3(0.2 * glm::cos(glm::radians(50.0f)), 0.2 * glm::sin(glm::radians(50.0f)), 0));
		coor.push_back(glm::vec3(0.2 * glm::cos(glm::radians(110.0f)), 0.2 * glm::sin(glm::radians(110.0f)), 0));
		coor.push_back(glm::vec3(0.2 * glm::cos(glm::radians(170.0f)), 0.2 * glm::sin(glm::radians(170.0f)), 0));
		coor.push_back(glm::vec3(0.2 * glm::cos(glm::radians(230.0f)), 0.2 * glm::sin(glm::radians(230.0f)), 0));
		coor.push_back(glm::vec3(0.2 * glm::cos(glm::radians(290.0f)), 0.2 * glm::sin(glm::radians(290.0f)), 0));
		for (int i = 0; i < 6; ++i)
			color.push_back(glm::vec3(r, g, b));
		break;
	case 4:
		coor.push_back(glm::vec3(0.2 * glm::cos(glm::radians(-10.0f)), 0.2 * glm::sin(glm::radians(-10.0f)), 0));
		coor.push_back(glm::vec3(0.2 * glm::cos(glm::radians(35.0f)), 0.2 * glm::sin(glm::radians(35.0f)), 0));
		coor.push_back(glm::vec3(0.2 * glm::cos(glm::radians(80.0f)), 0.2 * glm::sin(glm::radians(80.0f)), 0));
		coor.push_back(glm::vec3(0.2 * glm::cos(glm::radians(125.0f)), 0.2 * glm::sin(glm::radians(125.0f)), 0));
		coor.push_back(glm::vec3(0.2 * glm::cos(glm::radians(170.0f)), 0.2 * glm::sin(glm::radians(170.0f)), 0));
		coor.push_back(glm::vec3(0.2 * glm::cos(glm::radians(215.0f)), 0.2 * glm::sin(glm::radians(215.0f)), 0));
		coor.push_back(glm::vec3(0.2 * glm::cos(glm::radians(260.0f)), 0.2 * glm::sin(glm::radians(260.0f)), 0));
		coor.push_back(glm::vec3(0.2 * glm::cos(glm::radians(305.0f)), 0.2 * glm::sin(glm::radians(305.0f)), 0));
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

	view_route = false;
	for (float i = 0; i < 1; i += 0.01) {
		Lcoor.push_back(glm::vec3(((1 - i) * (1 - i) * controlPos[0].x) + (2 * i * (1 - i) * controlPos[1].x) + (i * i * controlPos[2].x),
			((1 - i) * (1 - i) * controlPos[0].y) + (2 * i * (1 - i) * controlPos[1].y) + (i * i * controlPos[2].y),
			0));
		Lcolor.push_back(glm::vec3(r, g, b));
	}
	route_mat = glm::mat4(1.0f);
}

Poly::Poly(GLuint* shaderProgram, std::vector<glm::vec3> new_pos, std::vector<glm::vec3> new_color, glm::vec2 new_loc, int way) : shader(shaderProgram)	// 잘리고 새로만들어진 도형
{
	t = 0;
	put_bucket = false;
	cutting = true;
	init_check = false;
	cur_loc = new_loc;
	modelTrans = glm::mat4(1.0f);
	glm::mat4 m_temp(1.0f);
	modelTrans = glm::translate(m_temp, glm::vec3(cur_loc, 0)) * modelTrans;
	coor = new_pos;
	for (int i = 0; i < coor.size(); ++i)
		color.push_back(glm::vec3(new_color[0].x, new_color[0].y, new_color[0].z));
	switch (way) {
	case 4:
		controlPos[0] = cur_loc;
		controlPos[1] = glm::vec2(cur_loc.x - 0.2, cur_loc.y + 0.5);
		controlPos[2] = glm::vec2(cur_loc.x - 0.4, cur_loc.y - 6);
		break;
	case 6:
		controlPos[0] = cur_loc;
		controlPos[1] = glm::vec2(cur_loc.x + 0.2, cur_loc.y + 0.5);
		controlPos[2] = glm::vec2(cur_loc.x + 0.4, cur_loc.y - 6);
		break;
	}

	view_route = false;
	for (float i = 0; i < 1; i += 0.01) {
		Lcoor.push_back(glm::vec3(((1 - i) * (1 - i) * controlPos[0].x) + (2 * i * (1 - i) * controlPos[1].x) + (i * i * controlPos[2].x),
			((1 - i) * (1 - i) * controlPos[0].y) + (2 * i * (1 - i) * controlPos[1].y) + (i * i * controlPos[2].y),
			0));
		Lcolor.push_back(glm::vec3(new_color[0].x, new_color[0].y, new_color[0].z));
	}
	route_mat = glm::mat4(1.0f);

}

void Poly::deleteBuffer()
{
	if (init_check) {
		glDeleteBuffers(2, VBO);
		glDeleteVertexArrays(1, &VAO);

		glDeleteBuffers(2, LVBO);
		glDeleteVertexArrays(1, &LVAO);
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

	glGenVertexArrays(1, &LVAO);
	glBindVertexArray(LVAO);

	glGenBuffers(2, LVBO);
	glBindBuffer(GL_ARRAY_BUFFER, LVBO[0]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * Lcoor.size(), &Lcoor.front(), GL_STATIC_DRAW);
	loc = glGetAttribLocation(*shader, "vPos");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	glBindBuffer(GL_ARRAY_BUFFER, LVBO[1]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * Lcolor.size(), &Lcolor.front(), GL_STATIC_DRAW);
	loc = glGetAttribLocation(*shader, "vColor");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);
}

void Poly::setSpeed(float new_speed)
{
	speed = new_speed;
}

void Poly::setView(bool flag, bool route)
{
	view_poly = flag;
	view_route = route;
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
	if (view_route && not put_bucket) {
		uni = glGetUniformLocation(*shader, "transform");
		glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(route_mat));
		glBindVertexArray(LVAO);
		glDrawArrays(GL_LINES, 0, Lcoor.size());
	}
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

bool Poly::check_cut(glm::vec2 start, glm::vec2 end)
{
	if (put_bucket)
		return false;
	place_cross[0] = place_cross[1] = 0;
	vertex_list.clear();
	if (start.x == end.x)
		end.x += 0.0001;
	float minx, maxx, temp;
	float miny, maxy;
	float cutter_m, rect_n;	//기울기
	float cross_x;
	glm::vec2 first, second;
	cutter_m = (end.y - start.y) / (end.x - start.x);
	vertex_list.push_back(coor[0]);
	bool crossPos[2]{ false, false };
	for (int i = 0; i < coor.size(); ++i) {
		if (i == coor.size() - 1) {
			minx = start.x;
			maxx = end.x;
			if (minx > maxx) {
				temp = minx;
				minx = maxx;
				maxx = temp;
			}
			miny = coor[i].y + cur_loc.y;
			maxy = coor[0].y + cur_loc.y;
			if (miny > maxy) {
				temp = miny;
				miny = maxy;
				maxy = temp;
			}
			first.x = coor[i].x + cur_loc.x; first.y = coor[i].y + cur_loc.y;
			second.x = coor[0].x + cur_loc.x; second.y = coor[0].y + cur_loc.y;
			rect_n = (second.y - first.y) / (second.x - first.x);
			/*cross_x = ((1 / (cutter_m - rect_n)) * ((-1 * rect_n * first.x) + first.y - start.y)) +
				((cutter_m / (cutter_m - rect_n)) * start.x);*/
			cross_x = (1 / (cutter_m - rect_n)) * ((-1 * rect_n * first.x) + first.y + (cutter_m * start.x) - start.y);
			if (cross_x >= minx && cross_x <= maxx &&
				miny <= ((cutter_m * (cross_x - start.x)) + start.y) && maxy >= ((cutter_m * (cross_x - start.x)) + start.y)) {
				if (crossPos[0]) {
					crossPos[1] = true;
				}
				else
					crossPos[0] = true;
				if (place_cross[1] == 0) {
					vertex_list.push_back(glm::vec3(cross_x - cur_loc.x, ((cutter_m * (cross_x - start.x)) + start.y) - cur_loc.y, 0));
					if (place_cross[0] == 0)
						place_cross[0] = vertex_list.size() - 1;
					else
						place_cross[1] = vertex_list.size() - 1;
				}
			}
		}
		else {
			minx = start.x;
			maxx = end.x;
			if (minx > maxx) {
				temp = minx;
				minx = maxx;
				maxx = temp;
			}
			miny = coor[i].y + cur_loc.y;
			maxy = coor[i+ 1].y + cur_loc.y;
			if (miny > maxy) {
				temp = miny;
				miny = maxy;
				maxy = temp;
			}
			first.x = coor[i].x + cur_loc.x; first.y = coor[i].y + cur_loc.y;
			second.x = coor[i + 1].x + cur_loc.x; second.y = coor[i + 1].y + cur_loc.y;
			rect_n = (second.y - first.y) / (second.x - first.x);
			/*cross_x = ((1 / (cutter_m - rect_n)) * ((-1 * rect_n * first.x) + first.y - start.y)) +
				((cutter_m / (cutter_m - rect_n)) * start.x);*/
			cross_x = (1 / (cutter_m - rect_n)) * ((-1 * rect_n * first.x) + first.y + (cutter_m * start.x) - start.y);
			if (cross_x >= minx && cross_x <= maxx &&
				miny <= ((cutter_m* (cross_x - start.x)) + start.y) && maxy >= ((cutter_m * (cross_x - start.x)) + start.y)) {
				if (crossPos[0]) {
					crossPos[1] = true;
				}
				else
					crossPos[0] = true;
				if (place_cross[1] == 0) {
					vertex_list.push_back(glm::vec3(cross_x - cur_loc.x, ((cutter_m * (cross_x - start.x)) + start.y) - cur_loc.y, 0));
					if (place_cross[0] == 0)
						place_cross[0] = vertex_list.size() - 1;
					else
						place_cross[1] = vertex_list.size() - 1;
				}
			}
		}
		if(i != coor.size() - 1)
			vertex_list.push_back(coor[i + 1]);
	}
	if (crossPos[0] && crossPos[1])
		return true;
	else
		return false;
}

std::vector<glm::vec3> Poly::return_L()
{
	std::vector<glm::vec3> left_coor;
	for (int i = 0; i < vertex_list.size(); ++i) {
		if (i == place_cross[0]) {
			left_coor.push_back(vertex_list[i]);
			i = place_cross[1] - 1;
		}
		else {
			left_coor.push_back(vertex_list[i]);
		}
	}
	return left_coor;
}

std::vector<glm::vec3> Poly::return_R()
{
	std::vector<glm::vec3> right_coor;
	for (int i = place_cross[0]; i <= place_cross[1]; ++i) {
		right_coor.push_back(vertex_list[i]);
	}
	return right_coor;
}

glm::vec2 Poly::return_loc()
{
	return cur_loc;
}

std::vector<glm::vec3> Poly::return_color()
{
	return color;
}

bool Poly::check_put()
{
	return put_bucket;
}

void Poly::crash_check(const Bucket& b)
{
	glm::vec2 LB = b.return_coor_LB();
	glm::vec2 RT = b.return_coor_RT();
	glm::vec2 min(coor[0].x + cur_loc.x, coor[0].y + cur_loc.y);
	for (int i = 1; i < coor.size(); ++i) {
		if (min.y > coor[i].y + cur_loc.y) {
			min.x = coor[i].x + cur_loc.x;
			min.y = coor[i].y + cur_loc.y;
		}
	}
	if (LB.x <= min.x && RT.x >= min.x &&
		LB.y <= min.y && RT.y >= min.y && cutting) {
		put_bucket = true;
	}
}

void Poly::Move(bool way)
{
	glm::mat4 temp(1.0f);
	if (way) {
		modelTrans = glm::translate(temp, glm::vec3(-0.01, 0, 0)) * modelTrans;
	}
	else {
		modelTrans = glm::translate(temp, glm::vec3(0.01, 0, 0)) * modelTrans;
	}
}