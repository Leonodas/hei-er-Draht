//////////Fehleranzeige////////////////

#define Draht 27
#define Buzzer 4
#define LED_Rot 19
#define LED_Gelb 21
#define LED_Gruen 22

int z;

void setup() {
  pinMode(Draht, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(LED_Rot, OUTPUT);
  pinMode(LED_Gelb, OUTPUT);
  pinMode(LED_Gruen, OUTPUT);
  z = 0;
}

void Ton()
{
  {
    digitalWrite(Buzzer, HIGH);
    delay(250);
    digitalWrite(Buzzer, LOW);
    delay(250);
  }
}

void Alarm()
{
  int i;
  for (i = 1; i <= 4; i++)
  {
    digitalWrite(LED_Gruen, HIGH);
    digitalWrite(LED_Gelb, HIGH);
    digitalWrite(LED_Rot, HIGH);
    Ton();
    delay(500);
    digitalWrite(LED_Gruen, LOW);
    digitalWrite(LED_Gelb, LOW);
    digitalWrite(LED_Rot, LOW);
    Ton();
    delay(500);
  }
}

void loop() {
  //Alle LEDs zu Beginn anschalten:
  if (z == 0)
  {
    digitalWrite(LED_Gruen, HIGH);
    digitalWrite(LED_Gelb, HIGH);
    digitalWrite(LED_Rot, HIGH);
  }

  //Wenn der Draht berührt wird, erhöht sich der Zähler um 1.
  if (digitalRead(Draht) == HIGH)
  {
    z = z + 1;
    Ton();
  }

  //Grüne LED bei Berührung aus. (erstes Leben verloren)
  if (z == 1)
  {
    digitalWrite(LED_Gruen, LOW);
  }

  //Gelbe LED bei Berührung aus. (zweites Leben verloren)
  if (z == 2)
  {
    digitalWrite(LED_Gelb, LOW);
    digitalWrite(LED_Gruen, LOW);
  }

  //Rote LED bei Berührung aus. (drittes Leben verloren)(Spiel aus).
  if (z == 3)
  {
    digitalWrite(LED_Rot, LOW);
    digitalWrite(LED_Gelb, LOW);
    digitalWrite(LED_Gruen, LOW);
    delay(500);
    z=4;
    Alarm();
  }

  //Reset in Ausgangsstellung
  if (z > 3)
  {
    z = 0;
    digitalWrite(LED_Gruen, HIGH);
    digitalWrite(LED_Gelb, HIGH);
    digitalWrite(LED_Rot, HIGH);
  }
}
