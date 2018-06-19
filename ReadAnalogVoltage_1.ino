#include <DS18B20.h>
#include <OneWire.h>

/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5 / 1023.0);
  float odczyt = voltage * 100.;
  // print out the value you read:
  
  Serial.println(odczyt);
}

*/
const byte ONEWIRE_PIN = 2;

OneWire onewire(ONEWIRE_PIN);
byte address[8] = {0x28, 0x83, 0xFF, 0xE2, 0x7, 0x0, 0x0, 0x50};
DS18B20 sensors(&onewire);

void setup()
{
  while(!Serial);
  Serial.begin(9600);

  sensors.begin();
  sensors.request(address);
}

void loop()
{
    if (sensors.available())
  {

    float temperature = sensors.readTemperature(address);
    Serial.print(temperature);
    Serial.println(F(" 'C"));
    float tempfahrenheit = 9*temperature/5.+32.;
    Serial.print(tempfahrenheit);
    Serial.println(F(" F"));
    float tempkelwin = temperature+273.15;
    Serial.print(tempkelwin);
    Serial.println(F(" K"));
    Serial.println((""));
    sensors.request(address);
 
 }
}

