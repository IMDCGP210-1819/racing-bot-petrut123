#pragma once
/**
This class contains all the calculations necessary to determine the next state of the driver 
**/
class Operations
{
public:
	Operations();
	~Operations();
	bool isOffTrack();
	float getSpeedLimit();
	bool changeGear();
};

