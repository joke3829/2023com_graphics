//================================================================================================
// Floor.h
// Mesh 큐브들을 이용해 바닥을 만드는 헤더
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