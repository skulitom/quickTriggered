#include "SaveGame.h"

SaveGame::SaveGame(GameProgress *currentProgress, std::string fileName){
	this->saveAll(currentProgress,fileName);
}

void SaveGame::saveAll(GameProgress *currentProgress, std::string fileName){
	this->saveLocation(currentProgress->getLocation(), fileName );
	this->saveStoryPoint(currentProgress->getStoryPoint(), fileName);
}

void SaveGame::saveLocation(int location, std::string fileName){
	std::ofstream saveFile;
    saveFile.open(fileName+this->fileType);
	std::string currentName;
	
	saveFile.close();
}

void SaveGame::saveStoryPoint(int storyPoint, std::string fileName){
	std::ofstream saveFile;

//	saveFile.close;
}

int SaveGame::getLocation(){
	return 0;
}

int SaveGame::getStoryPoint(){
	return 0;
}

SaveGame::~SaveGame(){

}