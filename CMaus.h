/*
 * CMaus.h
 *
 *  Created on: Dec 20, 2019
 *      Author: Bruce Chin
 */

#ifndef CMAUS_H_
#define CMAUS_H_

//#include "Global.h"
#include <string>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/input.h>
#include <cmath>

using namespace std;

#define radius 44.5				// Abstand zwischen Maussensor und Rotationsachse [mm]
//#define Faktor_pxToMM -34.9
//#define Faktor_pyToMM 34.058
#define Faktor_pxToMM -72.8
#define Faktor_pyToMM 76.229

class CMaus
{
public:
	CMaus(const string& device);
	CMaus(const CMaus&) = delete;
	CMaus operator = (const CMaus&) = delete;
	~CMaus();
	int getEvent();
	int getData(double& pX, double& pY, double& pPhi);
	int update();
	void deltaInMm();

private:
	string mDevice;
	int fd = -1;
	double mDeltaX;
	double mDeltaY;
	double mPhi;
	double mX_abs;
	double mY_abs;
	struct input_event ie;
};



#endif /* CMAUS_H_ */
