//Programme capteur poussiere avant essaie TIMER

// This #include statement was automatically added by the Particle IDE.
#include "neopixel/neopixel.h"
#include "SparkCorePolledTimer/SparkCorePolledTimer.h"
#include "Particle.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D6
#define PIXEL_COUNT 13
#define PIXEL_TYPE WS2812B
#define LOW_THRESHOLD 800 //minimum pota = 0 maximum pota = 4095
#define HIGH_THRESHOLD 2000

#define UNDEFINED_STATE  0xFFFFU
#define SONG_FALSE 0U
#define SONG_NOTE_0_STATE 1U
#define SONG_NOTE_1_STATE 2U
#define SONG_NOTE_2_STATE 3U
#define SONG_NOTE_3_STATE 4U
#define SONG1_NOTE_0_STATE 5U
#define SONG1_NOTE_1_STATE 6U
#define SONG1_NOTE_2_STATE 7U
#define SONG1_NOTE_3_STATE 8U


// Notes pour buzzeur
const int C = 1046;
const int D = 1175;
const int E = 1319;
const int F = 1397;
const int G = 1568;
const int A = 1760;
const int B = 1976;
const int C_1 = 2093;
const int D_1 = 2349;

//Déclaration variables
int buzzerPin = D1;
int dustPin=A0;
double dustVal=0.0;
float etat = UNDEFINED_STATE;
int ledPower=D0;
int delayTime=280;
int delayTime2=40;
double valDust = 0;
float coef = 0.95;

SparkCorePolledTimer Timer1(1000);  //Create a timer object and set it's timeout in milliseconds
void TimerSong(void);   //Prototype for timer callback method
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {
    
    Serial.begin(9600);
    pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as an OUTPUT
    pinMode(ledPower,OUTPUT);
    pinMode(dustPin, INPUT);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    Spark.variable("dustval", &dustVal, DOUBLE);
    Serial.println("Setup Executé");
}
 

 void colorstrip(uint8_t r, uint8_t g, uint8_t b)
 {
    float StepDelay = 1.7; // ms for a step delay on the lights
    int brightness = 10;
    
    // Animation Led montante
    for (brightness = 10; brightness <= 255; brightness++) {
        for (int ledNumber = 0; ledNumber < PIXEL_COUNT; ledNumber++) 
        {
            strip.setPixelColor(ledNumber, r, g, b); //Transmet au LED , la valeur de RGB définit dans la fonction readSensor() 
        }
        strip.setBrightness(brightness); // Récupére la luminosité
        strip.show();  
        delay(StepDelay);
    }
        
    // Animation Led descendant
    for (brightness = 255; brightness >=10; brightness--) {
        for (int ledNumber = 0; ledNumber < PIXEL_COUNT; ledNumber++)
        {
            strip.setPixelColor(ledNumber, r, g, b);
        }
        strip.setBrightness(brightness); // Récupére la luminosité
        strip.show();    
        delay(StepDelay);
    }
}


void TimerSong(void) {  // Handler for the timer, will be called automatically

   // Etape d'une melody lors de l'appel de la fonction de callbak : OnTimer
   // Machine a état mise à jour pour appel des tonalité
   
   if (etat == SONG_NOTE_0_STATE)
    {
        noTone(buzzerPin);
        etat = SONG_NOTE_1_STATE;
        // Joue apres 1s
        Timer1.Reset();

    }
   
    else if (etat == SONG_NOTE_1_STATE)
   {
       tone(buzzerPin, E);
       etat = SONG_NOTE_2_STATE;
       // Joue après 1s
       Timer1.Reset();
   }
   
    else if(etat == SONG_NOTE_2_STATE)
    {
       noTone(buzzerPin);
       etat = SONG_NOTE_3_STATE;
       // Joue après timer s
       Timer1.Reset();
    }
    
    else if(etat == SONG_NOTE_3_STATE)
    {
       tone(buzzerPin, E);
       etat = UNDEFINED_STATE;
       // Stop timer
       Timer1.SetCallback(NULL); // Met la callback a NULL est donc arrete de passez dans les différents états de la machine
    }
    
    
    // Fin premiere melody debut 2nd melody
    else if (etat == SONG1_NOTE_0_STATE)
    {
        noTone(buzzerPin);
        etat = SONG1_NOTE_1_STATE;
    }
   
    else if (etat == SONG1_NOTE_1_STATE)
   {
       tone(buzzerPin, C);
       etat = SONG1_NOTE_2_STATE;
       // Joue après 1s
       Timer1.Reset();
   }
   
    else if(etat == SONG1_NOTE_1_STATE)
    {

       noTone(buzzerPin);
       etat = SONG1_NOTE_2_STATE;
       // Joue après 1s
       Timer1.Reset();
    }
    
    else if(etat == SONG1_NOTE_2_STATE)
    {
       tone(buzzerPin, C);
       etat = SONG1_NOTE_3_STATE;
       // Joue après timer 1s
       Timer1.Reset();
    }
    
    else if(etat == SONG1_NOTE_3_STATE)
    {
       noTone(buzzerPin);
       etat = UNDEFINED_STATE;
       // Stop du timer
       Timer1.SetCallback(NULL); // Met la callback a NULL est donc arrete de passez dans les différents états de la machine
    }

    else 
    {
	    Serial.println("ERROR STATE");// Renseigne si aucun états ne correspond sur port serie
    }
}


void readSensor(void)
{   
    digitalWrite(ledPower,LOW); // Power on the LED
    delayMicroseconds(delayTime);
    float val=(float)analogRead(dustPin); // Read the dust value via pin 5 on the sensor
    digitalWrite(ledPower,HIGH); // Turn the LED off
    

    dustVal = dustVal*coef + val*(1.0-coef); 
    // Serial.println(dustVal); // Affiche la valeur apres filtrage du capteur sur le port série   
  
  
    if(dustVal<LOW_THRESHOLD)
    {
        noTone(buzzerPin);
        colorstrip (0, 0, 255); // Color strip in blue: air quality is good
        Timer1.Reset();
    }
    
    else if(dustVal<HIGH_THRESHOLD)
    {
        Serial.println(etat);
        colorstrip(255,255,0);  // Color strip in yellow: air quality is acceptable
        tone(buzzerPin, E);
        // Joue après 1s
        etat = SONG_NOTE_0_STATE;
        Timer1.SetCallback(TimerSong); // Appel la fonction de callBack  pour jouer la 1ère melody avertissement
    }
    
    else 
    {
        colorstrip(255,0,0); // Color strip in red: air quality is bad
        tone(buzzerPin, C);
        etat = SONG1_NOTE_0_STATE;
        Timer1.SetCallback(TimerSong); // Appel la fonction de callBack  pour jouer la 2nd melody alarm
    }
}

void loop() {
    
    Timer1.Update(); // Appel la fonction de callBack si != NULL toutes les ("Temps Timer") 500 ms
    readSensor(); // Effectue continuellement une lecture du capteur après la fin de chaque animation
    //Particle.variable("dustVal", dustVal); // Permet de récupérer la valeur de dustVal (Taux de poussière après filtrage sur une page web
}

