///////////////////Stoppuhr_Display////////////////////////////

//Taster werden als die Pins 16,17 und 18 deklariert.
#define Taster_Start 16
#define Taster_Stopp 17       
#define Taster_Reset 18

//Bibliotheken für die Displaynutzung werden eingebunden.
#include <Wire.h>
#include <SSD1306Wire.h>

//Variablendeklaration zur Zeit-Berechnung.
int Sekunden;
int Minuten;
int Stunden;
unsigned long StartZeit;
unsigned long AktuelleZeit;
boolean Merker=0;

SSD1306Wire anzeige(0x3C, 21, 22);      //OLED-Display wird eingebunden. (mit "anzeige" Variable)

void setup() {
  anzeige.init();                     //Display wird intitialisiert.
  anzeige.clear();
  anzeige.setFont(ArialMT_Plain_16);  //Display wird formatiert(festlegen von Schriftart und Farben)
  anzeige.invertDisplay();
  Reset();                            //Reset-Funktion wird aufgerufen um Display zu beschreiben.
}

//Stoppuhr-Funktion:
void Stoppuhr()
{
  //Die Zeiten werden berechnet.
  Sekunden = (60 + AktuelleZeit / 1000)% 60;
  Minuten = (60 + AktuelleZeit / 60000)% 60;
  Stunden = (25 + AktuelleZeit / 3600000)% 25;
  //Stringumwandlung, da mit Integer nicht geschrieben werden kann.
  String Stunden_zahl = String(Stunden,DEC);
  String Minuten_zahl = String(Minuten,DEC);
  String Sekunden_zahl = String(Sekunden,DEC);
  //Display Ausgabe:
  anzeige.clear();
  anzeige.drawString(0,0,"Stoppuhr");
  anzeige.drawVerticalLine(0,10,100);
  anzeige.drawString(5,20,Stunden_zahl);
  anzeige.drawString(15,20,"h");
  anzeige.drawString(30,20,Minuten_zahl);
  anzeige.drawString(40,20,"m");
  anzeige.drawString(55,20,Sekunden_zahl);
  anzeige.drawString(75,20,"s");
  anzeige.display();
}

//Reset-Funktion:
void Reset()
{
  //Mit Reset wird alles auf "0" gesetzt.
  Sekunden=0;
  Minuten=0;
  Stunden=0;
  Merker=0;
  anzeige.clear();
  anzeige.drawString(0,0,"Stoppuhr");
  anzeige.drawVerticalLine(0,10,100);
  anzeige.drawString(5,20,"0");
  anzeige.drawString(15,20,"h");
  anzeige.drawString(30,20,"0");
  anzeige.drawString(40,20,"m");
  anzeige.drawString(55,20,"00");
  anzeige.drawString(75,20,"s");
  anzeige.display();
}


void loop() {
  
//Wenn der Start-Taster gedrückt wird, nimmt die Variable "StartZeit" millis() an.
//Außerdem wird die Boolsche Variable "Merker" auf 1 also True gesetzt.
if (digitalRead(Taster_Start)==HIGH)
{
  StartZeit=millis();
  Merker=1;
  delay(200);
}
//Wird der Taster nicht gedrückt, wird die aktuelle Zeit berechnet: "millis" - "StartZeit"
else
{
  AktuelleZeit=millis() - StartZeit; 
}

//Wird der Reset Taster Gedrückt, wird auch die Reset-Funktion ausgeführt.
if (digitalRead(Taster_Reset)==HIGH)
{
  delay(200);
  Reset();
}

//Während der Merker auf 1 steht wird die Stoppuhr ausgeführt.
while (Merker==1)
{
  Stoppuhr();
  //Wird aber währenddessen der Stopp-Taster gedrückt, so wird die Schleife durch "break" abgebrochen
  //und der Merker wird auf 0 also False gesetzt.
  if (digitalRead(Taster_Stopp)==HIGH)
  {
    delay(200);
    Merker=0;
    break;
  }
  break;
}
}
