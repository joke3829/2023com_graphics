#pragma once
#include"stdafx.h"

// 파일을 읽고 GLchar* 문자열을 전달해주는 함수
char* filetobuf(std::string file)
{
	static std::string buf = "";
	buf = "";
	std::ifstream fin(file);
	fin >> std::noskipws;
	char a;
	while (fin >> a) {
		buf += a;
	}
	char* c = const_cast<char*>(buf.c_str());
	std::cout << c << std::endl;
	return c;
}