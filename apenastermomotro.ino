#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Porta do pino de sinal do DS18B20 - PINO D4
#define ONE_WIRE_BUS D4

// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

// Armazena temperaturas minima e maxima
float tempMin = 999;
float tempMax = 0;
float temp; // Variavel que armazena a temperatura
float umidade; // Variavel que armazena a umidade
float tempC;


void mostra_endereco_sensor(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


void setup() {
  // put your setup code here, to run once:

  Serial.begin (115200); //configuração da UART


    sensors.begin();


      // Localiza e mostra enderecos dos sensores
  Serial.println("Localizando sensores DS18B20...");
  Serial.print("Foram encontrados ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sensores.");
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println("Sensores nao encontrados !"); 
  // Mostra o endereco do sensor encontrado no barramento
  Serial.print("Endereco sensor: ");
  mostra_endereco_sensor(sensor1);
  Serial.println();
  Serial.println();


}

void loop() {
  // put your main code here, to run repeatedly:

// Le a informacao do sensor
//-------------------------------------------------------------------------
  sensors.requestTemperatures();
  tempC = sensors.getTempCByIndex(0);
  // Atualiza temperaturas minima e maxima
  if (tempC < tempMin)
  {
    tempMin = tempC;
  }
  if (tempC > tempMax)
  {
    tempMax = tempC;
  }
  // Mostra dados no serial monitor
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Min : ");
  Serial.print(tempMin);
  Serial.print(" Max : ");
  Serial.println(tempMax);

}
