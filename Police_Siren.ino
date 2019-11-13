// Code by Ben Royans
// 13/11/2019
// Strobe Light

#define pinRed 9
#define pinBlue 11
#define pinGreen 10
#define rotation 0
#define sync 3
#define mode 2
#define buzzer 5

int currentMode = 0;
int numberOfModes = 2;


void setup() {
  // Set pins
  pinMode(pinRed, INPUT);
  pinMode(pinGreen, INPUT);
  pinMode(pinBlue, INPUT);
  pinMode(rotation, OUTPUT);
  pinMode(sync, INPUT);
  pinMode(mode, INPUT);
  pinMode(buzzer, OUTPUT);

  // Begin Serial output
  Serial.begin(9600);

  // Header
  Serial.println("\t\t\t****************************************************************");
  Serial.println("\t\t\t\t\t\tArduino Strobe Light\n");
  Serial.println("\t\t\t\t\t\tCode by Ben Royans");
  Serial.println("\t\t\t\t\t\t\t© 2019");
  Serial.println("\t\t\t****************************************************************\n\n");

  // Startup Tone
  Arpeggio(5, 500, 100, 2000, 100); 
}

void loop() 
{ 
  // Get switch state if pressed 
  UpdateSwitch();
  
  switch (currentMode)
  {      
     case 0:
      if (digitalRead(3) == 1)
      {  
        PoliceSiren1();
      }    
      break;  
      
    case 1:
      if (digitalRead(3) == 1)
      {  
        PoliceSiren2();
      }
      break;

    default:
      tone(buzzer, 100, 500);
      delay(500);
      tone(buzzer, 100, 500);
      delay(3500);      
      break;      
  }
}

void UpdateSwitch() 
{
  if (digitalRead(2) == 0)
  {    
    currentMode++;
    if (currentMode > numberOfModes)
    {
      currentMode = 0;
      PlayTone(3);
    }
    else 
    {
      PlayTone(2);
    }       
  }
}

void PlayTone(int t)
{
  switch (t)
  {
    case 1:
      tone(5, 2000, 100);
      delay(100);
      tone(5, 4000, 100); 
      break;

    case 2:
      tone(5, 6000, 100);
      delay(150);
      tone(5, 4000, 100);       
      break;

    case 3:
      tone(5, 6000, 100);
      delay(150);
      tone(5, 8000, 100); 
      break;

    default:
      Arpeggio(5, 200, 50, 800, 50);
      break;
  }
}

void PoliceSiren2() 
{
      RBG(255, 0, 0);
      delay(analogRead(rotation) / 2);
      RBG(0, 255, 0);
      delay(analogRead(rotation) / 2);
}

void PoliceSiren1() 
{
      for (int r = 0; r < 255; r++)
      {
        RBG(r, 0, 0);
        delay(1);
      }
      for (int r = 255; r > 0; r--)
      {
        RBG(r, 0, 0);
        delay(1);
      }
      for (int b = 0; b < 255; b++)
      {
        RBG(0, b, 0);
        delay(1);
      }
      for (int b = 255; b > 0; b--)
      {
        RBG(0, b, 0);
        delay(1);
      }
}

void RBG(int red, int blue, int green)
{   
   analogWrite(9, red);
   analogWrite(10, blue);
   analogWrite(11, green);
}

void Arpeggio(int numberOfNotes, int interval, int noteLength, int initialTone, int timeDelay)
{
  for (int i = 0; i < numberOfNotes; i++)
  {
    tone(buzzer, (initialTone + (interval * i)), noteLength);
    delay(timeDelay);
  }
}
