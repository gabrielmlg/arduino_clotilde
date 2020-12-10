#include <Arduino.h>
#include <Adafruit_Sensor.h> // Biblioteca DHT Sensor Adafruit

#include <DHT.h>
#include <DHT_U.h>
#define DHTTYPE DHT11 // Sensor DHT11
#define DHTPIN 2 // Pino do Arduino no Sensor (Data)

DHT_Unified dht(DHTPIN, DHTTYPE); // configurando o Sensor DHT - pino e tipo
uint32_t delayMS = 500; // variável para atraso no tempo

int sensorUmidadeSolo = A0; // Sensor de umidade do solo pino A0 conectado no A0 do Arduino
int sensorUmidadeSolo2 = A1; // Sensor de chuva pino A0 conectado no A1 do Arduino
int valorLimiteUmidade = 500; // valor da tensão de comparação do sensor / valor máximo = 1024
int valorLimiteChuva = 500; // valor da tensão de comparação do sensor máximo = 1024
bool chuva; // condição de chuva
bool soloUmido; // condição de solo úmido

int valorSensorUmidadeSolo = 0;
float umidade1;
float valor_umidade1 = 0;

int valorSensorUmidadeSolo2 = 0;
float umidade2 = 0;
float valor_umidade2 = 0;

const float solo_max_1 = 0.0;
const float solo_min_1 = 4.1;
const float solo_max_2 = 3.3;
const float solo_min_2 = 0.0;

void setup() {
  pinMode(sensorUmidadeSolo, INPUT); // Sensor de umidade do solo - porta A0 é entrada
  pinMode(sensorUmidadeSolo2, INPUT);
  
  Serial.begin(9600); // Monitor console 9600 Bps

  dht.begin(); // inicializa a função
  sensor_t sensor;
}


void loop()
{

  delay(5000); // atraso de 5 segundos

  // Sensor umidade 1
  valorSensorUmidadeSolo = analogRead(sensorUmidadeSolo); // leitura do Sensor de umidade do solo
  umidade1 = (float(analogRead(valorSensorUmidadeSolo))/1023.0)*4.1; // ToDo: verificar a saida real analogica para o calculo de voltagem
  valor_umidade1 = map(umidade1, solo_min_1, solo_max_1, 100, 0);
  
  // Sensor umidade 2
  valorSensorUmidadeSolo2 = analogRead(sensorUmidadeSolo2); // leitura do Sensor de umidade do solo
  umidade2 = (float(analogRead(valorSensorUmidadeSolo2))/1023.0)*3.3;
  valor_umidade2 = map(umidade2, solo_min_2, solo_max_2, 100, 0);
  
  // Sensor temperatura
  sensors_event_t event; // inicializa o evento da Temperatura
  dht.temperature().getEvent(&event); // faz a leitura da Temperatura

  Serial.print("{'valorSensorUmidadeSolo': ");
  Serial.print(valorSensorUmidadeSolo); // valor do sensor de umidade do solo
  Serial.print(", 'umidade1': ");
  Serial.print(umidade1); // valor do sensor de umidade do solo
  Serial.print(", 'per_solo': ");
  Serial.print(valor_umidade1); // valor do sensor de umidade do solo

  Serial.print(", 'valorSensorUmidadeSolo2': ");
  Serial.print(valorSensorUmidadeSolo2); // valor do sensor de umidade do solo
  Serial.print(", 'umidade2': ");
  Serial.print(umidade2); // valor do sensor de umidade do solo
  Serial.print(", 'per_solo2': ");
  Serial.print(valor_umidade2); // valor do sensor de umidade do solo


  Serial.print(", 'temperatura ambiente': ");
  Serial.print(event.temperature); // valor do sensor de umidade do solo
  Serial.println("}");    

}