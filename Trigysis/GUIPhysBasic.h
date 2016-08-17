#ifndef PHYS_BASIC_H
#define PHYS_BASIC_H

#include "Element.h"

#define PH_G 9.8

class PhysBasic : public Element
{

public :
	PhysBasic(BasicInterface* super);
	virtual ~PhysBasic();

	void SetLifeTime(float newLifeTime) { this->LifeTime = newLifeTime; }
	float GetLifeTime() { return this->LifeTime; }

	float GetLifeTimeLeft(){ return this->LifeTime - this->LLifeTime; }

	void SetMass(float newMass) { this->Mass = newMass; }
	float GetMass() { return this->Mass; }

	void AddImpulse(Vector2d& impulse) { this->Impulse = this->Impulse + impulse; }
	Vector2d& GetImpulse() { return this->Impulse; }
	void SetImpulse(Vector2d& newImpulse) { this->Impulse = newImpulse; }
	void ResetImpulse(){ this->Impulse = Vector2d(0, 0); }

	void TogglePhysic() { this->IsPhysicEnabled ? this->IsPhysicEnabled = false : this->IsPhysicEnabled = false; }

	virtual bool Update() override;
	virtual void Spawn(Vector2d& position, short indexOfVP) override;

protected:

private:

	virtual void PhysUpdate();

private:

	ID3D11ShaderResourceView* ATexture;

	bool IsPhysicEnabled;

	float Mass;

	float LifeTime;
	float LLifeTime;

	Vector2d Impulse;

};

#endif //!PHYS_BASIC_H