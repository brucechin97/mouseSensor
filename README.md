# mouseSensor

Reading data from an optical mouse sensor for the purpose of reading relative movement in x and y direction.
Written in C++ for Embedded Linux (BeagleBone Black was used for this project).

Everything in Linux is a file. So the information for any hardware can be accessed through the device file.
These files can be opened with the system call open() and can be read with the system call read().
This saves us the trouble of soldering or connecting cables to the CMOS chip, because the data can be retrieved through USB directly.

When the mouse is moved or clicked, a signal is sent to the computer which will trigger an interrupt.
A piece of code in the Linux Kernel then calls an Interrupt handler to read the data and carry out the respective program.
The purpose of this code is to retrieve these information to calculate the number of pixels moved and to convert them into millimeters.


The command "cat /proc/bus/input/devices" in the terminal lists out the devices that are connected. In our case it was the Handler "event1".
