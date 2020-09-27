  
  //4Thermo_Arduino Program
  //Program for read data off 4 adafruit Max31856 and print the data on an SD card reader
  //The program uses Pins 2,3,4,5,6,7,8 Digital pins for the thermocouples
  //Pin 10,11,12,13 are for the SD card reader
  //Uses 5 volt supply
  
  //Librarys
  #include <Adafruit_MAX31856.h>
  #include <SD.h>
  //File Initiallization
  File ThermoData;

  //Initiallizing Ports for Thermocouples: CS, DI, DO, CLK
  Adafruit_MAX31856 maxthermo1 = Adafruit_MAX31856(2, 6, 7, 8);
  Adafruit_MAX31856 maxthermo2 = Adafruit_MAX31856(3, 6, 7, 8);
  Adafruit_MAX31856 maxthermo3 = Adafruit_MAX31856(4, 6, 7, 8);
  Adafruit_MAX31856 maxthermo4 = Adafruit_MAX31856(5, 6, 7, 8);
  


void setup() {
  //Begins the thermo boards to get data
  maxthermo1.begin();
  maxthermo2.begin();
  maxthermo3.begin();
  maxthermo4.begin();
//Pin and SD pin identification   
  pinMode(10, OUTPUT);
  SD.begin(10);
//Sets Thermocouple type
  maxthermo1.setThermocoupleType(MAX31856_TCTYPE_K);
  maxthermo2.setThermocoupleType(MAX31856_TCTYPE_K);
  maxthermo3.setThermocoupleType(MAX31856_TCTYPE_K);
  maxthermo4.setThermocoupleType(MAX31856_TCTYPE_K);

//Setting lower and upper limit for cold junction and thermocouple
  maxthermo1.setColdJunctionFaultThreshholds(-.127,127);
  maxthermo1.setTempFaultThreshholds(-4096, 4096);
  maxthermo2.setColdJunctionFaultThreshholds(-.127,127);
  maxthermo2.setTempFaultThreshholds(-4096, 4096);
  maxthermo3.setColdJunctionFaultThreshholds(-.127,127);
  maxthermo3.setTempFaultThreshholds(-4096, 4096);
  maxthermo4.setColdJunctionFaultThreshholds(-.127,127);
  maxthermo4.setTempFaultThreshholds(-4096, 4096);

//Creating and seting up the Thermo file  
  ThermoData = SD.open("Thermo.txt", FILE_WRITE);
  ThermoData.println("Thermo Data: Time, 1, 2, 3, 4");
  ThermoData.close();
//Begins serial output at 9600 baud
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Opens the file for writing
  ThermoData = SD.open("Thermo.txt", FILE_WRITE);
  //Prints time in milliseconds
  ThermoData.print(millis());
  ThermoData.print("            ");

  //Temp for Thermocouple 1 (C)
  ThermoData.print(maxthermo1.readThermocoupleTemperature());
  ThermoData.print("            ");
  Serial.print(maxthermo1.readThermocoupleTemperature());
  Serial.print(" Time:");
  Serial.print(millis());
  Serial.print("ms | ");
  //Temp for Thermocouple 2 (C)
  ThermoData.print(maxthermo2.readThermocoupleTemperature());
  ThermoData.print("            ");
  Serial.print(maxthermo2.readThermocoupleTemperature());
  Serial.print(" Time:");
  Serial.print(millis());
  Serial.print("ms | ");
  //Temp for Thermocouple 3 (C)
  ThermoData.print(maxthermo3.readThermocoupleTemperature());
  ThermoData.print("            ");
  Serial.print(maxthermo3.readThermocoupleTemperature());
  Serial.print(" Time:");
  Serial.print(millis());
  Serial.print("ms | ");
  //Temp for Thermocouple 4 (C)
  ThermoData.println(maxthermo4.readThermocoupleTemperature());
  Serial.print(maxthermo4.readThermocoupleTemperature());
  Serial.print(" Time:");
  Serial.print(millis());
  Serial.println("ms | ");
  //Delay for each data point
  delay(500);


  //File Close
  ThermoData.close();
}
