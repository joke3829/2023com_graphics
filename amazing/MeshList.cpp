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
	row = 0;
	col = 0;
	while (5 > row || 25 < row) {
		std::cout << "행을 입력(5~25): ";
		std::cin >> row;
		if (5 > row || 25 < row)
			std::cout << "범위가 잘못됨!" << '\n';
	}

	while (5 > col || 25 < col) {
		std::cout << "열을 입력(5~25): ";
		std::cin >> col;
		if (5 > col || 25 < col)
			std::cout << "범위가 잘못됨!" << '\n';
	}

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
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				mesh_array[i][j].anime_2();
			}
		}
		break;
	case 3:
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				mesh_array[i][j].anime_2();
			}
		}
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
	int r_mid;
	int c_mid;
	if (row % 2 == 0)
		r_mid = row / 2;
	else
		r_mid = (row / 2) + 1;

	if (col % 2 == 0)
		c_mid = col / 2;
	else
		c_mid = (col / 2) + 1;

	switch (n) {
	case 1:
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				mesh_array[i][j].ready_ani_1();
			}
		}
		break;
	case 2:
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				mesh_array[i][j].ready_ani_2(i);
			}
		}
		break;
	case 3:
		for (int i = 0; i < r_mid; ++i) {
			int q = 0;
			for (int j = 0; j < c_mid; ++j) {
				if (q < i) {
					mesh_array[i][j].ready_ani_3(q);
					mesh_array[i][col - j - 1].ready_ani_3(q);

					mesh_array[row - i - 1][j].ready_ani_3(q);
					mesh_array[row - i - 1][col - j - 1].ready_ani_3(q);
					++q;
				}
				else {
					mesh_array[i][j].ready_ani_3(i);
					mesh_array[i][col - j - 1].ready_ani_3(i);

					mesh_array[row - i - 1][j].ready_ani_3(i);
					mesh_array[row - i - 1][col - j - 1].ready_ani_3(i);
				}
			}
		}
		break;
	}
}