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
	//for (int k = 1; k <= 100 && bIsSuccess; k++) {
	//string strMessage = "Now is the time for all good men to come to the aide of their country";
		string strMessage = getRandomString();
		cout << "加密的数据：" << strMessage << endl;

		string strDigest;

		strDigest = CryptoSHA256::CalculateSHA256(strMessage);
		cout << "SHA256后的结果：" << strDigest << endl;
		cout << "SHA256后长度：" << strDigest.size() << endl;

		//验证
		string m = strMessage;
		//m = "saas";
		bIsSuccess = CryptoSHA256::VerifySHA256(strDigest, m);
		//通过校验，看看strDigest是否对应原来的message
		if (bIsSuccess)
		{
			cout << "验证成功！" << endl;
			cout << "原始数据为：" << strMessage << endl << endl;
		}
		else
		{
			cout << "验证失败！" << endl;
		}
		
		//Sleep(400);
	//}


	getchar();
	return 0;
}