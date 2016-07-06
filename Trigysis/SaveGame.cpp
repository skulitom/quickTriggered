#include "SaveGame.h"

SaveGame::SaveGame(GameProgress *currentProgress, std::string fileName){
	this->saveAll(currentProgress,fileName);
}

void SaveGame::saveAll(GameProgress *currentProgress, std::string fileName){
	this->saveLocation(currentProgress->getLocation(), fileName );
	this->saveStoryPoint(currentProgress->getStoryPoint(), fileName);
}

void SaveGame::save(int num, std::string fileName, std::string name){
	FM->Open(fileName + this->fileType, FM_FILE_WRITE);
	int position = FM->FindString(name);
	if (position = -1){
		position = FM->getLineQuo();
		FM->writeToFileAt(num, position);
	}
	else{
		FM->writeToFileAt(num, position);
	}
}

int SaveGame::getLocation(){
	return 0;
}

int SaveGame::getStoryPoint(){
	return 0;
}

SaveGame::~SaveGame(){

}