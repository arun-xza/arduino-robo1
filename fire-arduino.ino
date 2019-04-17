const int pwm1 = 11 ; //speed for motor 1
const int m1b = 13 ; //motor 1 input a
const int m1a = 12 ;  //motor 1 input b
const int pwm2 = 10 ; //speed for motor 2
const int m2b = 8 ; //motor 2 input a
const int m2a = 7 ;  //motor 2 input b
int  distance = 0;
#define trigPin 4
#define echoPin 9
#define Buzzer 3
int smoke = A5;
// Your threshold value
int smokeThres = 500;

int duration = pulseIn(echoPin, HIGH); 
char BTDATA=0;
int UDATA=0;
char state=0;
int led=2;
int count=0;
  
void setup() 
{    // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
pinMode(pwm1,OUTPUT) ;   //we have to set PWM pin as output 
pinMode(m1a,OUTPUT) ;  //Logic pins are also set as output 
pinMode(m1b,OUTPUT) ; 
pinMode(pwm2,OUTPUT) ;   //we have to set PWM pin as output 
pinMode(m2b,OUTPUT) ;  //Logic pins are also set as output 
pinMode(m2a,OUTPUT) ;
analogWrite(pwm1,220) ; //220 for max speed
analogWrite(pwm2,220) ;  
  pinMode(led,OUTPUT);
  pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(Buzzer, OUTPUT); 
pinMode(smoke, INPUT);
} 

int ultrasonic(void)
{
  int dis=0;
  digitalWrite(trigPin, LOW); 
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(5);
digitalWrite(trigPin, LOW);
int duration = pulseIn(echoPin, HIGH);
return dis = (duration/2) / 29.1;

 }
void light_on(void)
{digitalWrite(led,HIGH);}
void light_off(void)
{digitalWrite(led,LOW);}

void front(void)
{

digitalWrite(m1a,HIGH) ; 
digitalWrite(m1b,LOW) ;
digitalWrite(m2a,HIGH) ;  
digitalWrite(m2b,LOW) ;  

}

void brake(void)
{
digitalWrite(m1a,LOW) ; 
digitalWrite(m1b,LOW) ; 
digitalWrite(m2b,LOW) ; 
digitalWrite(m2a,LOW) ; 
delay(300) ; 
} 
void reverse(void){
digitalWrite(m1a,LOW) ; 
digitalWrite(m1b,HIGH) ; 
digitalWrite(m2a,LOW) ;
digitalWrite(m2b,HIGH) ; 
delay(600) ; 
}
void left(void){
digitalWrite(m1a,LOW) ; 
digitalWrite(m1b,LOW) ;
digitalWrite(m2a,HIGH) ;  
digitalWrite(m2b,LOW) ; 
delay(500) ; 
}
void right (void){
digitalWrite(m1a,HIGH) ; 
digitalWrite(m1b,LOW) ; 
digitalWrite(m2a,LOW) ; 
digitalWrite(m2b,LOW) ; 
delay(500) ;  }

void loop() 
{ 
   int analogSmoke = analogRead(smoke);

  UDATA=0;
  distance = ultrasonic();
  if (distance<30)
  {UDATA=1;}
   Serial.print("SONAR:");
   Serial.println(UDATA);
   Serial.print("                                         Smoke:");
    Serial.print(analogSmoke);
  if(analogSmoke>smokeThres)
  {digitalWrite(Buzzer,HIGH);delay(100);digitalWrite(Buzzer,LOW); }
  
  if(Serial.available() > 0)  //Save income data to variable 'state'   
     { state = Serial.read(); }
      Serial.print("                    bt :");
   Serial.println(state);
   if (state == 'F') {
      state = '1';}
    else if (UDATA==0&&state == '1') {
      front();}
    else if(UDATA==1&&state == '1') {
      light_on();brake();reverse();left();brake();light_off();}
    else if((state=='0')&&((UDATA==1)||(UDATA==0))) {
      brake();}
     else if (UDATA==0&&state == 'L') {
     left();}
      else if (UDATA==0&&state == 'B') {
    reverse();}
     else if (UDATA==0&&state == 'R') {
    right();}
  }
