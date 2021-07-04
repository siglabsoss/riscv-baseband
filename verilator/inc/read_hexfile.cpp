#include "read_hexfile.hpp"

#include <iostream>
#include <algorithm>
#include <assert.h>


using namespace std;

void eex(std::string path) {
	cout << "got: " << path << endl;
}



uint32_t _hti(char c) {
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	return c - '0';
}

uint32_t _hToI(char *c, uint32_t size) {
	uint32_t value = 0;
	for (uint32_t i = 0; i < size; i++) {
		value += _hti(c[i]) << ((size - i - 1) * 4);
	}
	return value;
}

void get_hexfile_as_uint8_t(std::vector<uint8_t> &buf, std::string path) {
	FILE *fp = fopen(path.c_str(), "r");
	assert(fp != 0);
	// if(fp == 0){
	// 	cout << path << " not found" << endl;
	// 	return;
	// }

	cout << "Opened .hex file " << path << endl;

	// for now
	assert(buf.size() == 0);
	// buf.resize(128);


	fseek(fp, 0, SEEK_END);
	uint32_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* content = new char[size];
	fread(content, 1, size, fp);

	int offset = 0;
	char* line = content;
	uint32_t calc, newsize;
	while (1) {
		if (line[0] == ':') {
			uint32_t byteCount = _hToI(line + 1, 2);
			uint32_t nextAddr = _hToI(line + 3, 4) + offset;
			uint32_t key = _hToI(line + 7, 2);
			// printf("%d %d %d\n", byteCount, nextAddr,key);
			switch (key) {
			case 0:
				for (uint32_t i = 0; i < byteCount; i++) {
					calc = nextAddr + i;

					newsize = max((uint32_t)buf.size(), calc+1);

					buf.resize(newsize, (uint8_t)0); // this allows the vector to always be big enough
					buf[calc] = _hToI(line + 9 + i * 2, 2);
					// cout << "calc " << calc << endl;

					// printf("  %x %x %c%c\n",nextAddr + i,_hToI(line + 9 + i*2,2),line[9 + i * 2],line[9 + i * 2+1]);
				}
				break;
			case 2:
//				cout << offset << endl;
				offset = _hToI(line + 9, 4) << 4;
				break;
			case 4:
//				cout << offset << endl;
				offset = _hToI(line + 9, 4) << 16;
				break;
			default:
//				cout << "??? " << key << endl;
				break;
			}
		}

		while (*line != '\n' && size != 0) {
			line++;
			size--;
		}
		if (size <= 1)
			break;
		line++;
		size--;
	}

	delete content;
}