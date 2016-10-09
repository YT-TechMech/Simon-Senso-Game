int data_pin = 3;
int latch_pin = 2;
int clock_pin = 4;
int speaker = 5;
int button1 = 6;
int button2 = 7;
int button3 = 8;
int button4 = 9;
int led1 = 10;
int led2 = 11;
int led3 = 12;
int led4 = 13;

int sound[]={135,440,492,932};
int pause = 400;
int enter_pause = 20;
int lesspause = 10;
int lives = 3;
int number[]={192,249,164,176,153,146,130,248,128,144,64,121,36,48,25,18,2,120,0,16};
int melody[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
int led[]={10,11,12,13};
int level = 0;
int melodybox = 0;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

boolean stopp = true;
boolean allowbuttonpress = false;
//boolean correct = true;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(data_pin, OUTPUT);  //Data
pinMode(latch_pin, OUTPUT); //Latch
pinMode(clock_pin, OUTPUT); //Clock
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
pinMode(speaker, OUTPUT);
pinMode(button1, INPUT);
pinMode(button2, INPUT);
pinMode(button3, INPUT);
pinMode(button4, INPUT);
randomSeed(analogRead(0));


//Create random number:
newrandomnumbers();

//Level 0 Initialize:
writelevel();
}

void loop() // put your main code here, to run repeatedly:
{

if (stopp==true){
  for (int i=0;i<level+1;i++){
    toneandled(melody[i], pause, pause/2);
   }
   stopp = false;
   melodybox = 0; 
   allowbuttonpress = true;
}

 if (allowbuttonpress == true){
    buttonState1 = digitalRead(button1);
    buttonState2 = digitalRead(button2);
    buttonState3 = digitalRead(button3);
    buttonState4 = digitalRead(button4);

      if (buttonState1 == HIGH) {
        allowbuttonpress = false;
        checkifcorrect(0);
      }

      if (buttonState2 == HIGH) {
        allowbuttonpress = false;
        checkifcorrect(1);
      }

      if (buttonState3 == HIGH) {
        allowbuttonpress = false;
        checkifcorrect(2);
      }

      if (buttonState4 == HIGH) {
        allowbuttonpress = false;
        checkifcorrect(3);
      }

 }


}

void toneandled(int LED, int PAUSEONE, int PAUSETWO){
  digitalWrite(led[LED],HIGH);
  tone(speaker,sound[LED]);
  delay(PAUSEONE);
  digitalWrite(led[LED],LOW);
  noTone(speaker);
  delay(PAUSETWO);
}

void checkifcorrect(int lednumber){

  if (lednumber == melody[melodybox]){
      toneandled(lednumber, pause, enter_pause);

      if (melodybox == level){ //Abfrage ob sequenz vollständig
        sequencecorrect();  
      }
      melodybox++;
      allowbuttonpress = true;
  }
  
  else {
    sequencefalse();
  }
  

  
  
}
void sequencecorrect(){
  tone(speaker,475);
  delay(150);
  noTone(speaker);
  tone(speaker,475);
  delay(150);
  noTone(speaker);
  level++;
  writelevel();
  pause = pause - lesspause;
  delay(1000);
  stopp = true;
}

void sequencefalse(){
  lives = lives -1;
  for (int i = 1;i<4-lives;i++){
  tone(speaker,475);
  delay(150);
  noTone(speaker);
  tone(speaker,130);
  delay(650);
  noTone(speaker);
  delay(50);
  }
  delay(1000);
  if (lives == 0){
    level = 0;
    lives = 3;
    newrandomnumbers();
    writelevel();
    pause = 400;
    }
  stopp = true;
 }

 void writelevel(){
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, MSBFIRST,number[level]);
  digitalWrite(latch_pin, HIGH);
  delay (1000);
 }

 void newrandomnumbers(){
 randomSeed(analogRead(0));
 for (int i = 0; i<20;i++){
  melody[i]=random(0,4);

  }
 }

