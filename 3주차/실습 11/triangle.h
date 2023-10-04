#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>

class TRIANGLE {
	float coor[9]{};			// 좌표
	float colors[9]{};		// 색상 속성
	float line_color[9]{};
	int count;				// 6번만에 변화시켜라
	GLuint vao[2], vbo[4];
public:
	TRIANGLE()
	{
		count = 0;
		coor[0] = -0.9; coor[1] = 0.3;
		coor[3] = -0.1; coor[4] = 0.9;
		coor[6] = -0.5; coor[7] = 0.6;
		colors[2] = colors[5] = colors[8] = 1.0;
	}
	//vao vbo제너레이트
	void Gen()
	{
		glGenVertexArrays(2, vao);
		glGenBuffers(4, vbo);
	}
	// 버퍼 설정 
	void InitBuffer()
	{
		glBindVertexArray(vao[0]);
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
		glDrawArrays(GL_LINE_LOOP, 0, 3);

		glLineWidth(1);
		glBindVertexArray(vao[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	// 애니메이션 함수
	void transform(int w_display)
	{
		switch(w_display){
		case 1:
			coor[4] -= (1.8) / 15;
			coor[7] += (0.9) / 15;
			count++;
			if (count > 15) {
				count = 0;
				coor[0] = -0.9; coor[1] = -0.9;
				coor[3] = 0.9; coor[4] = 0.9;
				coor[6] = 0; coor[7] = 0;
			}
			break;
		case 5:
			coor[1] -= (0.3 - 0.1) / 15;
			coor[4] -= (0.9 - 0.1) / 15;
			coor[7] += (0.9 - 0.6) / 15;
			count++;
			if (count > 15) {
				count = 0;
				coor[0] = -0.9; coor[1] = 0.3;
				coor[3] = -0.1; coor[4] = 0.9;
				coor[6] = -0.5; coor[7] = 0.6;
			}
			break;
		}
	}
	void initial(int w_display) {
		count = 0;
		switch (w_display) {
		case 1:
			coor[0] = -0.9; coor[1] = -0.9;
			coor[3] = 0.9; coor[4] = 0.9;
			coor[6] = 0; coor[7] = 0;
			break;
		case 5:
			coor[0] = -0.9; coor[1] = 0.3;
			coor[3] = -0.1; coor[4] = 0.9;
			coor[6] = -0.5; coor[7] = 0.6;
			break;
		}
	}
};