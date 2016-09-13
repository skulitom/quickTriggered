#include "Files.h"

FileManager::FileManager(){}

FileManager::FileManager(std::string& fileName)
{

	this->FileName = fileName;

}

FileManager::~FileManager()
{

	this->Close();

}

void FileManager::Open(std::string& fileName, char FM_FILE_READ_OR_WRITE)
{
	this->FileName = fileName;
	if (FM_FILE_READ_OR_WRITE == FM_FILE_READ)
		this->FILE.open(fileName, std::ios_base::in);
	else
		this->FILE.open(fileName, std::ios_base::out);



}

void FileManager::Open(char FM_FILE_READ_OR_WRITE)
{

	FileManager::Open(this->FileName, FM_FILE_READ_OR_WRITE);
	// TODO exception when no FileName
	
}

void FileManager::clearFile()
{
	this->FILE.close();
	this->FILE.open(FileName.c_str(), std::fstream::out | std::fstream::trunc);
	this->FILE.close();
}

void FileManager::Close()
{

	this->FILE.close();

}

void FileManager::writeToFileAt(int num, int loc){
	this->FILE.seekg(loc);
	writeToFile(num);
	this->FILE.seekg(0);
}

void FileManager::writeToFileAt(std::string& name, int loc){
	this->FILE.seekg(loc);
	writeToFile(name);
	this->FILE.seekg(0);

}


std::string& FileManager::GetStringFromFile()
{

	std::getline(this->FILE, this->CString);
	return this->CString;

}

int FileManager::FindString(std::string findName){
	this->FILE.seekg(0);
	int lineNumber = 0;
	
	while (!this->FILE.eof()){
		std::getline(this->FILE, this->CString);
		if (this->CString==findName){
			break;
		}
		lineNumber++;
	}
	if (this->CString != findName){
		lineNumber = -1;
	}
	this->FILE.seekg(0);
	return lineNumber;

}

int FileManager::getIntFromLine(int lineNum){
	this->FILE.seekg(lineNum);
	int num = GetINTFromFile();
	this->FILE.seekg(0);
	return num;
}

int FileManager::getLineQuo(){
	this->FILE.seekg(0);
	int lineNumber = 0;

	while (!this->FILE.eof()){
		std::getline(this->FILE, this->CString);
		lineNumber++;
	}
	this->FILE.seekg(0);
	return lineNumber;
}

bool FileManager::GetBoolFromString()
{

	FileManager::GetStringFromFile();

	if (this->CString == "True" || this->CString == "true")
		return true;
	else if (this->CString == "False" || this->CString == "false")
		return false;

}

int FileManager::GetINTFromFile()
{

	FileManager::GetStringFromFile();
	if (StringHelp::ASCIIToINT(this->CString) == 31)
		this->CString = this->CString;
	return StringHelp::ASCIIToINT(this->CString);

}
