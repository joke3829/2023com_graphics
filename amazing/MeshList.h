#pragma once
#include "Mesh.h"

class MeshList {
public:
	MeshList();
	~MeshList();

	void setRC();
	void delete_RC();
	void RC_init();

	void mesh_ani();

	void setAS(int);

	void Render() const;

private:
	int row, col;
	Mesh** mesh_array;
	int ani_state;			// 몇번째 애니메이션?
};