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

#include "States.h"



States::States()
{
}

States::~States()
{
}
//The driver tries to steer towards the middle of the track 
//Not very efficient when it comes to lap times but it's a safe option
void States::SteeringState(tCarElt* car)
{
	float angle;
	angle = RtTrackSideTgAngleL(&(car->_trkPos)) - car->_yaw;
	NORM_PI_PI(angle); 

	angle -= car->_trkPos.toMiddle / car->_trkPos.seg->width;

	car->ctrl.steer = angle / car->_steerLock;
}

void States::StuckState(tCarElt* car)
{
	float angle;
	angle = RtTrackSideTgAngleL(&(car->_trkPos)) - car->_yaw;
	NORM_PI_PI(angle);

	angle -= car->_trkPos.toMiddle / car->_trkPos.seg->width;

	car->ctrl.steer = -angle / car->_steerLock;
}

void States::BrakingState(tCarElt* car)
{
	//If the speed is too low we risk dividing by 0 when we calculate the slip
	if (car->_speed_x < 3) //do not brake
	{
		return;
	}

	float slip = 0;
	//This calculates the average slip of the wheels
	for (int i = 0; i < 4; i++) 
	{
		slip += car->_wheelSpinVel(i) * car->_wheelRadius(i) / car->_speed_x;
	}
	slip = slip / 4;

	if (slip < 0.9) 
	{
		car->ctrl.brakeCmd = slip;
	}
}
//When the driver enters this state it sets the amount of acceleration needed for the speed limit on the current segment and then gears up / down
void States::AcceleratingState(tCarElt* car, float maxSpeed)
{
	car->ctrl.accelCmd = maxSpeed / car->_wheelRadius(REAR_RGT) * car->_gearRatio[car->_gear + car->_gearOffset] / car->_enginerpmRedLine;

	// I was not able to find out why the car was always shifting from neutral to one and back so I commented out the code and replaced
	// it with car->ctrl.gear = 1 in the drive function of the robot
	/*if (car->_gear <= 0)
	{
		car->ctrl.gear = 1;
	}
	else if (car->_enginerpmRedLine / car->_gearRatio[car->_gear + car->_gearOffset] * car->_wheelRadius(REAR_RGT) < car->_speed_x) 
	{
		car->ctrl.gear = car->_gear + 1;
	}
	else if (car->_gear > 1 && car->_enginerpmRedLine / car->_gearRatio[car->_gear + car->_gearOffset - 1] * car->_wheelRadius(REAR_RGT) > car->_speed_x + 5)
	{
		car->ctrl.gear = car->_gear - 1;
	}
	else
	{
		car->ctrl.gear = car->_gear;
	}*/
}
