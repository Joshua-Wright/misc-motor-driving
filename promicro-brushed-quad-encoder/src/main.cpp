#include <Arduino.h>
#include <PID_v1.h>



///////////////////////////////////////
/// quadrature decoder

#define PIN_A 7
#define PIN_B 3

volatile long encoder_position = 0;
volatile byte pin_a_state = LOW;
volatile byte pin_b_state = LOW;
volatile byte last_interrupt = 0;

void quad_a_change() {
  pin_a_state = digitalRead(PIN_A);
  if (pin_a_state == HIGH) {
    // rising
    if (pin_b_state == HIGH) {
      encoder_position += 1;
    } else {
      encoder_position -= 1;
    }
  } else {
    // falling
    if (pin_b_state == HIGH) {
      encoder_position -= 1;
    } else {
      encoder_position += 1;
    }
  }
}

void quad_b_change() {
  pin_b_state = digitalRead(PIN_B);

  if (pin_b_state == HIGH) {
    // rising
    if (pin_a_state == HIGH) {
      encoder_position -= 1;
    } else {
      encoder_position += 1;
    }
  } else {
    // falling
    if (pin_a_state == HIGH) {
      encoder_position += 1;
    } else {
      encoder_position -= 1;
    }
  }
}

void setup_quad_decoder() {
  pinMode(PIN_A, INPUT);
  pinMode(PIN_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_A), quad_a_change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_B), quad_b_change, CHANGE);
}

///////////////////////////////////////
/// motor control

#define PIN_ENA1 10
#define PIN_IN1  16
#define PIN_IN2  14

void forward(int speed) {
  digitalWrite(PIN_IN1, 1);
  digitalWrite(PIN_IN2, 0);
  analogWrite(PIN_ENA1, speed);
}

void reverse(int speed) {
  digitalWrite(PIN_IN1, 0);
  digitalWrite(PIN_IN2, 1);
  analogWrite(PIN_ENA1, speed);
}

void brake() {
  digitalWrite(PIN_IN1, 0);
  digitalWrite(PIN_IN2, 0);
  analogWrite(PIN_ENA1, 0);
}

void floating() {
  digitalWrite(PIN_IN1, 1);
  digitalWrite(PIN_IN2, 1);
  analogWrite(PIN_ENA1, 0);
}


void setup_motor() {
  pinMode(PIN_ENA1, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  // analogWriteResolution(8);
  // analogWriteFrequency(1000);
}

///////////////////////////////////////


//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Define the aggressive and conservative Tuning Parameters
double aggKp=4, aggKi=0.2, aggKd=1;
double consKp=1, consKi=0.05, consKd=0.25;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);


void setup() {
  // put your setup code here, to run once:
  pinMode(PIN3, OUTPUT);
  
  setup_quad_decoder();
  setup_motor();

  Serial.begin(9600);
  myPID.SetMode(AUTOMATIC);
  Setpoint = 10;

  floating();
}

long prev_encoder = 0;
long last_move = 0;
byte min_speed = 32;
byte max_speed = 255;

void loop() {
  Input = double(encoder_position)/100.0;
  double gap = (Setpoint-Input); //distance away from setpoint
  myPID.SetTunings(consKp, consKi, consKd);
  // if (abs(gap) < 100) {
  //   //we're close to setpoint, use conservative tuning parameters
  //   myPID.SetTunings(consKp, consKi, consKd);
  // } else {
  //    //we're far from setpoint, use aggressive tuning parameters
  //    myPID.SetTunings(aggKp, aggKi, aggKd);
  // }

  myPID.Compute();
  if (Output > 1.0) {
    forward(constrain(abs(Output), double(min_speed), double(max_speed)));
  } else if (Output < 1.0) {
    reverse(constrain(abs(Output), double(min_speed), double(max_speed)));
  } else {
    floating();
  }

  if (encoder_position != prev_encoder) {
    digitalWrite(PIN3, 1);

    Serial.print("\t");
    Serial.print(encoder_position, DEC);
    Serial.print("\t");
    Serial.print(pin_a_state);
    Serial.print("\t");
    Serial.print(pin_b_state);
    // Serial.print("\t");

    // Serial.print("\t");
    // if (encoder_position > prev_encoder) {
    //   forward(25);
    //   Serial.print("forward");
    // } else {
    //   reverse(25);
    //   Serial.print("reverse");
    // }

    Serial.print("\t");
    Serial.print(Input);
    Serial.print("\t");
    Serial.print(Setpoint);
    Serial.print("\t");
    Serial.print(Output);
    Serial.print("\t");
    Serial.print(gap);
  
    Serial.println();
    prev_encoder = encoder_position;

  } else {
    digitalWrite(PIN3, 0);
  }

  // digitalWrite(PIN3, 1);
  // delay(1);
  // digitalWrite(PIN3, 0);
  // delay(1);

  // put your main code here, to run repeatedly:
}

