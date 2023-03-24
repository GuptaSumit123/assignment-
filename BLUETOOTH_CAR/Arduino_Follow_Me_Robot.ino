

//include the library code:
#include<NewPing.h>           
#include<Servo.h>             
#include<AFMotor.h>           

#define RIGHT A2           
#define LEFT A3              
#define TRIGGER_PIN A1      
#define ECHO_PIN A0           
#define MAX_DISTANCE 200      

unsigned int distance = 0;    
unsigned int Right_Value = 0; 
unsigned int Left_Value = 0; 
  

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  //NewPing setup of pins and maximum distance:

//create motor objects
AF_DCMotor Motor1(1,MOTOR12_1KHZ);
AF_DCMotor Motor2(2,MOTOR12_1KHZ);
AF_DCMotor Motor3(3,MOTOR34_1KHZ);
AF_DCMotor Motor4(4,MOTOR34_1KHZ);

 Servo myservo; 
 int pos=0;    

void setup() { // the setup function runs only once when power on the board or reset the board:
  
   Serial.begin(9600);
   myservo.attach(10); 
{
for(pos = 90; pos <= 180; pos += 1){    
  myservo.write(pos);                   
  delay(15);                          
  } 
for(pos = 180; pos >= 0; pos-= 1) {     
  myservo.write(pos);                  
  delay(15);                            //wait 15ms for the servo to reach the position:
  }
for(pos = 0; pos<=90; pos += 1) {       //goes from 180 degrees to 0 degrees:
  myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
  delay(15);                            //wait 15ms for the servo to reach the position:
  }
}
   pinMode(RIGHT, INPUT); 
   pinMode(LEFT, INPUT); 
}

// the lope function runs forever
void loop() {                             
  
delay(50);                                        //wait 50ms between pings:
distance = sonar.ping_cm();                       //send ping, get distance in cm and store it in 'distance' variable:
Serial.print("distance");                   
Serial.println(distance);                         // print the distance in serial monitor:


    Right_Value = digitalRead(RIGHT);             // read the value from Right IR sensor:
    Left_Value = digitalRead(LEFT);               // read the value from Left IR sensor:
 
Serial.print("RIGHT");                      
Serial.println(Right_Value);                      // print the right IR sensor value in serial monitor:
Serial.print("LEFT");                       
Serial.println(Left_Value);                       //print the left IR sensor value in serial monitor:

if((distance > 1) && (distance < 15)){            //check wheather the ultrasonic sensor's value stays between 1 to 15.
                                                  //If the condition is 'true' then the statement below will execute:
  //Move Forward:
  Motor1.setSpeed(130);  
  Motor1.run(FORWARD);   
  Motor2.setSpeed(130);  
  Motor2.run(FORWARD);  
  Motor3.setSpeed(130);  
  Motor3.run(FORWARD);   
  Motor4.setSpeed(130);  
  Motor4.run(FORWARD);   
  
}else if((Right_Value==0) && (Left_Value==1)) {   //If the condition is 'true' then the statement below will execute:
  
  //Turn Left                                                
  Motor1.setSpeed(150);  //define motor1 speed:
  Motor1.run(FORWARD);   //rotate motor1 cloclwise:
  Motor2.setSpeed(150);  //define motor2 speed:
  Motor2.run(FORWARD);   //rotate motor2 clockwise:
  Motor3.setSpeed(150);  //define motor3 speed:
  Motor3.run(BACKWARD);  //rotate motor3 anticlockwise:
  Motor4.setSpeed(150);  //define motor4 speed:
  Motor4.run(BACKWARD);  //rotate motor4 anticlockwise:
  delay(150);
  
}else if((Right_Value==1)&&(Left_Value==0)) {     //If the condition is 'true' then the statement below will execute:
  
  //Turn Right
  Motor1.setSpeed(150);  //define motor1 speed:
  Motor1.run(BACKWARD);  //rotate motor1 anticlockwise:
  Motor2.setSpeed(150);  //define motor2 speed:
  Motor2.run(BACKWARD);  //rotate motor2 anticlockwise:
  Motor3.setSpeed(150);  //define motor3 speed:
  Motor3.run(FORWARD);   //rotate motor3 clockwise:
  Motor4.setSpeed(150);  //define motor4 speed:
  Motor4.run(FORWARD);   //rotate motor4 clockwise:
  delay(150);
  
}else if(distance > 15) {                          //If the condition is 'true' then the statement below will execute:
  
  //Stop
  Motor1.setSpeed(0);    //define motor1 speed:
  Motor1.run(RELEASE);   //stop motor1:
  Motor2.setSpeed(0);    //define motor2 speed:
  Motor2.run(RELEASE);   //stop motor2:
  Motor3.setSpeed(0);    //define motor3 speed:
  Motor3.run(RELEASE);   //stop motor3:
  Motor4.setSpeed(0);    //define motor4 speed:
  Motor4.run(RELEASE);   //stop motor4:
}
}
