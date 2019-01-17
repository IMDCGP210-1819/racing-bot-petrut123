#pragma once
/**
This class contains all the calculations necessary to determine the next state of the driver 
**/
class Operations
{
public:
	Operations();
	~Operations();
	bool isOffTrack(tCarElt* car);
	float getSpeedLimit(tTrackSeg* segment);
	bool Brake(tCarElt* car);
	float calculateDistanceToEndOfSegment(tCarElt* car);
};

