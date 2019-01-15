#include "States.h"

//Idle state is not defined in a function because it's the default state and it's there for the situations in which the driver doesn't have to do anything
enum State
{
	Idle,
	Steering,
	Stuck,
	Break,
	Accelerate
};

States::States()
{
}


States::~States()
{
}

void States::SteeringState()
{
}

void States::StuckState()
{
}

void States::BreakingState()
{
}

void States::AcceleratingState()
{
}
