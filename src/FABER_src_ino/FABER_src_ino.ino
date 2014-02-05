// definisco il pin pwm per il motore CC
const int pwmCC = 5; 
// definisco i pin che determinano la direzione del motore CC
const int dirCC1 = 4;
const int dirCC2 = 7;
// definisco il pin per il motore Stepper
int steppin = 3;
// definisco il pin che determina la direzione del motore Stepper
int stepdirpin=12;
// inizializzo la variabile che determina quanto tempo intercorre tra uno step e l'altro
int step_delay;
// inizializzo la variabile che determina quanto tempo è durato l'ultimo step
int long last_step_time=0;
// definsco quanto è il periodo max delle rotazioni del motore Stepper
float  periodoS=8000;
// inizializzo tre variabili che servono per definire la velocità di rotazione del motore stepper
float vel3;
float vel2;
long velS;
// inizializzo una variabile che utilizzo per definire il senso di rotazione del motore stepper
float dir;
// inizializzo due variabili che servono per definire la velocità di rotazione del motore CC
float vel;
int velCC;

// Setup del sistema
 void setup()
 {
   // Carico la libreria Serial per debug... decommentare la prossima riga in caso di utilizzo
   //Serial.begin(9600);
   // Definisco la modalità con cui utilizzo i ppin definiti in precedenza
   pinMode( dirCC1,OUTPUT );
   pinMode( dirCC2,OUTPUT );
   pinMode( pwmCC,OUTPUT );
   pinMode(steppin, OUTPUT);
   pinMode(stepdirpin, OUTPUT);
 }
 
//Creo una funzione per gestire il motore CC
void setspeedCC(void)
 {  
   //Definisco la velocità del motore CC
   vel=sin(millis()/3000.0)*1000; 
   // Definisco il senso di rotazione in base al verso della velocità e setto gli output in modo opportuno
   if (vel>=0){
   digitalWrite(dirCC1,LOW);
   digitalWrite(dirCC2,HIGH);
   }else{
   digitalWrite(dirCC1,HIGH);
   digitalWrite(dirCC2,LOW);
   }
   // Rimappo la velocità calcolata in modo che sia compatibile col comando analogWrite
   velCC=int(map(abs(vel),0,1000,254,255));
 // Scrivo il valore di velocità sul pin che gestisce il motore CC  
 analogWrite(pwmCC,velCC);
 }
 
//Creo una funzione per gestire il motore Stepper
 void setspeedStepper(void)
 {
   // definisco una velocità dipendente da millis
   vel3=(millis()*3.14)/(periodoS);
   // ne faccio il seno e moltiplico per 1000
   vel2=sin(vel3)*1000;
   // la direzione sarà in quadratura di fase con vel2 e avrà una frequenza doppia
   dir=sin((vel3+1.57)/2);
   // rimappo la velocità in modo da essere compatibile col comando analogWrite
   long int velS=map(int(abs(vel2+1000)),0,2000,0.5,15);
   // definisco, in base alla velocità, quanto dovrà durare l'intervallo tra uno step e l'altro
  step_delay = 60L * 1000L / 200 / velS/8;
  // se millis - il tempo a cui è stato eseguito l'ultimo passo è maggiiore dell'intervallo previsto allora...
  if (millis() - last_step_time >= step_delay) {
    // millis diventa il tempo a cui è stato eseguito l'ultimo passo
    last_step_time = millis();
    // setto il valore di stepdirpin in base alla valore di direzione calcolato sopra  
    if (dir >=0){
      digitalWrite(stepdirpin, HIGH);}
      else{
        digitalWrite(stepdirpin, LOW);}
        // se ha finito una rotazione completa (andata e ritorno) allora scelgo in modo random il periodo della rotazione successiva
        if(int(dir*10)==0){
      periodoS=float(random(3000, 7000));}
    // fai avanzare il motore stepper di uno step
    digitalWrite(steppin, HIGH);}
  // se non è ancora arrivato il momento non far avanzare il motore stepper  
  else{
    digitalWrite(steppin, LOW);}
 }
 
 // Fuzione principale di Arduino (viene ripetuta finchè non si interrompe l'alimentazione)
 void loop()
 {
 //Richiamo la funzione setspeedCC  
 setspeedCC();
 //Richiamo la funzione setspeedStepper
 setspeedStepper();
 }
