// Define the LED digit patters, from 0 - 9
// Note that these patterns are for common anode displays
// For common anode displays, change the 1's to 0's and 0's to 1's
// 1 = LED on, 0 = LED off, in this order:
byte seven_seg_digits[10][7] = { { 0,0,0,0,0,0,1 },  // = 0
                                 { 1,0,0,1,1,1,1 },  // = 1
                                 { 0,0,1,0,0,1,0 },  // = 2
                                 { 0,0,0,0,1,1,0 },  // = 3
                                 { 1,0,0,1,1,0,0 },  // = 4
                                 { 0,1,0,0,1,0,0 },  // = 5
                                 { 0,1,0,0,0,0,0 },  // = 6
                                 { 0,0,0,1,1,1,1 },  // = 7
                                 { 0,0,0,0,0,0,0 },  // = 8
                                 { 0,0,0,1,1,0,0 }   // = 9
                                                           };                    
int ledpin1 = 10;
//int ledpin2 = 11;
int speakerPin = 11;

void setup() 
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  writeDot(HIGH);  // start with the "dot" off
  pinMode(ledpin1, OUTPUT);
  //pinMode(ledpin2,OUTPUT);
  
  pinMode(speakerPin, OUTPUT);
  myloop();
}

void writeDot(byte dot) 
{
  digitalWrite(9, dot);
}

int value;
int pin[] = { A5, A4, A3, A2, A1, A0, 12, 13 };
int i,y,z;
float x;

int read()
{
  int val = 0;
  for (i = 0; i < 8; i++)
  {
    value = digitalRead(pin[i]);
    Serial.println(value);
    Serial.println("value in the loop");
    val = val*2 + value;
  }
  x = (40.0 * val) / 255.0;
  Serial.println(val);
  Serial.println("value");
  Serial.println(x);
  Serial.println("x");
  y = int(x);
  Serial.println(y);
  Serial.println("y");
  if ((x-y)>0.5)
    return y+1;
  else 
     return y;
}


void sevenSegWrite(byte digit)
{
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
    }

}

int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone); 
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

int k=0;
void myloop() { 
  for (k=0;k<100;)
  {
    z = read();
    int tens = z/10;
    digitalWrite(ledpin1, HIGH);
    sevenSegWrite(z/10);
    delay(50);
    digitalWrite(ledpin1, LOW);
    sevenSegWrite(z%10); 
    if(z/10 >= 0 && z%10>=7)
  {
     for (int i = 13; i < length; i++)
    {
      
    if (notes[i] == ' ') {
      delay(beats[i] * tempo);
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    delay(tempo / 2);
     z = read();
          int tens = z/10;
          digitalWrite(ledpin1, HIGH);
          sevenSegWrite(z/10);
          delay(5);
          digitalWrite(ledpin1, LOW);
          sevenSegWrite(z%10);   
}
  }
  
}
}

void loop(){}
