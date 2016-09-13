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
	this->password = "pvxWty782qw";
	this->fileName = "./saves.txt";
	fileManager = new FileManager();
	fileManager->Open(fileName, 1);
}

std::string Crypter::readFile()
{
	fileManager->Close();
	fileManager->Open(fileName, 0);
	encrypted = fileManager->GetStringFromFile(); 
	decrypted = "";
	if (encrypted == "")
	{
		return decrypted;
	}
	decrypt();
	fileManager->clearFile();
	fileManager->Open(fileName, 1);
	writeToFile(decrypted);
	return decrypted;
}

void Crypter::writeToFile(std::string& toEncrypt)
{
	encrypted = "";
	encrypt(toEncrypt);
	fileManager->writeToFile(encrypted);
	encrypted = "";
}

void Crypter::encrypt(std::string& toEncrypt)
{
	StringSource ss1(toEncrypt, true,
		new DefaultEncryptorWithMAC(
			(byte*)password.data(), password.size(),
				new HexEncoder(
				new StringSink(encrypted)
			)
		)
	);

}

void Crypter::decrypt()
{
	StringSource ss1(encrypted, true,
		new HexDecoder(
			new DefaultDecryptorWithMAC(
				(byte*)password.data(), password.size(),
				new StringSink(decrypted)
			)
		)
	);

}

Crypter::~Crypter()
{
	
}