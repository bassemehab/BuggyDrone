//Temp
float tempInput; // tempreture sensor Input
float temp; // real temperature
int tempInputPin=0; //pin which temp sensor bluged in

int x = 50; // the distance before reaching the v(lim)>>Maximum velocity (in cm)
int changeDirectionForwardPin = 2;
int motor1 = 3;
int motor2 = 4;
int changeDirectionBackwardPin = 5;
int motor3 = 6;
int motor4 = 7;

//Sonar hight
int echoPinHight = 8;
int initPinHight = 9;
int hight=0;

//Reverse motor direction pins
int reverseMotor1=10;
int reverseMotor2=11;
int reverseMotor3=12;
int reverseMotor4=13;


void setup() {
  pinMode(tempInputPin,INPUT);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(motor3,OUTPUT);
  pinMode(motor4,OUTPUT);
  pinMode(changeDirectionForwardPin,OUTPUT);
  pinMode(changeDirectionBackwardPin,OUTPUT);
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,LOW);
  digitalWrite(motor3,LOW);
  digitalWrite(motor4,LOW);
  digitalWrite(changeDirectionForwardPin,LOW);
  digitalWrite(changeDirectionBackwardPin,LOW);
  
  //Hight sensor (Sonar)
  pinMode(initPinHight,OUTPUT);
  pinMode(echoPinHight,INPUT);
  Serial.begin(9600);
  
  //Reverse Motors direction
  pinMode(reverseMotor1,LOW);
  pinMode(reverseMotor2,LOW);
  pinMode(reverseMotor3,LOW);
  pinMode(reverseMotor4,LOW);
}

void loop() {

  sendData();
  delay(250);
}

void sendData(){
  sendTemp();
}

void sendTemp(){
  temp=analogRead(tempInputPin);
  temp=(5.0*tempInput*100)/1024;
  //Temp is Ready To be sent ... <code here>
}
void checkPressure(){}
void checkGravity(){}

//check if there is any obstacles to reach next step
boolean checkObstaclesAtDirection(String direction,float movingDistance){
  if(direction=="up"){
  //Move servo that connected to ultrasonic obstacles checker up
  }
  else if(direction=="down"){}
  else if(direction=="forward"){}
}

//checking your hieght
float getHight(){ //using ultrasonic
  digitalWrite(initPinHight,LOW);
  delayMicroseconds(2);
  digitalWrite(initPinHigh,HIGH);
  delayMicroseconds(10);
  digitalWrite(echoPinHight,LOW);
  float duration=pulseIn(echoPinHight, HIGH);
  hight=(duration/2)29.1;
  return hight;
}

void reverseMotors(String motorName,String startORend){
  if(startORend=="start"){
    if(motorName=="motor1"){
      digitalWrite(reverseMotor1,HIGH);
    }else if(motorName=="motor2"){
      digitalWrite(reverseMotor2,HIGH);
    }else if(motorName=="motor3"){
      digitalWrite(reverseMotor3,HIGH);
    }else if(motorName=="motor4"){
      digitalWrite(reverseMotor4,HIGH);
    }else if(motorName=="all"){
      digitalWrite(reverseMotor1,HIGH);
      digitalWrite(reverseMotor2,HIGH);
      digitalWrite(reverseMotor3,HIGH);
      digitalWrite(reverseMotor4,HIGH);
    }
  }else if(startORend=="end"){
    if(motorName=="motor1"){
      digitalWrite(reverseMotor1,LOW);
    }else if(motorName=="motor2"){
      digitalWrite(reverseMotor2,LOW);
    }else if(motorName=="motor3"){
      digitalWrite(reverseMotor3,LOW);
    }else if(motorName=="motor4"){
      digitalWrite(reverseMotor4,LOW);
    }else if(motorName=="all"){
      digitalWrite(reverseMotor1,LOW);
      digitalWrite(reverseMotor2,LOW);
      digitalWrite(reverseMotor3,LOW);
      digitalWrite(reverseMotor4,LOW);
    }
  }
}

void moveUp(float dist){
  if(!checkObstaclesAtDirection("up",dist)){
    float requiredHight=getHight+dist; //the required height after this step
    if(dist>2x){ //first case Look at app slides
    int y=dist-2x;
    float p1=getHight+x; //firt point >> the point of stopping motors
    float p2=getHight+x+y; //second point >> the point of reverse motors rotating direction
    float p3=getHight+x+y+x;//third point >> the point of stop moving
    for(int i=0;i<=255;i++){
    analogWrite(motor1,i);
    analogWrite(motor2,i);
    analogWrite(motor3,i);
    analogWrite(motor4,i);
    delay(50);
    if(getHight==p1){
      break;
    }
    }
    loop{
    if(getHight==p2){
      break;
    }
    }
    for(i;i>=0;i--){
    revreseMotors("all","start");
    analogWrite(motor1,i);
    analogWrite(motor2,i);
    analogWrite(motor3,i);
    analogWrite(motor4,i);
    revreseMotors("all","end");
    delay(50);
    }
    }
    // case 2 short distances
    if(dist<=2x){
    float p1=getHight+dist/2; //firt point >> the point of reverse motors rotating direction
    float p2=getHight+dist; //second point >> the point of stop movement
    for(int i=0;i<=255;i++){
      analogWrite(motor1,i);
      analogWrite(motor2,i);
      analogWrite(motor3,i);
      analogWrite(motor4,i);
      delay(50);
      if(getHight==p1){
      break;
      }
    for(i;i>=0;i--){
      analogWrite(motor1,i);
      analogWrite(motor2,i);
      analogWrite(motor3,i);
      analogWrite(motor4,i);
      delay(50);
      if(getHight==p2){
      break;
      }
    }
    
    }
    //Error Correction (tolerence 1cm)
    float error=getHight-requiredHight;
    if(error>1){
      moveDown(error);
    }else if(error<-1){
      moveUp(error);
  }
    
   //sendback success message to application to get next step
  }
  }else{
  //sendback faild message to application to repeat this step in different way
  }
}
void moveDown(float dist){}
void rotatRight(float degree){}
void rotatLeft(float degree){}
void moveForward(float dist){}




