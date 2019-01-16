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
	void StuckState();
	void BreakingState();
	void AcceleratingState(tCarElt* car, float maxSpeed);
	enum class State
	{
		Idle,
		Steering,
		Stuck,
		Break,
		Accelerate
	};
	State currentState = State::Steering;
};

