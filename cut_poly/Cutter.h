#include "stdafx.h"

class Cutter {
public:
	void initialize(GLuint*);
	void Draw();
	void BufferUpdate();
	void startPos(float, float);
	void endPos(float, float);
private:
	GLuint VAO, VBO[2];
	GLuint* shader;
	float coor[6]{};
	float color[6]{};

	glm::mat4 modelTrans;
};