#pragma once
#include<random>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> urd_color(0.0, 1.0);

class LINE_OBJ {
	float coor[12]{};
	float color[12]{};
	GLuint vao, vbo[2];
public:
	LINE_OBJ()
	{
		coor[0] = coor[9] = coor[1] = coor[4] = -0.5;
		coor[3] = coor[6] = coor[7] = coor[10] = 0.5;
		for (int i = 0; i < 12; ++i) {
			color[i] = urd_color(dre);
		}
	}
	LINE_OBJ(int line)
	{
		switch (line) {
		case 0:
			coor[1] = 1;
			coor[4] = -1;
			break;
		case 1:
			coor[0] = -1;
			coor[3] = 1;
			break;
		}
		color[0] = color[1] = color[2] = color[3] = color[4] = color[5] = 0;
	}
	// vao, vbo 생성
	void Gen()
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(2, vbo);
	}
	
	void InitBuffer()
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(coor), coor, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
	}

	void Draw()
	{
		glBindVertexArray(vao);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}

	void Draw_line()
	{
		glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, 2);
	}

	int Grab_point(float x, float y)
	{
		for (int i = 0; i < 12; i += 3)
		{
			if (coor[i] - 0.05 <= x && coor[i] + 0.05 >= x &&
				coor[i + 1] - 0.05 <= y && coor[i + 1] + 0.05 >= y) {
				return i / 3;
			}
		}
		return -1;
	}

	void move_point(int p_num, float x, float y)
	{
		coor[p_num * 3] = x;
		coor[p_num * 3 + 1] = y;
	}

	bool Mouse_Check(float x, float y)
	{
		float inclination_1, inclination_2;
		float max_y, min_y;
		min_y = coor[1]; max_y = coor[7];
		for (int i = 0; i < 12; i += 3) {
			if (min_y > coor[i + 1])
				min_y = coor[i + 1];
			if (max_y < coor[i + 1])
				max_y = coor[i + 1];
		}
		if (y >= min_y && y <= max_y) {
			if (max_y == coor[10]) {			// 3번 점이 올라갔을 때
				if (y >= coor[7]) {				// 마우스가 2번 점보다 위에 있을 때
					inclination_1 = (coor[3] - coor[9]) / (coor[4] - coor[10]);
					inclination_2 = (coor[6] - coor[9]) / (coor[7] - coor[10]);
					if ((coor[9] + (y - coor[10]) * inclination_1) <= x &&
						(coor[9] + (y - coor[10]) * inclination_2) >= x) {
						return true;
					}
				}
				else {
					inclination_1 = (coor[3] - coor[9]) / (coor[4] - coor[10]);
					inclination_2 = (coor[3] - coor[6]) / (coor[4] - coor[7]);
					if ((coor[9] + (y - coor[10]) * inclination_1) <= x &&
						(coor[6] + (y - coor[7]) * inclination_2) >= x) {
						return true;
					}
				}
				if (min_y == coor[1]) {			// 0번 점이 내려갔을 때
					if (y >= coor[4]) {
						inclination_1 = (coor[0] - coor[9]) / (coor[1] - coor[10]);
						inclination_2 = (coor[3] - coor[9]) / (coor[4] - coor[10]);
						if ((coor[9] + (y - coor[10]) * inclination_1) <= x &&
							(coor[9] + (y - coor[10]) * inclination_2) >= x) {
							return true;
						}
					}
					else {
						inclination_1 = (coor[0] - coor[9]) / (coor[1] - coor[10]);
						inclination_2 = (coor[0] - coor[3]) / (coor[1] - coor[4]);
						if ((coor[9] + (y - coor[10]) * inclination_1) <= x &&
							(coor[3] + (y - coor[4]) * inclination_2) >= x) {
							return true;
						}
					}
				}
				else if (min_y == coor[4]) {	// 1번 점이 내려갔을 때
					if (y >= coor[1]) {
						inclination_1 = (coor[0] - coor[9]) / (coor[1] - coor[10]);
						inclination_2 = (coor[3] - coor[9]) / (coor[4] - coor[10]);
						if ((coor[9] + (y - coor[10]) * inclination_1) <= x &&
							(coor[9] + (y - coor[10]) * inclination_2) >= x) {
							return true;
						}
					}
					else {
						inclination_1 = (coor[3] - coor[0]) / (coor[4] - coor[1]);
						inclination_2 = (coor[3] - coor[9]) / (coor[4] - coor[10]);
						if ((coor[0] + (y - coor[1]) * inclination_1) <= x &&
							(coor[9] + (y - coor[10]) * inclination_2) >= x) {
							return true;
						}
					}
				}
			}
			else if (max_y == coor[7]) {		// 2번 점이 올라갔을 때
				if (y >= coor[10]) {				// 마우스가 3번 점보다 위에 있을 때
					inclination_1 = (coor[9] - coor[6]) / (coor[10] - coor[7]);
					inclination_2 = (coor[3] - coor[6]) / (coor[4] - coor[7]);
					if ((coor[6] + (y - coor[7]) * inclination_1) <= x &&
						(coor[6] + (y - coor[7]) * inclination_2) >= x) {
						return true;
					}
				}
				else {
					inclination_1 = (coor[3] - coor[9]) / (coor[4] - coor[10]);
					inclination_2 = (coor[3] - coor[6]) / (coor[4] - coor[7]);
					if ((coor[9] + (y - coor[10]) * inclination_1) <= x &&
						(coor[6] + (y - coor[7]) * inclination_2) >= x) {
						return true;
					}
				}
				if (min_y == coor[1]) {
					if (y >= coor[4]) {
						inclination_1 = (coor[0] - coor[9]) / (coor[1] - coor[10]);
						inclination_2 = (coor[3] - coor[9]) / (coor[4] - coor[10]);
						if ((coor[9] + (y - coor[10]) * inclination_1) <= x &&
							(coor[9] + (y - coor[10]) * inclination_2) >= x) {
							return true;
						}
					}
					else {
						inclination_1 = (coor[0] - coor[9]) / (coor[1] - coor[10]);
						inclination_2 = (coor[0] - coor[3]) / (coor[1] - coor[4]);
						if ((coor[9] + (y - coor[10]) * inclination_1) <= x &&
							(coor[3] + (y - coor[4]) * inclination_2) >= x) {
							return true;
						}
					}
				}
				else if (min_y == coor[4]) {
					if (y >= coor[1]) {
						inclination_1 = (coor[0] - coor[9]) / (coor[1] - coor[10]);
						inclination_2 = (coor[3] - coor[9]) / (coor[4] - coor[10]);
						if ((coor[9] + (y - coor[10]) * inclination_1) <= x &&
							(coor[9] + (y - coor[10]) * inclination_2) >= x) {
							return true;
						}
					}
					else {
						inclination_1 = (coor[3] - coor[0]) / (coor[4] - coor[1]);
						inclination_2 = (coor[3] - coor[9]) / (coor[4] - coor[10]);
						if ((coor[0] + (y - coor[1]) * inclination_1) <= x &&
							(coor[9] + (y - coor[10]) * inclination_2) >= x) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	void move_rect(float x, float y)
	{
		coor[0] += x; coor[3] += x; coor[6] += x; coor[9] += x;
		coor[1] += y; coor[4] += y; coor[7] += y; coor[10] += y;
	}
};