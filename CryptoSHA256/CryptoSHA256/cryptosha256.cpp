#include "cryptosha256.h"

#include "sha.h"
#include "secblock.h"
#include "modes.h"
#include "hex.h"
#include "channels.h"
#include "filters.h"

#pragma comment(lib, "cryptlib.lib")

using namespace std;
using namespace CryptoPP;

CryptoSHA256::CryptoSHA256()
{
}

CryptoSHA256::~CryptoSHA256()
{
}

std::string CryptoSHA256::CalculateSHA256(std::string Message) {
	string s;
	SHA256 sha256;
	HashFilter f(sha256, new HexEncoder(new StringSink(s)));
	ChannelSwitch cs;
	cs.AddDefaultRoute(f);
	StringSource ss(Message, true/*pumpAll*/, new Redirector(cs));

	return s;
}
bool CryptoSHA256::VerifySHA256(std::string Digest, std::string Message) {
	//cout << "verifyint ------ " << endl;
	cout << Message << endl;
	std::string stemp = CalculateSHA256(Message);
	//cout << stemp << endl;
	//cout << Digest << endl;
	if (stemp == Digest ) {
		return true;
	}
	else {
		return false;
	}
}