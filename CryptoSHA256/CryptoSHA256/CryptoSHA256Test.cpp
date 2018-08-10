#include <iostream>
#include <string>
#include <CTIME>
#include <windows.h>

#include "tools.h"
#include "cryptosha256.h"


#pragma comment(lib, "cryptlib.lib")
using namespace std;

const int SIZE_CHAR = 10; //生成32 + 1位C Style字符串
const char CCH[] = "_  0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

std::string getRandomString() {
	string str;
	srand((unsigned)time(NULL));
	char ch[SIZE_CHAR + 1] = { 0 };
	for (int i = 0; i < SIZE_CHAR; ++i)
	{
		int x = rand() / (RAND_MAX / (sizeof(CCH) - 1));
		ch[i] = CCH[x];
		str += CCH[x];
	}
	return str;
}

int main(void)

{
	bool bIsSuccess = true;
	for (int k = 1; k <= 100 && bIsSuccess; k++) {
	//string strMessage = "Now is the time for all good men to come to the aide of their country";
		string strMessage = getRandomString();
		cout << k << ":" << strMessage << endl;

		string strDigest;

		for (int i = 0; i < 10; i++) {
			strDigest = CryptoSHA256::CalculateSHA256(strMessage);
			cout << "the size of Digest is: " << strDigest.size() << endl;
			vector<unsigned char> vchDigest1;
			Tools::StringToByte(strDigest, vchDigest1);
			cout << "Digest is:";
			Tools::PrintByte(vchDigest1);
		}

		//验证
		string m = strMessage;
		bIsSuccess = CryptoSHA256::VerifySHA256(strDigest, m);
		//通过校验，看看strDigest是否对应原来的message
		if (bIsSuccess)
		{
			cout << "verify succeed!!!!!" << endl;
			cout << "origin string is: " << strMessage << endl << endl;
		}
		else
		{
			cout << "verify fail!!!!!" << endl;
		}
		Sleep(400);
	}


	getchar();
	return 0;
}