#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>

class Shape {
	float center[2];					// 0 = x, 1 = y 합성 범위는 0.2 * 0.2
	float coor[15];
	float color[15];
	bool right, up;
	unsigned int index[9];
	int number_of_vertex;				// 꼭짓점 수
	bool merge_state;					// 합쳤는지 판단 여부
	GLuint VAO, VBO[2], EBO;
public:
	// 생성자 꼭짓점 수, x센터, y센터, rgb
	Shape(int nov, float x, float y, float r, float g, float b)
	{
		right = up = true;
		merge_state = false;
		center[0] = x; center[1] = y;
		for (int i = 0; i < 15; i += 3) {
			color[i] = r;
			color[i + 1] = g;
			color[i + 2] = b;
		}
		number_of_vertex = nov;
		index[0] = 0; index[1] = 1; index[2] = 3;
		index[3] = 1; index[4] = 2; index[5] = 3;
		index[6] = 0; index[7] = 3; index[8] = 4;
	}
	// 버퍼 생성
	void Gen()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(2, VBO);
		glGenBuffers(1, &EBO);
	}
	// 버퍼 업데이트
	void InitBuffer()
	{
		switch (number_of_vertex) {
		case 0:
			number_of_vertex = 5;
			coor[0] = center[0] - 0.05; coor[1] = center[1] - 0.1;
			coor[3] = center[0] + 0.05; coor[4] = center[1] - 0.1;
			coor[6] = center[0] + 0.1; coor[7] = center[1] + 0.02;
			coor[9] = center[0]; coor[10] = center[1] + 0.1;
			coor[12] = center[0] - 0.1; coor[13] = center[1] + 0.02;
			break;
		case 1:
			coor[0] = center[0];
			coor[1] = center[1];
			break;
		case 2:
			coor[0] = center[0] - 0.1; coor[1] = center[1] + 0.1;
			coor[3] = center[0] + 0.1; coor[4] = center[1] - 0.1;
			break;
		case 3:
			coor[0] = center[0] - 0.1; coor[1] = center[1] - 0.1;
			coor[3] = center[0] + 0.1; coor[4] = center[1] - 0.1;
			coor[6] = center[0]; coor[7] = center[1] + 0.1;
			break;
		case 4:
			coor[0] = center[0] - 0.1; coor[1] = center[1] - 0.1;
			coor[3] = center[0] + 0.1; coor[4] = center[1] - 0.1;
			coor[6] = center[0] + 0.1; coor[7] = center[1] + 0.1;
			coor[9] = center[0] - 0.1; coor[10] = center[1] + 0.1;
			break;
		case 5:
			coor[0] = center[0] - 0.05; coor[1] = center[1] - 0.1;
			coor[3] = center[0] + 0.05; coor[4] = center[1] - 0.1;
			coor[6] = center[0] + 0.1; coor[7] = center[1] + 0.02;
			coor[9] = center[0]; coor[10] = center[1] + 0.1;
			coor[12] = center[0] - 0.1; coor[13] = center[1] + 0.02;
			break;
		}
		glBindVertexArray(VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(coor), coor, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
	}
	// 그리기 함수
	void Draw()
	{
		InitBuffer();
		switch (number_of_vertex) {
		case 1:
			glPointSize(10);
			glDrawArrays(GL_POINTS, 0, 1);
			break;
		case 2:
			glDrawArrays(GL_LINES, 0, 2);
			break;
		case 3:
			glDrawArrays(GL_TRIANGLES, 0, 3);
			break;
		case 4:
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			break;
		case 5:
			glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
			break;
		}
	}
	// 합성 함수
	void merge_shape(Shape& merged_shape)
	{
		number_of_vertex = (number_of_vertex + merged_shape.number_of_vertex) % 5;
		merge_state = true;
		merged_shape.center[0] = merged_shape.center[1] = -100;
		merged_shape.merge_state = false;
	}
	// 대각선 이동 애니메이션
	void move()
	{
		if (merge_state) {
			if (up) {
				if (right) {
					center[0] += 0.01;
					if (center[0] + 0.1 >= 1)
						right = false;
				}
				else {
					center[0] -= 0.01;
					if (center[0] - 0.1 <= -1)
						right = true;;
				}
				center[1] += 0.01;
				if (center[1] + 0.1 >= 1)
					up = false;
			}
			else {
				if (right) {
					center[0] += 0.01;
					if (center[0] + 0.1 >= 1)
						right = false;
				}
				else {
					center[0] -= 0.01;
					if (center[0] - 0.1 <= -1)
						right = true;;
				}
				center[1] -= 0.01;
				if (center[1] - 0.1 <= -1)
					up = true;
			}
		}
	}
	// 이 도형을 잡았는가?
	bool check_grab(float x, float y)
	{
		if (x >= center[0] - 0.1 && x <= center[0] + 0.1 &&
			y >= center[1] - 0.1 && y <= center[1] + 0.1) {
			return true;
		}
		return false;
	}
	// 마우스 이동 시 도형 이동
	void move_mouse(float x, float y)
	{
		center[0] = x;
		center[1] = y;
	}
};