#include <Servo.h> 

Servo myservo;  // create servo object to control a servo
int pos = 0;  // variable to store the servo position
const int trigPin = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
int duration;
int distance;
// Motor A connections
int in1 = 2;
int in2 = 3;
// Motor B connections
int in3 = 7;
int in4 = 8;
// vacuum cleaner connections
int in5 = 9;
int in6 = 10;
//pump connections
int in7 = 12;
int in8 = 13;
int pump = 4;
unsigned int val;

void setup() {
  // attaches the servo on pin 10 to the servo object
  myservo.attach(11); 
  Serial.begin(9600);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (Serial.available() > 0) {
    val = Serial.read();
    if (val == 'm') {
      while (val != 'n') {
        val = Serial.read();
        if (val == 'w') {
          forward();
        }
        if (val == 's') {
          back();
        }
        if (val == 'a') {
          left();
        }
        if (val == 'd') {
          right();
        }
        if (val == 'q') {
          off();
        }
        if (val == 'v') {
          vacuum_on();
        }
        if (val == 'b') {
          vacuum_off();
        }
        if (val == 'g') {
          mop_on();
        }
        if (val == 'h') {
          mop_off();
        }
        if (val == 'u') {
          pump_on();
        }
      }
      if (val == 'n') {
        off();
      }
    }
    if (val == 'p') {
      vacuum_on();
      mop_on();
      while (val != 'o') {
        val = Serial.read();
        int d, d1, d2;
        myservo.write(90);
        delay(1000);
        
        d = measureDistance();
        Serial.print("Distance = ");
        Serial.print(d);
        Serial.println(); 
        delay(1000);
        if (d < 30) {
          myservo.write(30);
          
          
          // sweeps from 0 degrees to 180 degrees
//          for (pos = 60; pos <= 120; pos += 1) {
//            myservo.write(pos);
//            delay(15);
//          } 
          
          d1 = measureDistance();
          delay(500);
          Serial.print("Distance1 = ");
          Serial.print(d1);
          Serial.println();
          delay(100);
          myservo.write(90);
          // sweeps from 180 degrees to 0 degrees
//          for (pos = 120; pos >= 0; pos -= 1) {
//            myservo.write(pos);
//            delay(15);
//          }
          delay(500);
          myservo.write(150);
          d2 = measureDistance();
          delay(500);
          Serial.print("Distance2 = ");
          Serial.print(d2);
          Serial.println();
          delay(1000);
          myservo.write(90);
          if (d1 >= d2) {
            
            delay(100);
            left();
            delay(3000);
            forward();
          } else {
            
            delay(100);
            right();
            delay(3000);
            forward();
          }
        } else {
          myservo.write(90);
          forward();
        }
        pump_on();
        delay(1000);
      }
      off();
    }
  }
}

void forward() {
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
}

void off() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
}

void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void back() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void vacuum_on() {
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
}

void vacuum_off() {
   digitalWrite(in5, LOW);
   digitalWrite(in6, LOW);
}

void mop_on() {
   digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
}

void mop_off() {
   digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
}

long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  return distance;
}

void pump_on() {
  digitalWrite(pump, HIGH);
  delay(500);
  digitalWrite(pump, LOW);
}

