// broj oscilacija
const int osc = 10;
// trenutna i prethodna vrednost napona i njihova razlika
double V, old, out;
// prag za detekciju prolaska
double prag = 5;
// oznacava da smo prosli prvi element (false - nismo, true - jesmo)
bool prvi = false;
//pocetno vreme i krajnje vreme merenja
int vr_poc, vr_kraj;
// brojac oscilacija
int br = 0;
// razlika vremena od krajnjeg i pocetnog
double vreme;

//stanja
enum states {
  initialise, // ceka da pocne merenje
  measure, // meri vreme
  value // prikazuje rezultat
};

states stanje = initialise;

// pritiskom na dugme pocinjemo merenje
const int button_start = 7;
// pritiskom na dugme se ponavlja merenje
const int button_reset = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button_start, INPUT);
  pinMode(button_reset, INPUT);
}

void loop() 
{
  if (stanje == initialise)
  {
    Serial.println("iiiiiii");
    if (button_start == HIGH)
    {
      stanje = measure;
    }
  }
  if (stanje == measure)
  {
    Serial.println("mmmmmmm");
    V = analogRead(A1);
    // ako nemamo prvi ne racuna razliku
    // oduzimanje se vrsi zbog filtriranja srednje vrednosti
    if (prvi)
    {
      out = (V - old);
      //Serial.print("out = ");
      //Serial.println(out);
      if (out > prag)
      {
        if (br == 0)
        {
          vr_poc = millis();
        }
        if (br == 2*osc)
        {
          vr_kraj = millis();
          stanje = value;
          vreme = ((double)(vr_kraj - vr_poc))/1000;
        }
        br++;
      }   
      else
      {
        prvi = true;  
      }
      old = V;
    }
  }
  if (stanje == value)
  {
    Serial.println("vvvvvv");
    Serial.print("Vreme oscilacija je ");
    Serial.println(vreme);
    if (button_reset == HIGH)
    {
      stanje = initialise;
    }
  }
}
