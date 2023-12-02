#include <Servo.h>


#define PWM_A 4 // left motor
#define PWM_B 5 // Right Motor
#define AIN1 32
#define AIN2 34
#define BIN1 30
#define BIN2 36

#define echoPin 31
#define trigPin 33
Servo myservo;

float distance1, distance2, distance3;
int PWM = 128;

int turn_direction;

int left_sensor = 27;
int right_sensor = 23;
int middle_sensor = 25;
int left_reading;
int right_reading;
int middle_reading;

void setup() {
  Serial.begin(9600);

  myservo.attach(51);
  myservo.write(96);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(left_sensor, INPUT);
  pinMode(right_sensor, INPUT);
  pinMode(middle_sensor, INPUT);

  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
 
}

void loop() {
  
  //1 is on the line 0 is off the line 
  left_reading = digitalRead(left_sensor);
  right_reading = digitalRead(right_sensor);
  middle_reading = digitalRead(middle_sensor);

  distance1 = ping();
  distance2 = ping();
  distance3 = ping();


  if(distance1 < 20 && distance2 < 20 && distance3 < 20){
    stopRobot();
    delay(300);
    rightTurn();
    delay(500);
    forward();
    delay(750);
    leftTurn();
    delay(850);
    forward();
    delay(450);
    while(!left_reading && !middle_reading && !right_reading){
      forward();
      left_reading = digitalRead(left_sensor);
      right_reading = digitalRead(right_sensor);
      middle_reading = digitalRead(middle_sensor);
    }
  }

  if(left_reading && middle_reading && !right_reading){
    leftTurn();
    turn_direction = 0;
  }

  else if(left_reading && !middle_reading && !right_reading){
    leftTurn();
    turn_direction = 0;
  }

  else if(!left_reading && !middle_reading && right_reading){
    rightTurn();
    turn_direction = 1;
  }
  else if(!left_reading && middle_reading && right_reading){
    rightTurn();
    turn_direction = 1;
  }
  else if(!left_reading && middle_reading && !right_reading){
    forward();
  }
  else if(left_reading && middle_reading && right_reading){
    forward();
  }
  else if(!left_reading && !middle_reading && !right_reading){
    if(turn_direction == 1){
      hardRight();
    }
    else{
      hardLeft();
    }
  }
  else if(left_reading && !middle_reading && right_reading){
    stopRobot();
  }

}

float ping() {
  long duration;
  float distance;
 // Set the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
// Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
// The pulseIn function times the signal return after bouncing off the object
  duration = pulseIn(echoPin, HIGH);
// Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (wave goes and comes back)
  if(distance == 0){
    distance = 100;
  }
  return distance;
}

void forward(){
  //Set speed
  analogWrite(PWM_A, PWM);
  analogWrite(PWM_B, PWM);

  digitalWrite(AIN1, HIGH); //Spin motor A
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, HIGH); //Spin motor B
  digitalWrite(BIN2, LOW);
}

void rightTurn(){
  //Set speed
  analogWrite(PWM_A, PWM - 70);
  analogWrite(PWM_B, PWM + 70);

  digitalWrite(AIN1, HIGH); //Spin motor A
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, HIGH); //Spin motor B
  digitalWrite(BIN2, LOW);
}

void hardRight(){
  analogWrite(PWM_A, 0);
  analogWrite(PWM_B,PWM + 70);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}


void leftTurn(){
  //Set speed
  analogWrite(PWM_A, PWM + 70);
  analogWrite(PWM_B, PWM - 70);

  digitalWrite(AIN1, HIGH); //Spin motor A
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN2, HIGH); //Spin motor B
  digitalWrite(BIN1, LOW);
}

void hardLeft(){
  analogWrite(PWM_A,PWM + 70);
  analogWrite(PWM_B, 0);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void stopRobot(){
  //stop motors
  digitalWrite(AIN1, LOW); 
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN2, LOW); 
  digitalWrite(BIN1, LOW);
}
