/////////////// GLOBALS ///////////////////

//encoder
int encoderPin1 = 2;
int encoderPin2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

//motor A connected between A01 and A02
//motor B connected between B01 and B02
int STBY = 10; //standby
int pwr = 2;
//Motor B
int PWMB = 5; //Speed control
int BIN1 = 7; //Direction (11)
int BIN2 = 6; //Direction (12)

// button
int stopBut = 4;
int buttonState = 0;

// led
int green = 14;
int red = 15;

// proximity sensor
int proxPin = A2;
int proxValue = 0;
boolean runCase = 2;

///////////////////////////////// CHANGE THESE ///////////////////

// motor position settings: posA = left position, posB = right position
int posA = -39; 
int posB = -57;
int pause = 7000; // seven second pause



void setup(){

  initPins();
  startUp();

}

void loop(){ 


  
  switch (runCase) {
  case 1:
  if(wordCount <= 61){
  do{
    lensRight();
  } while (encoderValue >= posB);
  
    stop();
    wordCount++;
    delay(pause);
do{
    lensLeft();
    } while (encoderValue <= posA);
    stop();
    wordCount++;
    delay(pause);
  } else {
    wordCount = 0;
    runCase = 2;
  }
    break;
  case 2:
      proxValue = analogRead(proxPin);
  if (proxValue == 0){
    runCase = 1;
    delay(postRoll);
  }
  
    break;   
  }

Serial.print("enc: ");
  Serial.println(encoderValue);
  delay(5);

} 
//////////////////// END LOOP //////////////////////

///////// MOTOR COMMANDS ///////////
void stop(){
  //enable standby  
  digitalWrite(STBY, LOW);
}

void lensRight(){
    move(2, 255, 0); //motor 1, pot speed, right
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
}

void lensLeft(){
    move(2, 255, 1); //motor 1, pot speed, left
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
}

/////// ROTARY ENCODER SETUP //////
void updateEncoder(){ 
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}

/////////// INITIALIZE MOTOR //////////////

void startUp(){ 
  do {
    buttonState = digitalRead(stopBut);
    lensLeft();
  } 
  while (buttonState == LOW);

  stop();
  encoderValue = 0;
  delay(200);

do{
  lensRight();
    } 
  while (encoderValue >= posA);

  stop();

  runCase = 2;

  blinky();
}

/////// MOTOR DRIVER //////
void move(int motor, int speed, int direction){ 

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){

  }
  else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

/////// FEEDBACK //////

void blinky(){ 

  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  delay(100);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  delay(100);
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  delay(100);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
}

/////// SETUP //////

void initPins(){ 
  Serial.begin (9600);

  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

  pinMode(stopBut, INPUT);

  pinMode(pwr, OUTPUT);
  pinMode(STBY, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(green, OUTPUT); 
  pinMode(red, OUTPUT); 
}




