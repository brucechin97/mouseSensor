/*
 * CMaus.cpp
 *
 *  Created on: Feb 7, 2020
 *      Author: Bruce Chin
 */

#include "CMaus.h"
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <string>

using namespace std;

CMaus::CMaus(const string& device)
: mDeltaX(0), mDeltaY(0), mPhi(0), 	mX_abs(0), mY_abs(0)
{
	mDevice = device;

	if((fd = open(mDevice.c_str(), O_RDONLY)) < 0)
		{
			std::cout << "Failed to open " << mDevice << std::endl;
		}
}

CMaus::~CMaus()
{
	close(fd);
}

int CMaus::getEvent()
{
	if (read(fd, &ie, sizeof(struct input_event)) != 1)		// read Event Handler
		{
			if(ie.type == EV_REL)		// if Event Type = relative movement
			{
				switch (ie.code)
				{
				case REL_X:				// Event was relative motion in x axis
					mDeltaX += ie.value;
					break;

				case REL_Y:				// Event was relative motion in y axis
					mDeltaY  += ie.value;
					break;

				default:
					cout<<"No relative movement.\n";
				}
			}
			return 0;
		}

	else return 1;
}

int CMaus::getData(double& pX, double& pY, double& pPhi)
{
	pX = mX_abs;
	pY = mY_abs;
	pPhi = mPhi;
	return 0;
}

void CMaus::deltaInMm()	// Konvertierung der Messung in mm
{
	mDeltaX = mDeltaX / Faktor_pxToMM;
	mDeltaY = mDeltaY / Faktor_pyToMM;
}

int CMaus::update()
{
		deltaInMm();
		mPhi = mPhi + mDeltaY/radius;				// in rad
		mX_abs = mX_abs - mDeltaX * sin(mPhi);
		mY_abs = mY_abs + mDeltaX * cos(mPhi);
		mDeltaX = 0;
		mDeltaY = 0;

/*		switch (mAbsolutMoveData.mMode)
				{
				case EStatus::CWCAM:
				case EStatus::CCWCAM:
					mSensorData.mAlpha = mSensorData.mAlpha + mSensorData.mRel_Y/radius;				// Winkel Alpha in rad
					break;

				default:
					mSensorData.mCartPosition.mX = mSensorData.mCartPosition.mX - mSensorData.mRel_Y * cos(mSensorData.mAlpha);		// im Falle von Schlupf, wenn eigentlich keine Winkeländerung passieren soll
					mSensorData.mCartPosition.mY = mSensorData.mCartPosition.mX - mSensorData.mRel_Y * sin(mSensorData.mAlpha);
					break;

				}
				mSensorData.mCartPosition.mX = mSensorData.mCartPosition.mX - mSensorData.mRel_X * sin(mSensorData.mAlpha);
				mSensorData.mCartPosition.mY = mSensorData.mCartPosition.mX + mSensorData.mRel_X * cos(mSensorData.mAlpha);

				mSensorData.mRel_X = 0;				// Reset relative data for next measurement
				mSensorData.mRel_Y = 0;
				*/

	return 0;
}
