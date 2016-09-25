#ifndef SecondaryGame_H
#define SecondaryGame_H

#include "D3DAPP.h"
#include "Element.h"
#include "Button.h"
#include "BasicInterface.h"
#include "Basic2DDraw.h"
#include "Files.h"
#include "Sound.h"

#define INDEX_OF_VP 1
#define HOMELESS_DOWN_SPEED 250
#define HOMELESS_UP_SPEED 50

class SecondaryGame
{
public:
	SecondaryGame(BasicInterface* super);
	void init();
	void Update();
	~SecondaryGame();
protected:

private:
	void spawnHomeless();
	void homelessSlide();

	BasicInterface* super;
	Element* homeless;
	SoundBasic* MainSound;

	bool homelessUp;
	bool tutorial;
};

#endif