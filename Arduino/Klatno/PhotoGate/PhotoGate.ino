/*
  HARDVER

  Button pinovi (napajanje, masa, signal)
  Photoresistor pinovi (napajanje, masa, signal)
  
*/

#include <LiquidCrystal.h>

const int button_start = 7;                                       //  dugme za pokretanje merenja kao i ponavljanje merenja
const int button_inc = 6;                                         //  dugme za namestanje broja oscilacija

double V, out, old, vreme;                                        //  trenutna vrednost, prethodna vrednost, razlika trenutne i prethodne napona sa senzora, vreme trajanje oscilacija
bool prvi, uslov = true, button_down = true;                      //  prag za detektovanje oscilacije, broj oscilacija (defaultno postavljeno na 20), brojac
int prag = 10, osc = 20, br = 0;
unsigned long vreme_poc, vreme_kraj;                              //  pocetno i krajnje vreme merenja (funkcija millis() trazi da tip podatka bude unsigned long)

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

enum states {                                                     //  3 stanja koda, za namestanje broja oscilacija, za merenje, i za prikaz rezultata
  initialise,
  measure,
  value
};

states stanje = initialise;

void setup() {
  pinMode(button_start, INPUT);
  pinMode(button_inc, INPUT);

  Serial.begin(9600);

  lcd.begin(16, 2);

  //Serial.println("Pritisnite START dugme za pocetak.");
  lcd.setCursor(0,1);
  lcd.print("OK za pocetak");
}

void loop() {
  if (stanje == initialise) 
  {
    //Serial.print("Broj oscijacija ");
    lcd.setCursor(0, 0);
    lcd.print("Br oscilacija");
    //Serial.println(osc);
    lcd.setCursor(14, 0);
    lcd.print(osc);
    if ((digitalRead(button_inc) == HIGH) && button_down)         //  ako je dugme za namestanje broja oscilacija pritisnuto povecaj broj oscilacija (dodatan uslov1 kako ne bi se povecao broj oscilacija vise nego potrebno)
    {
      button_down = false;
      if (osc == 60)
      {
        osc = 20;
      }
      else
      {
        osc += 5;
      }
    }
    else
    {
      if (digitalRead(button_inc) == LOW)                         //  resetuje se uslov1
      {
        button_down = true;
      }
    }
    if (digitalRead(button_start) == HIGH)                        //  ako je START dugme pritisnuto predji u merenje
    {
      stanje = measure;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Merenje");
    }
  }
  if (stanje == measure) 
  {
    //Serial.println("mmm");
    V = analogRead(A0);
    Serial.println(out);
    if (prvi)                                                     //  ako je prva iteracija ne moze da racuna razliku
    {
      out = old - V;
      if ((out > prag) && uslov)                                  //  ako je razlika signala veca od praga detektuj objekat (dodatan uslov2 da se za jednu detekciju ne procita dva dogadjaja)
        {
        uslov = false;
        if (br == 0) 
        {
          vreme_poc = millis();                                   //  ako je prva detekcija pocni da meris vreme
        }
        if (br == 2*osc)
        {
          vreme_kraj = millis();                                  //  ako je poslednja detekcija izmeri vreme, odredi proteklo vreme i udji u sledece stanje
          vreme = ((double)(vreme_kraj - vreme_poc))/1000;
          stanje = value;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Vreme je ");
          lcd.setCursor(9,0);
          lcd.print(vreme);
        }
        br++;
      }
      if (out < (-prag))                                          // resetuje se uslov2
      {
        uslov = true;
      }
    }
    else
    {
      prvi = true;
    }
    old = V;
  }
  if (stanje == value)                                            //  prikazi vreme, ako se pritisne dugme za ponovno merenje resetuj sve pocetne vrednosti i predji u stanje inicijalizacije
  {
    //Serial.print("Vreme je ");
    //Serial.println(vreme);
    if (digitalRead(button_start) == HIGH)
    {
      prvi = false;
      uslov = true;
      br = 0;
      stanje = initialise;
      //Serial.println("Pritisnite START dugme za pocetak.");
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("OK za pocetak");
    }
  }
}
