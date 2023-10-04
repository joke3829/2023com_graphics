#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>

class SQUARE {
	float coor[12]{};			// 좌표
	float colors[12]{};		// 색상 속성
	unsigned int index[6];
	float line_color[9]{};
	int count;				// 15번만에 변화시켜라
	GLuint vao[2], vbo[4], ebo;
public:
	SQUARE()
	{
		count = 0;
		index[0] = 0; index[1] = 1; index[2] = 3;
		index[3] = 1; index[4] = 3; index[5] = 2;
		coor[0] = 0.1; coor[1] = 0.1;
		coor[3] = 0.9; coor[4] = 0.1;
		coor[6] = 0.5; coor[7] = 0.7;
		coor[9] = 0.5; coor[10] = 0.7;
		colors[0] = colors[3] = colors[6] = colors[9] = 1.0;
		colors[1] = colors[4] = colors[7] = colors[10] = 1.0;
	}
	//vao vbo제너레이트
	void Gen()
	{
		glGenVertexArrays(2, vao);
		glGenBuffers(4, vbo);
		glGenBuffers(1, &ebo);
	}
	// 버퍼 설정 
	void InitBuffer()
	{
		glBindVertexArray(vao[0]);
		
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

		glBindVertexArray(vao[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(coor), coor, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(line_color), line_color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
	}
	// 그리기 함수
	void Draw()
	{
		glBindVertexArray(vao[1]);
		glLineWidth(10);
		glDrawArrays(GL_LINE_LOOP, 0, 4);

		glLineWidth(1);
		glBindVertexArray(vao[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	// 애니메이션 함수
	void transform(int w_display)
	{
		switch (w_display) {
		case 2:
			coor[6] += (0.9) / 15;
			coor[9] -= (0.9) / 15;
			count++;
			if (count > 15) {
				count = 0;
				coor[0] = -0.9; coor[1] = -0.9;
				coor[3] = 0.9; coor[4] = -0.9;
				coor[6] = 0; coor[7] = 0.7;
				coor[9] = 0; coor[10] = 0.7;
			}
			break;
		case 5:
			coor[6] += (0.5 - 0.1) / 15;
			coor[9] -= (0.9 - 0.5) / 15;
			count++;
			if (count > 15) {
				count = 0;
				coor[0] = 0.1; coor[1] = 0.1;
				coor[3] = 0.9; coor[4] = 0.1;
				coor[6] = 0.5; coor[7] = 0.7;
				coor[9] = 0.5; coor[10] = 0.7;
			}
			break;
		}
	}

	void initial(int w_display) {
		count = 0;
		switch (w_display) {
		case 2:
			coor[0] = -0.9; coor[1] = -0.9;
			coor[3] = 0.9; coor[4] = -0.9;
			coor[6] = 0; coor[7] = 0.7;
			coor[9] = 0; coor[10] = 0.7;
			break;
		case 5:
			coor[0] = 0.1; coor[1] = 0.1;
			coor[3] = 0.9; coor[4] = 0.1;
			coor[6] = 0.5; coor[7] = 0.7;
			coor[9] = 0.5; coor[10] = 0.7;
			break;
		}
	}
};