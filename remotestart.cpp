#include <IRremote.h>                     //Library for using IR sensor
 
int RECV_PIN = 11; 
int starter = 2;
int ignition = 7;
int accessory = 4;
int RELAY[] = {0,0,0};

#define code1 0x57E3C03F                  //hex signal sent from ROKU remote for home button
#define code2 0x57E3E817                  //hex signal sent from ROKU remote for power button
                                          //signals were determined from seperate read only script
 
IRrecv irrecv(RECV_PIN);
 
decode_results results;
 
void setup()
{
  Serial.begin(9600);   
  irrecv.enableIRIn();  
  pinMode(starter, OUTPUT);
  pinMode(ignition, OUTPUT);
  pinMode(accessory, OUTPUT);
}
 
void loop() 
{
  if (irrecv.decode(&results)) 
  {
    unsigned int value = results.value;
    switch(value) 
    {
       case code1://starting the car
       if(RELAY[2] == 1)
          {                                   
             digitalWrite(ignition, LOW);   //Ignition relay is activated 1.2 seconds before starter. 
             RELAY[2] = 0;                   //This isto allow enough time for the fuel pump to fully prime.
             delay(1200);                    //This relaywill remain activated until the car is turned off.
          }                                   
               
                         
        if(RELAY[1] == 1) 
          { 
              digitalWrite(starter, LOW);   //Starter relay is activated for 1.2 seconds, then deactivated. 
              RELAY[1] = 0;                 //The vechile this is to be installed in is equipped with an antigrind
              delay(1200);                  //system that disengages the solenoid of the starter once the engine
              digitalWrite(starter, HIGH);  //is started. This allows for a fixed time to be used.
              RELAY[1] = 1;
          }
        if(RELAY[3] == 1)
          {
              digitalWrite(accessory, LOW);  //Accessory relay is not activated until after the starter relay.
              RELAY[3] = 0;                  //This is so the battery still has enough amperage to start the car.
          }
          break; 
          
       case code2:                           //turning the car off. deactivates each relay.
         if(RELAY[2] == 0) 
         {
            digitalWrite(ignition, HIGH);
            RELAY[2] = 1;
         } 
         
         if(RELAY[3] == 0) 
         {
            digitalWrite(accessory, HIGH);
            RELAY[3] = 1;
         }
         
         if(RELAY[1] == 0) 
         {
            digitalWrite(starter, HIGH);
            RELAY[1] = 1;
         }
          break;
             
    }
    irrecv.resume(); // Receive the next value
  }
  }
