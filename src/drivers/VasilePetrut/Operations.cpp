#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <math.h>
#include <tgf.h> 
#include <track.h> 
#include <car.h> 
#include <raceman.h> 
#include <robottools.h>
#include <robot.h>

#include "Operations.h"



Operations::Operations()
{
}


Operations::~Operations()
{
}

bool Operations::isOffTrack(tCarElt* car)
{
	float angle = RtTrackSideTgAngleL(&(car->_trkPos)) - car->_yaw;
	//25 is an arbitrary chosen angle, 5 is an arbitrary cosen speed and 3.5 is an arbitrary chosen distance to the middle of the track (so the driver doesn't think it's stuck in the middle of the track)
	if (fabs(angle) > 25.0 && car->_speed_x < 5.0 && fabs(car->_trkPos.toMiddle) > 3.5 && car->_trkPos.toMiddle * angle < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Operations::getSpeedLimit(tTrackSeg* segment)
{
	//Straight segments don't have a speed limit
	if (segment->type == TR_STR)
	{
		return FLT_MAX;
	}
	else
	{
		float friction = segment->surface->kFriction;
		//sqrt(friction * g * segment->radius) is the formula to calculate the speed limit on a "turn" segment
		return sqrt(friction * G * segment->radius);
	}
}

bool Operations::Brake(tCarElt* car)
{
	//If the car is past the speed limit then it needs to brake
	if (getSpeedLimit(car->_trkPos.seg) < car->_speed_x)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Operations::calculateDistanceToEndOfSegment(tCarElt * car)
{
	//If the segment is straight the distance to the end is the difference between its length and the cars distance to the start of the segment
	if (car->_trkPos.seg->type = TR_STR)
	{
		return car->_trkPos.seg->length - car->_trkPos.toStart;
	}
	else
	{
		//If the segment is a "turn" it has a radius and that needs to be taken into account
		return (car->_trkPos.seg->arc - car->_trkPos.toStart) * car->_trkPos.seg->radius;
	}
}
