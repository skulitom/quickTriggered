#include "GUIPhysBasic.h"

PhysBasic::PhysBasic()
{

	this->Mass = 10;

	this->IsPhysicEnabled = true;

}

PhysBasic::~PhysBasic()
{

}

bool PhysBasic::Simulate(Vector2d& pos, float deltaTime)
{

	if (this->IsPhysicEnabled)
	{
		this->Impulse.Y = this->Impulse.Y - PH_G * this->Mass * deltaTime;
		pos = pos + this->Impulse * deltaTime;
		//this->Position = this->Position + this->Impulse * this->Super->GetTimer()->GetDeltaTime();
	}
	return true;
}

EPhysBasic::EPhysBasic(BasicInterface* super)
	:Element(super)
{

	this->LifeTime = 0;
	this->LLifeTime = 0;

}

EPhysBasic::~EPhysBasic()
{

}

void EPhysBasic::Spawn(Vector2d& position, short indexOfVP)
{

	Element::Spawn(position, indexOfVP);

	this->ATexture = this->MaterialPtr->AdditionalTexture;

}

bool EPhysBasic::Update()
{
	if (!Element::Update())
		return false;

	if (this->LifeTime > 0)
	{
		this->LLifeTime = this->LLifeTime + this->Super->GetTimer()->GetDeltaTime();

		if (this->LLifeTime >= this->LifeTime)
		{
			ElementDelete(this);
			return false;
		}

	}

	this->Simulate(this->GetPosition(), this->Super->GetTimer()->GetDeltaTime());

	if (this->ATexture)
		this->MaterialPtr->AdditionalTexture = this->ATexture;

	return true;
}