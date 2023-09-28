#pragma once
#include<fstream>
#include<string>

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
	return c;
}