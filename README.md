Quadcopter
==========

This project will be set up from the ground up to develop the software for a quadcopter.

For the first version, to get to a flying quadcopter we'll focus on the following parts:
* Flight controller board
  * Application and libraries
* Remote control application
  * Running on a Linux desktop

In future iteration we are planning to add:
* Android remote control application
* More telemetry support
* Camera support
* GPS support

Since we'll be making 2 quadcopters to play with, we've chosen to base one design on the Raspberry Pi and the other one the Beaglebone Black hardware platform.  Hardware and software design choices will need to consider the difficulties of developing a common code base for two distint hardware platforms.
