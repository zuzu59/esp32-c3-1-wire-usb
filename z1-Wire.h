// zf241017.1534

// lib pour la sonde de température 1-wire DS18B20

// Sources:
// https://randomnerdtutorials.com/esp32-ds18b20-temperature-arduino-ide/

// Temperature sensor DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>

const int vccPin = 1;       // the number of the VCC pin
const int pullupPin = 2;    // the number of the PULLUP pin
const int oneWireBus = 3;   // GPIO where the DS18B20 is connected to
const int gndPin = 4;       // the number of the GND pin

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Number of temperature devices found
int numberOfDevices;

// We'll use this variable to store a found device address
DeviceAddress tempDeviceAddress; 


// function to print a device address
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++){
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}


// Temperature sensor DS18B20 initialising
void initDS18B20Sensor(){
  pinMode(gndPin, OUTPUT);   // gnd
  digitalWrite(gndPin, LOW);
  pinMode(pullupPin, INPUT_PULLUP);   // pull up
  pinMode(vccPin, OUTPUT );   // vcc
  digitalWrite(vccPin, HIGH);
  // Start the DS18B20 sensor
  sensors.begin();

  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");

  // Loop through each device, print out address
  for(int i=0;i<numberOfDevices; i++){
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)){
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();
    } else {
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }
  }

}


// Lit les senseurs
void readSensor(){
  sensors.requestTemperatures(); // Send the command to get temperatures
  // Loop through each device, print out temperature data
  for(int i=0;i<numberOfDevices; i++){
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)){
      // Graphe sur l'Arduino IDE les courbes des mesures
      Serial.print("sensor");
      Serial.print(i,DEC);
      Serial.print(":");
      float tempC = sensors.getTempC(tempDeviceAddress);
      Serial.print(tempC);
      Serial.print(",");
    }
  }
  Serial.println("");
}

