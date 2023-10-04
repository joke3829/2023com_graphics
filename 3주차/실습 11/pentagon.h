#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>

class PENTAGON {
	float coor[15]{};			// 좌표
	float colors[15]{};		// 색상 속성
	unsigned int index[9];
	float line_color[9]{};
	int count;				// 15번만에 변화시켜라
	GLuint vao[2], vbo[4], ebo;
public:
	PENTAGON()
	{
		count = 0;
		index[0] = 0; index[1] = 3; index[2] = 4;
		index[3] = 0; index[4] = 1; index[5] = 3;
		index[6] = 1; index[7] = 2; index[8] = 3;
		coor[0] = -0.9; coor[1] = -0.9;
		coor[3] = -0.1; coor[4] = -0.9;
		coor[6] = -0.1; coor[7] = -0.1;
		coor[9] = -0.5; coor[10] = -0.1;
		coor[12] = -0.9; coor[13] = -0.1;
		colors[1] = colors[4] = colors[7] = colors[10] = colors[13] = 1.0;
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
		glDrawArrays(GL_LINE_LOOP, 0, 5);

		glLineWidth(1);
		glBindVertexArray(vao[0]);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	}
	// 애니메이션 함수
	void transform(int w_display)
	{
		switch (w_display) {
		case 3:
			coor[0] += (0.5) / 15;
			coor[3] -= (0.5) / 15;
			coor[7] -= (0.7) / 15;
			coor[13] -= (0.7) / 15;
			count++;
			if (count > 15) {
				count = 0;
				coor[0] = -0.9; coor[1] = -0.9;
				coor[3] = 0.9; coor[4] = -0.9;
				coor[6] = 0.9; coor[7] = 0.9;
				coor[9] = 0; coor[10] = 0.9;
				coor[12] = -0.9; coor[13] = 0.9;
			}
			break;
		case 5:
			coor[0] += (0.9 - 0.7) / 15;
			coor[3] -= (0.9 - 0.7) / 15;
			coor[7] -= (0.4 - 0.1) / 15;
			coor[13] -= (0.4 - 0.1) / 15;
			count++;
			if (count > 15) {
				count = 0;
				coor[0] = -0.9; coor[1] = -0.9;
				coor[3] = -0.1; coor[4] = -0.9;
				coor[6] = -0.1; coor[7] = -0.1;
				coor[9] = -0.5; coor[10] = -0.1;
				coor[12] = -0.9; coor[13] = -0.1;
			}
			break;
		}
	}

	void initial(int w_display) {
		count = 0;
		switch (w_display) {
		case 3:
			coor[0] = -0.9; coor[1] = -0.9;
			coor[3] = 0.9; coor[4] = -0.9;
			coor[6] = 0.9; coor[7] = 0.9;
			coor[9] = 0; coor[10] = 0.9;
			coor[12] = -0.9; coor[13] = 0.9;
			break;
		case 5:
			coor[0] = -0.9; coor[1] = -0.9;
			coor[3] = -0.1; coor[4] = -0.9;
			coor[6] = -0.1; coor[7] = -0.1;
			coor[9] = -0.5; coor[10] = -0.1;
			coor[12] = -0.9; coor[13] = -0.1;
			break;
		}
	}
};