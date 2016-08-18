#ifndef PHYS_BASIC_H
#define PHYS_BASIC_H

#include "Element.h"

#define PH_G 9.8

class PhysBasic
{

public:
	PhysBasic();
	virtual ~PhysBasic();

	void SetMass(float newMass) { this->Mass = newMass; }
	float GetMass() { return this->Mass; }

	void AddImpulse(Vector2d& impulse) { this->Impulse = this->Impulse + impulse; }
	Vector2d& GetImpulse() { return this->Impulse; }
	void SetImpulse(Vector2d& newImpulse) { this->Impulse = newImpulse; }
	void ResetImpulse(){ this->Impulse = Vector2d(0, 0); }

	void TogglePhysic() { this->IsPhysicEnabled ? this->IsPhysicEnabled = false : this->IsPhysicEnabled = false; }

	virtual bool Simulate(Vector2d& pos, float deltaTime);

protected:

private:

private:

	bool IsPhysicEnabled;

	float Mass;

	Vector2d Impulse;

};

class EPhysBasic : public Element, public PhysBasic
{

public:
	EPhysBasic(BasicInterface* super);
	virtual ~EPhysBasic();

	virtual bool Update() override;
	virtual void Spawn(Vector2d& position, short indexOfVP) override;

	void SetLifeTime(float newLifeTime) { this->LifeTime = newLifeTime; }
	float GetLifeTime() { return this->LifeTime; }

	float GetLifeTimeLeft(){ return this->LifeTime - this->LLifeTime; }


protected:

private:

private:

	ID3D11ShaderResourceView* ATexture;

	float LifeTime;
	float LLifeTime;

	
};

#endif //!PHYS_BASIC_H