#include <Servo.h> 
 
Servo servo_down;
Servo servo_up;

int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  servo_down.attach(10); //Upper Motor
  servo_up.attach(9); // Lower Motor
} 
 
 
void loop() 
{ 
 /*for(pos = 10; pos < 170; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    //servo_down.write(pos); 
    servo_up.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 170; pos>=10; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    //servo_down.write(pos); 
    servo_up.write(pos);            // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } */

//servo_down.write(20);
servo_up.write(70);
} 


