# Remote-Start
The goal of this project was to start my car remotely, I did this using three relays, 
an Arduino, and a Roku tv remote. Located behind the steering wheel there is an ignition,
starter, accessory, and a 12v constant wire. For the engine to turn over the ignition
wire has to have a connection with the 12v constant wire to power the cars ECU, fuel pump,
and every other component required to start the car. After the ignition and 12v wires are
connected the starter wire can be powered, however this one only needs to be powered for
long enough for the car to start. I accomplished this by setting delays between the time
ignition wire gets power, and the amount of time the starter wire gets power. After this
the car is started and the accessory wire gets power. The accessory wire powers the ac, 
radio, and other components not required for the engine to run.
