#include "GameProgress.h"

GameProgress::GameProgress(int storyPoint, int location){
	this->setStoryPoint(storyPoint);
	this->setLocation(location);
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

}