#include "GUIPhysBasic.h"

PhysBasic::PhysBasic(BasicInterface* super)
	:Element(super)
{

	this->Mass = 10;
	this->LifeTime = 0;
	this->LLifeTime = 0;

	this->IsPhysicEnabled = true;

}

PhysBasic::~PhysBasic()
{

}

void PhysBasic::Spawn(Vector2d& position, short indexOfVP)
{

	Element::Spawn(position, indexOfVP);

	this->ATexture = this->MaterialPtr->AdditionalTexture;

}

void PhysBasic::PhysUpdate()
{

	this->Impulse.Y = this->Impulse.Y - PH_G * this->Mass * this->Super->GetTimer()->GetDeltaTime();
	this->Position = this->Position + this->Impulse * this->Super->GetTimer()->GetDeltaTime();

}

bool PhysBasic::Update()
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

	if (this->IsPhysicEnabled)
		this->PhysUpdate();

	if (this->ATexture)
		this->MaterialPtr->AdditionalTexture = this->ATexture;

	return true;
}