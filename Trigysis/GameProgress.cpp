#include "GameProgress.h"

GameProgress::GameProgress(int storyPoint, int location){
	this->setStoryPoint(storyPoint);
	this->setLocation(location);
	this->crypt = new Crypter();
	locationS = "location";
	storyPointS = "storyPoint";
	saveFile = "";
}

void GameProgress::Update()
{
	std::size_t found;
	std::size_t delimiter;
	std::string result = "";
	this->saveFile = this->crypt->readFile();
	found = getFound(locationS);
	delimiter = this->saveFile.find(":");
	result = this->saveFile.substr(found, delimiter);
	setLocation(atoi(result.c_str()));
	found = getFound(storyPointS);
	delimiter = this->saveFile.find(":");
	result = this->saveFile.substr(found, delimiter);
	setStoryPoint(atoi(result.c_str()));
}

std::size_t GameProgress::getFound(std::string& name)
{
	return this->saveFile.find(name) + name.size();
}


void GameProgress::setLocation(int location){
	this->location = location;
}

void GameProgress::setStoryPoint(int storyPoint){
	this->storyPoint = storyPoint;
}

int GameProgress::getLocation(){
	return this->location;
}

int GameProgress::getStoryPoint(){
	return this->storyPoint;
}

GameProgress::~GameProgress(){
	delete this->crypt;
}