#include <LinkedList.h>

// ogranicenje velicine liste (ako je 0, lista nema ogranicenje)
int maxSize = 0;
// trenutna i prethodna vrednost napona i njihova razlika
double V, old, out;
// prag za detekciju prolaska
double prag = 10;
// oznacava da smo prosli prvi element (false - nismo, true - jesmo)
bool prvi = false;
// pomocna promenljiva za racunanje poluperiode, duzina trenutne poluperiode i periode
unsigned long tp, halfperiod, period;
// pocetak merenja
bool start = false;
// dodaje periodu u listu
bool dodaj = false;
// lista perioda
LinkedList<float> lista;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() 
{
  V = analogRead(A1);
  // ako nemamo prvi ne racuna razliku
  // oduzimanje se vrsi zbog filtriranja srednje vrednosti
  if (prvi)
  {
    out = (V - old);
  }
  else
  {
    prvi = true;  
  }
  //Serial.println(out);
  if (out>prag)
  {
    //Serial.println(3);
    if (start)
    {
      // poluperioda oscilacije, normalizovana na sekunde
      halfperiod = (millis()-tp)/1000;
      halfperiod = (float) halfperiod;
      if (dodaj)
      {
        period += halfperiod;
        lista.add(period);
        // provera da li postoji ogranicenje
        if (maxSize > 0)
        {
          //provera da li smo presli ogranicenje
          if (lista.size() > maxSize)
          {
            // ako jesmo, brisemo prvi clan
            lista.remove(0);
          }
        }
        dodaj = false;
      }
      else
      {
        period = halfperiod;
        dodaj = true;
      }
      tp = millis();
    }
    // inicijalizacija pocetnog vremena
    else
    {
      start = true;
      tp = millis();
    }
  }
  else 
  {
    //Serial.println(0);
  }
  old = V;
}


// merenje srednje vrednosti, svih clanova niza
float srvr(LinkedList<float> lista)
{
  float sum = 0;
  int kraj = lista.size() - 1;
  for (int i = 0; i < kraj; i++) {
    sum += lista.get(i);
  }
  sum = sum/kraj;
}
