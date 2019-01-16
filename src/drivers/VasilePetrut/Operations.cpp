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

bool Operations::isOffTrack()
{
	return false;
}

float Operations::getSpeedLimit(tTrackSeg* segment)
{
	if (segment->type == TR_STR)
	{
		return FLT_MAX;
	}
	else
	{
		float friction = segment->surface->kFriction;
		return sqrt(friction * G * segment->radius);
	}
}

bool Operations::changeGear()
{
	return false;
}
