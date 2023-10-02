#pragma once
#define _USE_MATH_DEFINES
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include<math.h>
class Shape {
	float count_l;
	float count_r;
	float count_u;
	float count_d;
	float s_x;
	float s_y;
	float count;
	float radian;			// 원 스파이럴 용 반지름;
	bool right;				// 대각선 이동용
	bool up;				// 대각선 이동용
	bool down;
	bool left;
	bool line;
	float speed;
	float coor[9]{};		// 좌표
	float colors[9]{};	// 색상
	GLuint vao, vbo[2];
public:
	Shape(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b, float s)
	{
		right = up = true;
		line = false;
		speed = s;
		coor[0] = x1; coor[1] = y1;
		coor[3] = x2; coor[4] = y2;
		coor[6] = x3; coor[7] = y3;
		colors[0] = colors[3] = colors[6] = r;
		colors[1] = colors[4] = colors[7] = g;
		colors[2] = colors[5] = colors[8] = b;
	};
	// vao, vbo 생성
	void Gen()
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(2, vbo);
	}
	// vao, vbo 바인드
	void InitBuffer()
	{
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(coor), coor, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
	}
	// 크기 바꾸기 함수
	void change_coor(float x, float y, float w, float h) {
		coor[0] = x - 0.1; coor[1] = y - 0.15;
		coor[3] = x + 0.1; coor[4] = y - 0.15;
		coor[6] = x; coor[7] = y + 0.15;
	}

	void set_bool()
	{
		right = up = true;
		count = 0;
	}
	// 면, 선 출력 결정 함수
	void change_line(bool n)
	{
		line = n;
	}

	void Draw()	// 출력 함수
	{
		glBindVertexArray(vao);
		if (line)
			glDrawArrays(GL_LINE_LOOP, 0, 3);
		else
			glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	// 대각선 이동
	void move_1()
	{
		if (up) {
			if (right) {
				coor[0] += speed;
				coor[1] += speed;
				coor[3] += speed;
				coor[4] += speed;
				coor[6] += speed;
				coor[7] += speed;
				if (coor[3] > 1) {
					coor[3] = 1;
					coor[0] = 1;
					coor[1] = coor[4] - 0.2;
					coor[6] = coor[0] - 0.3;
					coor[7] = (coor[1] + coor[4]) / 2;
					right = false;
				}
			}
			else {
				coor[0] -= speed;
				coor[1] += speed;
				coor[3] -= speed;
				coor[4] += speed;
				coor[6] -= speed;
				coor[7] += speed;
				if (coor[3] < -1) {
					coor[3] = -1;
					coor[0] = -1;
					coor[1] = coor[4] + 0.2;
					coor[6] = coor[0] + 0.3;
					coor[7] = (coor[1] + coor[4]) / 2;
					right = true;
				}
				else if (coor[0] < -1) {
					coor[0] = coor[3] = -1;
					coor[4] = coor[1] - 0.2;
					coor[6] = coor[0] + 0.3;
					coor[7] = (coor[1] + coor[4]) / 2;
					right = true;
				}
			}
			if (coor[4] > 1) {
				coor[4] = 1;
				coor[1] = 1;
				coor[0] = coor[3] + 0.2;
				coor[6] = (coor[0] + coor[3]) / 2;
				coor[7] = coor[1] - 0.3;
				up = false;
			}
			else if (coor[1] > 1) {
				coor[1] = coor[4] = 1;
				coor[3] = coor[0] - 0.2;
				coor[6] = (coor[0] + coor[3]) / 2;
				coor[7] = coor[1] - 0.3;
				up = false;
			}
		}
		else {
			if (right) {
				coor[0] += speed;
				coor[1] -= speed;
				coor[3] += speed;
				coor[4] -= speed;
				coor[6] += speed;
				coor[7] -= speed;
				if (coor[3] < -1) {
					coor[3] = -1;
					coor[0] = -1;
					coor[1] = coor[4] + 0.2;
					coor[6] = coor[0] + 0.3;
					coor[7] = (coor[1] + coor[4]) / 2;
					right = false;
				}
				else if (coor[0] > 1) {
					coor[0] = coor[3] = 1;
					coor[4] = coor[1] + 0.2;
					coor[6] = coor[0] - 0.3;
					coor[7] = (coor[1] + coor[4]) / 2;
					right = false;
				}
			}
			else {
				coor[0] -= speed;
				coor[1] -= speed;
				coor[3] -= speed;
				coor[4] -= speed;
				coor[6] -= speed;
				coor[7] -= speed;
				if (coor[3] < -1) {
					coor[3] = -1;
					coor[0] = -1;
					coor[1] = coor[4] + 0.2;
					coor[6] = coor[0] + 0.3;
					coor[7] = (coor[1] + coor[4]) / 2;
					right = true;
				}
			}
			if (coor[4] < -1) {
				coor[4] = -1;
				coor[1] = -1;
				coor[0] = coor[3] - 0.2;
				coor[6] = (coor[0] + coor[3]) / 2;
				coor[7] = coor[1] + 0.3;
				up = true;;
			}
			else if (coor[1] < -1) {
				coor[1] = coor[4] = -1;
				coor[3] = coor[0] + 0.2;
				coor[6] = (coor[0] + coor[3]) / 2;
				coor[7] = coor[1] + 0.3;
				up = true;
			}
		}
	}
	// 좌우 지그재그
	void move_2()
	{
		if (up && right) {
			coor[0] += speed;
			coor[3] += speed;
			coor[6] += speed;
			if (coor[0] > 1 || coor[3] > 1 || coor[6] > 1) {
				coor[0] = 1;
				coor[3] = coor[0] - 0.2; coor[4] = coor[1];
				coor[6] = (coor[0] + coor[3]) / 2;
				coor[7] = coor[1] - 0.3;
				right = false;
				up = false;
			}
		}
		else if (up && !right) {
			coor[0] -= speed;
			coor[3] -= speed;
			coor[6] -= speed;
			if (coor[0] < -1 || coor[3] < -1 || coor[6] < -1) {
				coor[3] = -1;
				coor[0] = coor[3] + 0.2; coor[1] = coor[4];
				coor[6] = (coor[0] + coor[3]) / 2;
				coor[7] = coor[1] - 0.3;
				right = true;
				up = false;
			}
		}
		else if (!up) {
			coor[1] -= speed;
			coor[4] -= speed;
			coor[7] -= speed;
			if (coor[7] < -1) {
				coor[1] = coor[4] = 1;
				coor[7] = coor[1] - 0.3;
			}
			count += 1;
			if (count > 5) {
				if (right) {
					coor[0] = -1;
					coor[1] = coor[4] + 0.2;
					coor[6] = coor[0] + 0.3;
					coor[7] = (coor[1] + coor[4]) / 2;
					count = 0;
					up = true;
				}
				else {
					coor[3] = 1;
					coor[4] = coor[1] + 0.2;
					coor[6] = coor[0] - 0.3;
					coor[7] = (coor[1] + coor[4]) / 2;
					count = 0;
					up = true;
				}
			}
		}
	}
	//사각 스파이럴
	void set_count()
	{
		count_r = count_u = 1;
		count_l = count_d = -1;
		up = true; right = down = left = false;
	}
	void move_3()
	{
		if (up) {
			coor[1] += speed;
			coor[4] += speed;
			coor[7] += speed;
			if (coor[7] > count_u) {
				coor[4] = count_u;
				coor[0] = coor[3]; coor[1] = coor[4] - 0.2;
				coor[6] = coor[0] - 0.3;
				coor[7] = (coor[1] + coor[4]) / 2;
				up = false;
				left = true;
				count_u -= 0.15;
			}
		}
		else if (left) {
			coor[0] -= speed;
			coor[3] -= speed;
			coor[6] -= speed;
			if (coor[6] < count_l) {
				coor[3] = count_l;
				coor[0] = coor[3] + 0.2; coor[1] = coor[4];
				coor[6] = (coor[0] + coor[3]) / 2;
				coor[7] = coor[1] - 0.3;
				left = false;
				down = true;
				count_l += 0.15;
			}
		}
		else if (down) {
			coor[1] -= speed;
			coor[4] -= speed;
			coor[7] -= speed;
			if (coor[7] < count_d) {
				coor[4] = count_d;
				coor[0] = coor[3]; coor[1] = coor[4] + 0.2;
				coor[6] = coor[0] + 0.3;
				coor[7] = (coor[1] + coor[4]) / 2;
				down = false;
				right = true;
				count_d += 0.15;
			}
		}
		else if (right) {
			coor[0] += speed;
			coor[3] += speed;
			coor[6] += speed;
			if (coor[6] > count_r) {
				coor[3] = count_r;
				coor[0] = coor[3] - 0.2; coor[1] = coor[4];
				coor[6] = (coor[0] + coor[3]) / 2;
				coor[7] = coor[1] + 0.3;
				right = false;
				up = true;
				count_r -= 0.15;
			}
		}
	}
	// 반지름 초기화
	void set_rad(float r)
	{
		count = 0;
		radian = r;
	}
	//원 스파이럴
	void move_4()
	{
		s_x = radian * cos(M_PI + (count * (speed * 4)));
		s_y = radian * sin(M_PI + (count * (speed * 4)));
		coor[0] = s_x - 0.1; coor[1] = s_y - 0.15;
		coor[3] = s_x + 0.1; coor[4] = s_y - 0.15;
		coor[6] = s_x; coor[7] = s_y + 0.15;
		count += 1;
		radian = radian +  (speed/8);
	}
};