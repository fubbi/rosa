rosa
====

Rosa Barba Eiki Control

the board is a sparkfun clone so you need to put the folder "SF32u4_boards" in 
~/Arduino/hardware/

if you do not have the folder hardware just create it. make sure you are running arduino 1.0.1 or higher
the connector is micro USB.

you should see this board: Sparkfun Pro Micro 5V/16MHz

The code has a startup function which sends the motor moving left until it hits the button. this sets the rotary controller
to zero and then rolls it up to position A and then starts cycling it between A and B.

the rotary encoder value is negative so position B (right) needs to be less than position A (left)

use these parameters to change position A and B and the idle time between moving.

// motor position settings:
int posA = -39; 
int posB = -57;
int pause = 7000; // seven second pause


the whole switch case scenario is supposed to listen to the proximity sensor but I had no chance to implement it. it does however work. it is an analog read on A2 and you will have various values coming and a hard zero on contact with the inductive surface (its already on the film) so it is easy to implement. the sensor also has several yellow leds on its shaft where you can see when contact occurs.

the way i was going to do it was to let the startup function go all the way to position A and hold there and wait for the proximity sensor impulse.
this would require a delay at the end of the startup function with the duration of the time from the sensor impulse to the first text plate.

good luck!

fubbi





