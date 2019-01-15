#pragma once
/**
The behaviour of the driver defined by states.
**/
class States
{
public:
	States();
	~States();
	void SteeringState();
	void StuckState();
	void BreakingState();
	void AcceleratingState();
	enum State;
	State currentState;
};

