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
    if (sel_state != 3){
    sel_state = sel_state + 1; 
    Serial.println("10"); 
  }
    else{
    sel_state = 0;
    Serial.println("11"); 
  }

    lastButtonPressTime = millis();
  }
  if (sel_state == 3){
    //dance
    Serial.println("9");
  }

    if (millis() - lastSerialTime > serialInterval) {
   
    // Serial.print("Select:");
    // Serial.print(sel_state);   
    // Serial.print(" x:" );  
    // Serial.print(x_axis); 
    // Serial.print(" y:" ); 
    // Serial.println(y_axis); 
    // delay(100);
    
    // Reset the serial timer
    lastSerialTime = millis();
  }

  //setting to min
  if (x_axis < 100 && sel_state == 1){
    pos_left = 0;
    //rfmin
    Serial.println("1"); 
  }
  else{
    pos_right = 75;
  }
  if (x_axis < 100 && sel_state == 0){
    pos_right = 0;
    //ltmin
    Serial.println("2"); 
  }
  else{
    pos_left = 75;
  }
  if (y_axis < 100 && sel_state == 1){
    pos_left = 0;
    //rtmin
    Serial.println("3"); 
  }
  else{
    pos_left = 75;
  }
  if (y_axis < 100 && sel_state == 0){
    pos_right = 0;
    //lfmin
    Serial.println("4"); 
  }
  else{
    pos_left = 75;
  }
  //setting to max
  if (x_axis > 500 && sel_state == 1){
    pos_right = 180;
    //rtmax
    Serial.println("5"); 
  }
  else{
    pos_right = 75;
  }
  if (x_axis > 500 && sel_state == 0){
    pos_right = 180;
    //ltmax
    Serial.println("6"); 
  }
  else{
    pos_right = 75;
  }
  if (y_axis > 500 && sel_state == 1){
    pos_left = 180;
    //rfmax
    Serial.println("7"); 
  }
  else{
    pos_left = 75;
  }
  if (y_axis > 500 && sel_state == 0){
    pos_left = 180;
    //lfmax
    Serial.println("8"); 
  }
  else{
    pos_left = 75;
  }

  }

