#include "SecondaryGame.h"

SecondaryGame::SecondaryGame(BasicInterface* super)
{
	this->super = super;
	this->tutorial = false;
	this->homelessUp = false;
	this->homeless = new Element(this->super);
}

void SecondaryGame::init()
{
	spawnHomeless();
}

void SecondaryGame::Update()
{
	if (tutorial)
	{
		homelessSlide();
	}
	else
	{
		if (homelessUp)
		{
			homelessSlide();
		}
	}
}

void SecondaryGame::spawnHomeless()
{
	this->homelessUp = true;
	this->homeless->SetSizes(Vector2d(400, 266));
	this->homeless->SetMaterial(std::string("homelessF"));
	this->homeless->Spawn(Vector2d(200, -150), INDEX_OF_VP);
}

void SecondaryGame::homelessSlide()
{
	if (this->homelessUp)
	{
		if (this->homeless->GetPosition().Y > -500)
		{
			this->homeless->SetPosition(this->homeless->GetPosition()-Vector2d(0,HOMELESS_DOWN_SPEED*this->super->GetTimer()->GetDeltaTime()));
		}
		else
		{
			this->homelessUp = false;
			this->tutorial = true;
		}
	}
	else
	{
		if (this->homeless->GetPosition().Y < -150)
		{
			this->homeless->SetPosition(this->homeless->GetPosition() + Vector2d(0, HOMELESS_UP_SPEED * this->super->GetTimer()->GetDeltaTime()));
		}
		else
		{
			this->homelessUp = true;
		}
	}
}

SecondaryGame::~SecondaryGame()
{
	D3DDelete(homeless);
}