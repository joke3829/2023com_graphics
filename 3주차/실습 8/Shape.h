#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
class Shape {
	bool line;
	float coor[9]{};		// 좌표
	float colors[9]{};	// 색상
	GLuint vao, vbo[2];
public:
	Shape(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)
	{
		line = false;
		coor[0] = x1; coor[1] = y1;
		coor[3] = x2; coor[4] = y2;
		coor[6] = x3; coor[7] = y3;
		colors[0] = colors[3] = colors[6] = r;
		colors[1] = colors[4] = colors[7] = g;
		colors[2] = colors[5] = colors[8] = b;
	};
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
	}

	void change_coor(float x, float y, float w, float h) {
		coor[0] = x - w; coor[1] = y - h;
		coor[3] = x + w; coor[4] = y - h;
		coor[6] = x; coor[7] = y + h;
	}

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
};