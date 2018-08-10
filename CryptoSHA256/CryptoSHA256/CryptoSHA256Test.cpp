#include <iostream>
#include <string>
#include <CTIME>
#include <windows.h>

#include "tools.h"
#include "cryptosha256.h"

#include "sha.h"
#include "channels.h"
#include "filters.h"
#include "hex.h"

#pragma comment(lib, "cryptlib.lib")
using namespace std;
using namespace CryptoPP;

const int SIZE_CHAR = 40; //生成32 + 1位C Style字符串
const char CCH[] = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

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
	/*bool bIsSuccess = true;
	for (int k = 1; k <= 100 && bIsSuccess; k++) {*/
	string strMessage = "Now is the time for all good men to come to the aide of their country";
		//string strMessage = getRandomString();
		//cout << k << ":" << strMessage << endl;
		strMessage.insert(0, "0xa0");

		string m;
		for (int i = 0; i < strMessage.size(); i++) {
			m += strMessage.at(i);
		}

		string strDigest;

		for (int i = 0; i < 10; i++) {
			strDigest = CryptoSHA256::CalculateDigest(strMessage);
			cout << "the size of Digest is: " << strDigest.size() << endl;
			vector<unsigned char> vchDigest1;
			Tools::StringToByte(strDigest, vchDigest1);
			cout << "Digest is:";
			Tools::PrintByte(vchDigest1);
		}

	//	//验证

	//	bIsSuccess = CryptoSHA256::VerifyDigest(strDigest, m);
	//	//通过校验，看看strDigest是否对应原来的message
	//	if (bIsSuccess)
	//	{
	//		cout << "verify succeed!" << endl;
	//		cout << "origin string is: " << strMessage << endl << endl;
	//	}
	//	else
	//	{
	//		cout << "verify fail!" << endl;
	//	}
	//	Sleep(400);
	//}

	//string message = "Now is the time for all good men to come to the aide of their country";
	string message = getRandomString();
	string s1, s2, s3, s4;
	SHA1 sha1; SHA224 sha224; SHA256 sha256; SHA512 sha512;
	HashFilter f1(sha1, new HexEncoder(new StringSink(s1)));
	HashFilter f2(sha224, new HexEncoder(new StringSink(s2)));
	HashFilter f3(sha256, new HexEncoder(new StringSink(s3)));
	HashFilter f4(sha512, new HexEncoder(new StringSink(s4)));
	ChannelSwitch cs;
	cs.AddDefaultRoute(f1);
	cs.AddDefaultRoute(f2);
	cs.AddDefaultRoute(f3);
	cs.AddDefaultRoute(f4);
	StringSource ss(message, true/*pumpAll*/, new Redirector(cs));
	cout << "Message:" <<message <<endl;
		cout << "SHA-1:" << s1 << endl;
	cout << "SHA-224:" << s2 << endl;
	cout << "SHA-256:" << s3 << endl;
	cout << "SHA-256 length:" << s3.size() << endl;
	cout << "SHA-512:" << s4 << endl;

	getchar();
	return 0;
}