#include <Servo.h>

Servo foot_left; 
Servo foot_right; 
Servo hip_right; 
Servo hip_left; 

const int y_axis_pin = A1;
const int x_axis_pin = A0;
const int joyButton = 2; 
int joyValue = 0;
int sel_state = 0;  
int pos_left = 75;   
int pos_right = 75;   
int y_axis;
int x_axis;
unsigned long lastButtonPressTime = 0;
unsigned long debounceDelay = 200;
unsigned long lastSerialTime = 0;
unsigned long serialInterval = 500;


void setup() {

  Serial.begin(9600); 

  foot_left.attach(6); 
  foot_right.attach(3); 
  hip_right.attach(11); 
  hip_left.attach(9); 
  // pinMode(sel_pin, INPUT_PULLUP);
  pinMode(joyButton, INPUT_PULLUP);

}

void loop() {

    int buttonState = digitalRead(joyButton);

    foot_left.write(pos_left); 
    foot_right.write(pos_right);
    hip_right.write(pos_right);
    hip_left.write(pos_left);   

    y_axis = analogRead(y_axis_pin);   
    x_axis = analogRead(x_axis_pin);  

    if (buttonState == LOW && (millis() - lastButtonPressTime > debounceDelay)) {
    if (sel_state != 1){
    sel_state = sel_state + 1; 
  }
    else{
    sel_state = 0;
  }
    lastButtonPressTime = millis();
  }
    if (millis() - lastSerialTime > serialInterval) {
   
    Serial.print("Select:");
    Serial.print(sel_state);   
    Serial.print(" x:" );  
    Serial.print(x_axis); 
    Serial.print(" y:" ); 
    Serial.println(y_axis); 
    delay(100);
    
    // Reset the serial timer
    lastSerialTime = millis();
  }

 


  if (x_axis < 100 && sel_state == 1){
    pos_left = 0;
  }
  else{
    pos_left = 75;
  }

  if (x_axis < 100 && sel_state == 0){
    pos_right = 0;
  }
  else{
    pos_right = 75;
  }
  }

