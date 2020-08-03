/*
 * main.cpp
 *
 *  Created on: Dec 3, 2019
 *      Author: Bruce
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
using namespace std;
#include "CMaus.h"					// Einbinden Header file
#define _USE_MATH_DEFINES			// Definierter Wert von Pi
#include <math.h>

#define Maus_fd "/dev/input/event1"

CMaus Sensor_Maus(Maus_fd);			// Sensor als globales Objekt anlegen

int main()
{
	double abs_X, abs_Y = 0;		// Pose des Roboters im Bezug auf absoluten Koordinaten (Tafel)
	double phi = M_PI*1.5;			// Startorientierung
	while (true)
	{
		Sensor_Maus.getEvent();
		Sensor_Maus.update();
		Sensor_Maus.getData(abs_X,abs_Y, phi);
		cout<<"Absolute pos. X: "<<abs_X<<"mm\tAbsolute pos. Y = "<<abs_Y<<"mm\t";
		cout<<"Angle: "<< phi*180/M_PI << endl;						// Ausgabe Winkel in Grad
	}

	return 0;
}
