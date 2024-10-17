// zf241017.1106

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
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);


// Temperature sensor DS18B20 initialising
void initDS18B20Sensor(){
    pinMode(gndPin, OUTPUT);   // gnd
    digitalWrite(gndPin, LOW);
    pinMode(pullupPin, INPUT_PULLUP);   // pull up
    pinMode(vccPin, OUTPUT );   // vcc
    digitalWrite(vccPin, HIGH);
    // Start the DS18B20 sensor
    sensors.begin();
}


RTC_DATA_ATTR float tempInternal1 = 0;
RTC_DATA_ATTR float tempInternal2 = 0;


// Lit les senseurs
void readSensor(){
    // lit la température interne
    sensorValue1 = temperatureRead();
    sensorValue1 = sensorValue1 - 8.0;        // Enlève des ° en trop, je ne sais pas pourquoi ? zf240526.1142, zf240530.0908

    // moyenne glissante
    sensorValue1 = (sensorValue1 + tempInternal1 + tempInternal2) / 3;
    tempInternal1 = tempInternal2;
    tempInternal2 = sensorValue1;

    // lit la température du DS18B20
    sensors.requestTemperatures(); 
    sensorValue5 = sensors.getTempCByIndex(0);
}



// Data wire is plugged TO GPIO 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Number of temperature devices found
int numberOfDevices;

// We'll use this variable to store a found device address
DeviceAddress tempDeviceAddress; 

void setup(){
  // start serial port
  Serial.begin(115200);
  
  // Start up the library
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

void loop(){ 
  sensors.requestTemperatures(); // Send the command to get temperatures
  
  // Loop through each device, print out temperature data
  for(int i=0;i<numberOfDevices; i++){
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)){
      // Output the device ID
      Serial.print("Temperature for device: ");
      Serial.println(i,DEC);
      // Print the data
      float tempC = sensors.getTempC(tempDeviceAddress);
      Serial.print("Temp C: ");
      Serial.print(tempC);
      Serial.print(" Temp F: ");
      Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
    }
  }
  delay(5000);
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++){
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}

