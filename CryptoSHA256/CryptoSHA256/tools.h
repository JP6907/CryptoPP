#ifndef _tools
#define _tools

#include <vector>
#include <string>

class Tools {
public:

	Tools();
	~Tools();

	static void StringToByte(std::string s, int size, unsigned char *c);
	static void ByteToString(unsigned char c[], int size, std::string &s);

	static void StringToVector(std::string s, std::vector<unsigned char> &v);
	static void VectorToString(std::vector<unsigned char> &v, std::string &s);
	static void PrintByte(std::vector<unsigned char> v);

};
#endif