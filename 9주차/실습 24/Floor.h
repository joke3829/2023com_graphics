//================================================================================================
// Floor.h
// Mesh ť����� �̿��� �ٴ��� ����� ���
//================================================================================================

#include "Wall.h"

class Floor {
public:
	void Draw();
	void Initialize(GLuint*);
	Mesh getMesh(int, int);
protected:
private:
	Mesh Cube[10][10];
	GLuint* shader;
};