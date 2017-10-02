/* Glowing LED for Shooting- These will be based only on PAN and not TILT
Red LED would glow iff the angles sent to arduino are less than 3 degrees for 15 consecutive frames, else glows proportionally
*/
#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo_pan; 
Servo servo_tilt;  
int last_pos_pan, updated_pos_pan, last_pos_tilt, updated_pos_tilt;


int save[3]={0,0,0}, digit=0;
int i, recv, angle_recv;
int white_led=5, white_count=0;  // Count for no.of consecutive frames
int white_ref=servo_pan.read();
int laser_diode=6;


void setup() {
  servo_pan.attach(9);
  servo_tilt.attach(10);
  pinMode(white_led, OUTPUT);  
  Serial.begin(9600); 
  Serial.println(white_ref); 
  servo_pan.write(90);   servo_tilt.write(110);
  analogWrite(white_led, 0);  analogWrite(laser_diode, 0);
}

void loop() {
 
  if(Serial.available() >0){
      recv = Serial.read();
      if(recv=='e'){
        for(i=0;i<3;i++)
            save[i]=0;
        Serial.println("e"); 
        digit=0;
      }
      else if(digit<=3){
        save[digit]=recv-48;
        digit=digit+1;
        if(digit==3){
          for(i=0;i<3;i++)
            Serial.println(save[i]); 
          // Updating servo angles and angle to move
          last_pos_pan=servo_pan.read();
          if(last_pos_pan>175 || last_pos_pan<5)
             servo_pan.write(90);
          last_pos_tilt=servo_tilt.read();
          if(last_pos_tilt>175 || last_pos_tilt<5)
             servo_tilt.write(110);
          angle_recv=save[2]+10*save[1];
          
          // Moving the Servos
          if(save[0]==1)
            servo_pan.write(last_pos_pan+angle_recv);
          else if(save[0]==2)
            servo_pan.write(last_pos_pan-angle_recv);
          else if(save[0]==3)
            servo_tilt.write(last_pos_tilt+angle_recv);
          else if(save[0]==4)
            servo_tilt.write(last_pos_tilt-angle_recv);
         
          
          // Updating Pan and Tilt Positions
          updated_pos_pan=servo_pan.read(); 
          updated_pos_tilt=servo_tilt.read();
          
          // Signal to Red LED
          Serial.println(white_ref); 
          Serial.println(last_pos_pan); 
          Serial.println(updated_pos_pan);
          if(save[0]==1 || save[0]==2){
            if(abs(updated_pos_pan-white_ref)<3){
              Serial.println("Entered"); 
              white_count=white_count+1;
              if(white_count>=15)   {                         // This line can be edited
                analogWrite(white_led, 150); 
                analogWrite(laser_diode, 150);
              }
              else if(white_count<15){
                analogWrite(laser_diode, 0);
                analogWrite(white_led, 150*white_count/15);   // This line can be edited
              }
            } 
            else{
              white_ref=updated_pos_pan;
              white_count=0;
              analogWrite(white_led, 0);
            }
          }
          // Cleaning Digits      
          for(i=0;i<3;i++){
            save[i]=0;  
            digit=0; 
          }
        }
      }
  }
}

