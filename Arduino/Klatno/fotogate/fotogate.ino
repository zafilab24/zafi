// ogranicenje velicine liste
const int maxSize = 10;
// trenutna i prethodna vrednost napona i njihova razlika
double V, old, out;
// prag za detekciju prolaska
double prag = 5;
// oznacava da smo prosli prvi element (false - nismo, true - jesmo)
bool prvi = false;
// pomocna promenljiva za racunanje poluperiode
unsigned long tp;
// duzina trenutne poluperiode i periode
double halfperiod, period;
// pocetak merenja
bool start = false;
// dodaje periodu u listu
bool dodaj = false;
// lista perioda
double lista[maxSize];
// broj trenutnog elementa liste
int br = 0;


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
    //Serial.print("out = ");
  }
  else
  {
    prvi = true;  
  }

  
  if (out > prag)
  {
    Serial.print("out = ");
    Serial.println(out);
    
    if (start)
    {
      Serial.print("halfperiod = ");
      Serial.println(halfperiod);
      
      // poluperioda oscilacije, normalizovana na sekunde
      halfperiod = (double)(micros()-tp);
      halfperiod = halfperiod/1000000;
      if (dodaj)
      {
        period += halfperiod;
        lista[br] = period;
        br++;
        // provera da li stigli do kraja niza
        if (br == maxSize)
        {
          // vracamo se na pocetak i overwriteujemo vrednosti
          br = 0;
        }
        dodaj = false;
      }
      else
      {
        period = halfperiod;
        dodaj = true;
      }

      Serial.print("tp = ");
      Serial.println(tp);
      tp = micros();
    }
    // inicijalizacija pocetnog vremena
    else
    {
      start = true;
      tp = micros();
    }
  }

  //float srednja_vrednost = srvr(lista);
  //Serial.println(srednja_vrednost);
  old = V;
}


// merenje srednje vrednosti, svih clanova niza
float srvr(double lista[])
{
  double sum = 0;
  int notzero = 0;
  for (int i = 0; i < maxSize; i++) {
    notzero++;
    sum += lista[i];
  }
  sum = sum/notzero;
}
