#include "Crypter.h"

using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::FileSource;
using CryptoPP::FileSink;
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;
using CryptoPP::DefaultDecryptorWithMAC;
using CryptoPP::DefaultEncryptorWithMAC;


Crypter::Crypter()
{
	this->password = "pvx124";
	this->fileName = "./saves.txt";
	this->decrypted = "";
	this->encrypted = "";
	fileManager = new FileManager();
	encrypt();
}

std::string Crypter::openFile()
{

	fileManager->Open(fileName, 0);
	encrypt();
//	decript();
	return encrypted;
}

void Crypter::encrypt()
{
	FileSource fileSource1("./saves.txt", true,
		new DefaultEncryptorWithMAC(
			(byte*)this->password.data(), this->password.size(),
				new HexEncoder(
					new StringSink(this->encrypted)
				)
			)
		);

	fileManager->writeToFile(encrypted);



}

void Crypter::decript()
{
	FileSource fileSource2("./saves.txt", true,
			new HexDecoder(
				new DefaultDecryptorWithMAC(
					(byte*)this->password.data(), this->password.size(),
					new StringSink(decrypted)
				)
			)
		);
	fileManager->writeToFile(decrypted);
}

Crypter::~Crypter()
{
	
}