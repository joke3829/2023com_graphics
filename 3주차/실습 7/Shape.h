#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
class Shape {
	int kind;			// 종류
	float coor[12]{};		// 좌표
	float colors[9]{};	// 색상
	unsigned int index[6] {};
	GLuint vao, vbo[2], ebo;
public:
	Shape()		// 생성자 vao, vbo 생성
	{
		index[0] = 0; index[1] = 3; index[2] = 1;
		index[3] = 1; index[4] = 3; index[5] = 2;
	}

	void Gen()
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &ebo);
		glGenBuffers(2, vbo);
	}

	void InitBuffer()
	{
		glBindVertexArray(vao);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(coor), coor, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
	}

	void make_property(int k, float x, float y, float r, float g, float b)
	{
		kind = k;
		colors[0] = colors[3] = colors[6] = r;
		colors[1] = colors[4] = colors[7] = g;
		colors[2] = colors[5] = colors[8] = b;
		switch (k) {
		case 0:
			coor[0] = x;
			coor[1] = y;
			break;
		case 1:
			coor[0] = x - 0.1; coor[1] = y + 0.15;
			coor[3] = x + 0.1; coor[4] = y - 0.15;
			break;
		case 2:
			coor[0] = x - 0.1; coor[1] = y - 0.15;
			coor[3] = x + 0.1; coor[4] = y - 0.15;
			coor[6] = x; coor[7] = y + 0.15;
			break;
		case 3:
			coor[0] = x - 0.15; coor[1] = y - 0.15;
			coor[3] = x - 0.15; coor[4] = y + 0.15;
			coor[6] = x + 0.15; coor[7] = y + 0.15;
			coor[9] = x + 0.15; coor[10] = y - 0.15;
			break;
		}
	}

	void move(int way) 
	{
		switch (way) {
		case 0:	// w
			coor[1] += 0.1;
			coor[4] += 0.1;
			coor[7] += 0.1;;
			coor[10] += 0.1;
			break;
		case 1:	// a
			coor[0] -= 0.1;
			coor[3] -= 0.1;
			coor[6] -= 0.1;;
			coor[9] -= 0.1;
			break;
		case 2:	// s
			coor[1] -= 0.1;
			coor[4] -= 0.1;
			coor[7] -= 0.1;;
			coor[10] -= 0.1;
			break;
		case 3:	// d
			coor[0] += 0.1;
			coor[3] += 0.1;
			coor[6] += 0.1;;
			coor[9] += 0.1;
			break;
		}
	}

	void Draw()	// 출력 함수
	{
		glBindVertexArray(vao);
		switch (kind) {
		case 0:
			glPointSize(10.0);
			glDrawArrays(GL_POINTS, 0, 1);
			break;
		case 1:
			glDrawArrays(GL_LINES, 0, 2);
			break;
		case 2:
			glDrawArrays(GL_TRIANGLES, 0, 3);
			break;
		case 3:
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			break;
		}
	}
};