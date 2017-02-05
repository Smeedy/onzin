#include <Adafruit_NeoPixel.h>

bool debug = false;
int LED = 13;

int LV_H = 17;
int LV_T = 16;
int LA_H = 14;
int LA_T = 15;

int RV_H = 8;
int RV_T = 6;
int RA_H = 5;
int RA_T = 4;

int DST_TRIG1 = 10;
int DST_ECHO1 = 11;

#define PIXELPIN       12
#define NUMPIXELS      1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXELPIN, NEO_GRB + NEO_KHZ800);

int rood = 0;
int groen = 0;
int blauw = 0;
float afstand;

void setup() {

  pinMode(LED, OUTPUT);     
  pinMode(PIXELPIN, OUTPUT);     

  pinMode(LV_H, OUTPUT);     
  pinMode(LV_T, OUTPUT);     
  pinMode(LA_H, OUTPUT);     
  pinMode(LA_T, OUTPUT);     

  pinMode(RV_H, OUTPUT);     
  pinMode(RV_T, OUTPUT);     
  pinMode(RA_H, OUTPUT);     
  pinMode(RA_T, OUTPUT);     

  pinMode(DST_TRIG1, OUTPUT);
  pinMode(DST_ECHO1, INPUT);

  Serial.begin(115200);

  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.show();

  Serial.println("hallo, je bent hier...");
  Serial.flush();

  digitalWrite(LED, LOW);
}


void loop() {
    
  doeAfstand();
  doePixel();
  doeWielen();

  delay(100);

}

void doeAfstand() {

  digitalWrite(DST_TRIG1, HIGH);
  delayMicroseconds(1000);
  digitalWrite(DST_TRIG1, LOW);

  unsigned long echotijd = pulseIn(DST_ECHO1, HIGH);
  afstand = (echotijd / 2.0) / 29.1;
  if (afstand >= 200){
    //Serial.println("Te ver weg");
  } else if (afstand <= 0) {
    //Serial.println("Te dichtbij");
  } else {
    //Serial.print(afstand);
    //Serial.println(" cm");
  }
  
}

void doePixel() {

  rood = 255 / ( afstand * 0.7 );
  groen = 255 * (afstand - 10)* 0.03;
  if (groen < 0) groen = 0;
  blauw = 0;

  pixels.setPixelColor(0, pixels.Color(rood, groen, blauw));
  pixels.show();
   
}


void doeWielen() {

  if (afstand >= 10) {
    vooruit();

  } else {
    stoppen();
    
  }
  

//  stoppen();
//  delay(1000);

//  achteruit();
//  delay(4000);
//
//  stoppen();
//  delay(1000);
}


void vooruit() {

  Serial.println("vooruit");
  if (!debug) {
    digitalWrite(LV_H, HIGH);
    digitalWrite(LA_H, HIGH);
    digitalWrite(RV_H, HIGH);
    digitalWrite(RA_H, HIGH);
  }
  
  digitalWrite(LED, HIGH);
}


void achteruit() {

  Serial.println("achter");
  if (!debug) {
    digitalWrite(LV_T, HIGH);
    digitalWrite(LA_T, HIGH);
    digitalWrite(RV_T, HIGH);
    digitalWrite(RA_T, HIGH);
  }
  
  digitalWrite(LED, HIGH);

}


void stoppen() {

  Serial.println("stoppen");
  if (!debug) {
    digitalWrite(LV_H, LOW);
    digitalWrite(LA_H, LOW);
    digitalWrite(LV_T, LOW);
    digitalWrite(LA_T, LOW);
  
    digitalWrite(RV_H, LOW);
    digitalWrite(RA_H, LOW);
    digitalWrite(RV_T, LOW);
    digitalWrite(RA_T, LOW);
  }

  digitalWrite(LED, LOW);

}


