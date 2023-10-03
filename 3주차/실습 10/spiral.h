#pragma once
#define _USE_MATH_DEFINES
#include<cmath>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>


class SPIRAL {
	float coor[300]{};			// 좌표
	float color[300]{};			// 색상
	float radian;				// 반지름
	int rotation;				// 회전 수
	GLuint vao, vbo[2];			// vao, vbo
public:
	SPIRAL()
	{
		rotation = 0;
		radian = 0;
		for (int i = 0; i < 300; i += 3) {
			color[i] = 1.0;
			color[i + 1] = 1.0;
			color[i + 2] = 1.0;
		}
	}
	// vao, vbo생성
	void Gen()
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(2, vbo);
	}
	// 버퍼 생성
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
	// 점의 위치를 지정하는 함수
	void decide_point(float x, float y)
	{
		radian = 0; rotation = 0;
		coor[0] = x; coor[1] = y;
		for (int i = 3; i < 226; i += 3) {
			if (i > 111) {
				coor[i] = (x + 0.36) + radian * cos((M_PI / 6 ) * rotation);
				coor[i + 1] = y + radian * sin((M_PI / 6 ) * rotation);
				radian -= 0.005;
				rotation--;
			}
			else {
				coor[i] = x + radian * cos((M_PI / 6) * rotation);
				coor[i + 1] = y + radian * sin((M_PI / 6) * rotation);
				radian += 0.005;
				if (i == 111)
					rotation += 29;
				else
					rotation++;
			}
		}
	}
	//출력 함수
	void Draw(bool show_type, int start, int end)
	{
		std::cout << coor[111] - coor[0] << std::endl;
		glBindVertexArray(vao);
		if (show_type) {
			glDrawArrays(GL_LINE_STRIP, start, end);
		}
		else {
			glPointSize(5);
			glDrawArrays(GL_POINTS, start, end);
		}
	}
};