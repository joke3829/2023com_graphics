#include "Floor.h"

void Floor::Initialize(GLuint* shaderProgram)
{
	shader = shaderProgram;
	int color = 0;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			Cube[i][j].Initialize(shader, "cube.obj", color);
			Cube[i][j].init_scale(0.2);
			if (1 == i && 7 == j) {
				Cube[i][j].change_drop(1);		// 0 = 끝까지 1 = 바닥까지
				Cube[i][j].Move(glm::vec3((9 - j) - j, 1, (9 - i) - i));
			}
			else if (2 == i && 1 == j) {
				Cube[i][j].change_drop(1);		// 0 = 끝까지 1 = 바닥까지
				Cube[i][j].Move(glm::vec3((9 - j) - j, 1, (9 - i) - i));
			}
			else if (3 == i && 3 == j) {
				Cube[i][j].change_drop(0);		// 0 = 끝까지 1 = 바닥까지
				Cube[i][j].Move(glm::vec3((9 - j) - j, 1, (9 - i) - i));
			}
			else if (5 == i && 8 == j) {
				Cube[i][j].change_drop(0);		// 0 = 끝까지 1 = 바닥까지
				Cube[i][j].Move(glm::vec3((9 - j) - j, 1, (9 - i) - i));
			}
			else if (6 == i && 2 == j) {
				Cube[i][j].change_drop(1);		// 0 = 끝까지 1 = 바닥까지
				Cube[i][j].Move(glm::vec3((9 - j) - j, 1, (9 - i) - i));
			}
			else if (8 == i && 3 == j) {
				Cube[i][j].change_drop(0);		// 0 = 끝까지 1 = 바닥까지
				Cube[i][j].Move(glm::vec3((9 - j) - j, 1, (9 - i) - i));
			}
			else
				Cube[i][j].Move(glm::vec3((9 - j) - j, -1, (9 - i) - i));
			if (9 != j) {
				if (0 == color)
					color++;
				else
					color--;
			}
		}
	}
}

void Floor::Draw()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; ++j) {
			Cube[i][j].Draw();
		}
	}
}

Mesh Floor::getMesh(int i, int j)
{
	return Cube[i][j];
}