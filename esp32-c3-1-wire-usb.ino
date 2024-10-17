// Mesure simplement la température avec des sondes 1-wire DS18B20 et affiche le résultat sur la console série
// ATTENTION, il n'y a pas de couche WIFI dans ce projet, bien que cela utilise un esp32-c3-super-mini, mais utilisé seulement en mode Arduino
//
// ATTENTION, ce code a été testé sur un esp32-c3 super mini. Pas testé sur les autres boards !
//
#define zVERSION        "zf241017.1136"
#define zHOST           "esp32-c3-1-wire-usb"     // ATTENTION, tout en minuscule

int zDelay1Interval =   30000;                    // Délais en mili secondes pour la boucle loop

/*
Utilisation:

Astuce:

Afin d'économiser la résistance pull-up et de simplifier au maximum le câblage, 
j'utilise la pull up interne de l'esp32-c3 comme pull up et les deux pins 
adjacentes pour la masse et l'alimentation pour le DS18B20. Il faudra 
donc configurer ces pins en conséquence !


Installation:

Pour les esp32-c3 super mini, il faut:
 * choisir comme board ESP32C3 Dev Module
 * enabled USB CDC On Boot si on veut que la console serial fonctionne !
 * changer le schéma de la partition à Minimal SPIFFS (1.9MB APP with OTA/190kB SPIFFS)

Pour le 1-wire DS18B20 si ce n'est pas déjà fait, il faut installer ces deux libs:

https://github.com/PaulStoffregen/OneWire
https://github.com/milesburton/Arduino-Temperature-Control-Library


Sources:

https://grabcad.com/library/esp32-c3-supermini-1
https://forum.fritzing.org/t/need-esp32-c3-super-mini-board-model/20561
*/




// #define DEBUG true
// #undef DEBUG



// General
const int ledPin = 8;             // the number of the LED pin
const int buttonPin = 9;          // the number of the pushbutton pin


// Sonar Pulse
#include "zSonarpulse.h"


// Temperature sensor
#include "z1-Wire.h"


void setup() {
  // Pulse deux fois pour dire que l'on démarre
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); delay(zSonarPulseOn); digitalWrite(ledPin, HIGH); delay(zSonarPulseOff);
  digitalWrite(ledPin, LOW); delay(zSonarPulseOn); digitalWrite(ledPin, HIGH); delay(zSonarPulseOff);
  delay(zSonarPulseWait);

  // Start serial console
  Serial.begin(19200);
  Serial.setDebugOutput(true);       //pour voir les messages de debug des libs sur la console série !
  delay(3000);                          //le temps de passer sur la Serial Monitor ;-)
  Serial.println("\n\n\n\n**************************************\nCa commence !"); Serial.println(zHOST ", " zVERSION);

  // Configure les sondes de température 1-wire DS18B20
  initDS18B20Sensor();

  // go go go
  Serial.println("\nC'est parti !\n");
}


void loop() {
  // Envoie toute la sauce !
  // Lit les températures
  readSensor();

  // Délais non bloquant pour le sonarpulse et l'OTA
  zDelay1(zDelay1Interval);
}


// Délais non bloquant pour le sonarpulse et l'OTA
void zDelay1(long zDelayMili){
  long zDelay1NextMillis = zDelayMili + millis(); 
  while(millis() < zDelay1NextMillis ){
    // Un petit coup sonar pulse sur la LED pour dire que tout fonctionne bien
    sonarPulse();
  }
}

