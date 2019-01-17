#pragma once
/**
The behaviour of the driver defined by states.
**/
class States
{
public:
	States();
	~States();
	void SteeringState(tCarElt* car);
	void StuckState(tCarElt* car);
	void BrakingState(tCarElt* car);
	void AcceleratingState(tCarElt* car, float maxSpeed);
	enum class State
	{
		Idle,
		Steering,
		Stuck,
		Brake,
		Accelerate
	};
	State currentState = State::Steering;
};

