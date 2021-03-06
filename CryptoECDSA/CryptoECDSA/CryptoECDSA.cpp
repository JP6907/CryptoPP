// g++ -g3 -ggdb -O0 -DDEBUG -Wall -Wextra cryptopp-test.cpp -o cryptopp-test.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -Wall -Wextra cryptopp-test.cpp -o cryptopp-test.exe -lcryptopp -lpthread

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;


#include <stdexcept>
using std::runtime_error;

#include <cstdlib>
using std::exit;

#include "osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "eccrypto.h"
using CryptoPP::ECP;
using CryptoPP::ECDSA;

#include "sha.h"
using CryptoPP::SHA1;

#include "queue.h"
using CryptoPP::ByteQueue;

#include "oids.h"
using CryptoPP::OID;

// ASN1 is a namespace, not an object
#include "asn.h"
using namespace CryptoPP::ASN1;

#include "integer.h"
using CryptoPP::Integer;

#pragma comment(lib, "cryptlib.lib" )  

 static const unsigned int s_maxAutoNodeSize = 16*1024;

typedef unsigned char byte;

int main(int, char**) {

	AutoSeededRandomPool prng;
	ByteQueue privateKey, publicKey;

	string message = "Do or do not. There is no try.";

	//////////////////////////////////////////////////////

	// Generate private key
	ECDSA<ECP, SHA1>::PrivateKey privKey;
	privKey.Initialize(prng, secp160r1());
	privKey.Save(privateKey);
	
	//打印私钥
	//byte *privkeybyte = (unsigned char*)(malloc(s_maxAutoNodeSize*sizeof(unsigned char)));
	//privateKey.Get(privkeybyte, s_maxAutoNodeSize);
	//cout << privKey. << endl;
	//cout << privkeybyte
	//cout << "privkeybyte" << privkeybyte << endl;

	// Create public key
	ECDSA<ECP, SHA1>::PublicKey pubKey;
	privKey.MakePublicKey(pubKey);
	pubKey.Save(publicKey);

	//////////////////////////////////////////////////////    

	// Load private key (in ByteQueue, PKCS#8 format)
	ECDSA<ECP, SHA1>::Signer signer(privateKey);

	// Determine maximum size, allocate a string with that size
	size_t siglen = signer.MaxSignatureLength();
	string signature(siglen, 0x00);

	// Sign, and trim signature to actual size
	siglen = signer.SignMessage(prng, (const byte*)message.data(), message.size(), (byte*)signature.data());
	signature.resize(siglen);

	//////////////////////////////////////////////////////    

	// Load public key (in ByteQueue, X509 format)
	ECDSA<ECP, SHA1>::Verifier verifier(publicKey);

	bool result = verifier.VerifyMessage((const byte*)message.data(), message.size(), (const byte*)signature.data(), signature.size());
	if (result)
		cout << "Verified signature on message succeed!" << endl;
	else
		cerr << "Failed to verify signature on message!" << endl;

	getchar();
	return 0;
}
