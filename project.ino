#include <Servo.h>   //servo library
Servo servo;    
int pushPin = 4; 
int trigPin = 5;    
int echoPin = 6;   
int servoPin = 7;
int LED = 10;
long duration, dist, buttonState = 0, pushed = 0;   
long avg[3];   //array for average

void setup() {   
  Serial.begin(9600);    
    servo.attach(servoPin);  //will connect servoPIN to the servo(so that this pin will know that he needs to get input from the arduino).
    pinMode(trigPin, OUTPUT);//set the trigPin to be output for the sensor.
    pinMode(echoPin, INPUT); //set the echoPin to be input for the sensor.
    pinMode(LED, OUTPUT);//set the LED to be output for the LED.
    pinMode(pushPin, INPUT);//for the button.
    servo.write(0);//close cap on power on(sets the angle of the shaft (in degrees)).
    servo.detach();
} 

/*
 * a function that gets time(in microseconds), and converts it to distance(centimeters).
 */
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29.1 / 2;
}

/*
 * measure the distance in centimeters and puts the distance in dist variable.
 */
long measure() {  
  digitalWrite(trigPin, HIGH);//Write HIGH value to a digital pin(sensorOutputPIN). 
  digitalWrite(trigPin, LOW);
  //pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);//pulseIn Measures the time Between a pulse (LOW to HIGH) -> to LOW again, and return this time in microseconds or return 0 if it gives up
  return microsecondsToCentimeters(duration);//obtain distance
}

 void loop() { 
    buttonState = digitalRead(pushPin);//get the state of the button(0 if not pressed)
    if(buttonState == 1) {//save the state of the button.
      pushed = 1 - pushed;//if its preesed
      delay(1000);
    }
  Serial.println(pushed);//for The designers.
  
  if(pushed == 1) {//if the button is prssed then...
    for (int i = 0; i <= 2; i++)    //average distance   
      avg[i] = measure();            
  
    dist = (avg[0] + avg[1] + avg[2])/3;//calculate the average distance       
  
    if (dist < 50 ) {//lets move!
      servo.attach(servoPin);//turn on again
      digitalWrite(LED,HIGH);
      servo.write(0);//set the current angle(on closed mode) to be 0.
      delay(4000);       
      servo.write(150);   //move 150 degreas 
      delay(1000);
      servo.detach();//acts like servo.close()
      digitalWrite(LED,LOW);  
    
    }
  }   
}
