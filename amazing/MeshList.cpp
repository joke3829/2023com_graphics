#include "MeshList.h"

MeshList::MeshList()
{
	setRC();
	RC_init();
}

MeshList::~MeshList()
{
	delete_RC();
}

void MeshList::setRC()
{
	std::cout << "행을 입력: ";
	std::cin >> row;

	std::cout << "열을 입력: ";
	std::cin >> col;

	ani_state = 1;
	mesh_array = new Mesh * [row];
	for (int i = 0; i < row; ++i) {
		mesh_array[i] = new Mesh[col];
	}
}

void MeshList::delete_RC()
{
	for (int i = 0; i < row; ++i) {
		delete[] mesh_array[i];
	}
	delete mesh_array;
}

void MeshList::RC_init()
{
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			mesh_array[i][j].Initialize("cube.obj");
			mesh_array[i][j].init_scale(0.1);
			mesh_array[i][j].init_position(i, 0.5, j);
		}
	}
}

void MeshList::mesh_ani()
{
	switch (ani_state) {
	case 1:
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				mesh_array[i][j].anime_1();
			}
		}
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

void MeshList::Render() const
{
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			mesh_array[i][j].Render();
		}
	}
}

void MeshList::setAS(int n)
{
	ani_state = n;
	switch (n) {
	case 1:
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				mesh_array[i][j].ready_ani_1();
			}
		}
		break;
	case 2:
		break;
	case 3:
		break;
	}
}