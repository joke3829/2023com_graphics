#ifndef MOUSE
#define MOUSE
// ������ ���콺��ǥ�� gl ��ǥ�� ��ȯ���ִ� �Լ� ���
#pragma once

// ������ x��ǥ�� gl��ǥ�� �ٲ��ִ� �Լ�
float x_conversion(int x, int w)
{
	return (static_cast<float>(x) - (w / 2)) / (w / 2);
}

// ������ y��ǥ�� gl��ǥ�� �ٲ��ִ� �Լ�
float y_conversion(int y, int h)
{
	return ((static_cast<float>(y) * -1) + (h / 2)) / (h / 2);
}

#endif