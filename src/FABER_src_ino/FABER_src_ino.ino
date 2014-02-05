const int pwmCC = 5;
const int dirCC1 = 4;
const int dirCC2 = 7;
int steppin = 3;
int stepdirpin=12;
int step_delay;
int long last_step_time=0;
float  periodoS=4000*2;
float vel3;
float vel2;
float dir;
float vel;
int velCC;
long velS;

 void setup()
 {
   Serial.begin(9600);
   //pinMode( pinDirA,OUTPUT );
   //pinMode( pinPwmA,OUTPUT );
   pinMode( dirCC1,OUTPUT );
   pinMode( dirCC2,OUTPUT );
   pinMode( pwmCC,OUTPUT );
   pinMode(steppin, OUTPUT);
   pinMode(stepdirpin, OUTPUT);
 }
void setspeedCC(void)
 {
   
   vel=sin(millis()/3000.0)*1000;
   
   //Serial.println(vel);
   if (vel>=0){
   digitalWrite(dirCC1,LOW);
   digitalWrite(dirCC2,HIGH);
   }else{
   digitalWrite(dirCC1,HIGH);
   digitalWrite(dirCC2,LOW);
   }
   
   velCC=int(map(abs(vel),0,1000,254,255));
   //Serial.println(velCC);
 analogWrite(pwmCC,velCC);
 
 }
 
 
 void setspeedStepper(void)
 {
   vel3=(millis()*3.14)/(periodoS);
   //vel3=1;
   vel2=sin(vel3)*1000;
   dir=sin((vel3+1.57)/2);
   //Serial.println(vel2);
   long int velS=map(int(abs(vel2+1000)),0,2000,0.5,15);
   //long int velS=int(abs(vel3+21));
   //velS=1;
   //Serial.println(velS);
   //long speeds=int(velS);
   //_Stepper.setSpeed(speeds);
   //if (dir>=0){
     //numstep=ns;
     //}
     //else{
     //numstep=-ns;
     //}
    
  // _Stepper.step(numstep);
  step_delay = 60L * 1000L / 200 / velS/8;
  if (millis() - last_step_time >= step_delay) {
    last_step_time = millis();
    if (dir >=0){
      //Serial.println("maggiore");
      digitalWrite(stepdirpin, HIGH);}
      else{
        //Serial.println("minore");
        digitalWrite(stepdirpin, LOW);}
        if(int(dir*10)==0){
      periodoS=float(random(3000, 7000));}
    digitalWrite(steppin, HIGH);}
  else{
    digitalWrite(steppin, LOW);}

 }
 
 
 
 void loop()
 {

 setspeedCC();
 setspeedStepper();
 //delay(10);
 }
