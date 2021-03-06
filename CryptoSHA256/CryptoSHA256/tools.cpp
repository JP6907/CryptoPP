#include "tools.h"
#include <sstream>

Tools::Tools()
{
}

Tools::~Tools()
{
}
//4,1,125,99,62
//4 1 7d 63 3e
void Tools::StringToVector(std::string s, std::vector<unsigned char> &v) {
	for (int i = 0; i<s.length(); i += 2) {
		char ch1 = s[i];
		char ch2 = s[i + 1];
		int int1, int2;
		if (ch1 >= 'a') {
			int1 = ch1 - 'a' + 10;
		}
		else {
			int1 = ch1 - '0';
		}
		if (ch2 >= 'a') {
			int2 = ch2 - 'a' + 10;
		}
		else {
			int2 = ch2 - '0';
		}
		unsigned char c = int1 * 16 + int2;
		v.push_back((unsigned char)c);
	}
}

//4,1,125,99,62
//4 1 7d 63 3e
//注意长度 为 string长度的一半
void Tools::StringToByte(std::string s, int size, unsigned char *c) {
	int index = 0;
	for (int i = 0; i<s.length(); i += 2) {
		char ch1 = s[i];
		char ch2 = s[i + 1];
		int int1, int2;
		if (ch1 >= 'a') {
			int1 = ch1 - 'a' + 10;
		}
		else {
			int1 = ch1 - '0';
		}
		if (ch2 >= 'a') {
			int2 = ch2 - 'a' + 10;
		}
		else {
			int2 = ch2 - '0';
		}
		unsigned char c0 = int1 * 16 + int2;
		c[index++] = c0;
	}
}
void Tools::ByteToString(unsigned char c[], int size, std::string &s) {
	for (int i = 0; i < size; i++) {
		int c0 = c[i];
		int c1 = (c0 / 16);
		int c2 = c0 % 16;
		char temp;
		if (c1 >= 10) {
			temp = (char)(c1 - 10 + 'a');
		}
		else {
			temp = (char)(c1 + '0');
		}
		s += temp;
		if (c2 >= 10) {
			temp = (char)(c2 - 10 + 'a');
		}
		else {
			temp = (char)(c2 + '0');
		}
		s += temp;
	}
}

void Tools::VectorToString(std::vector<unsigned char> &v, std::string &s) {
	for (int i = 0; i < v.size(); i++) {
		int c = v[i];
		int c1 = (c / 16);
		int c2 = c % 16;
		char temp;
		if (c1 >= 10) {
			temp = (char)(c1 - 10 + 'a');
		}
		else {
			temp = (char)(c1 + '0');
		}
		s += temp;
		if (c2 >= 10) {
			temp = (char)(c2 - 10 + 'a');
		}
		else {
			temp = (char)(c2 + '0');
		}
		s += temp;
	}
}

void Tools::PrintByte(std::vector<unsigned char> v) {
	for (int i = 0; i < v.size(); i++) {
		printf("%02x", v[i]);
	}
	printf("\n");
}
