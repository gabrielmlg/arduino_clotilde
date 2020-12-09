#include <Arduino.h>
#include <Adafruit_Sensor.h> // Biblioteca DHT Sensor Adafruit

#include <DHT.h>
#include <DHT_U.h>
#define DHTTYPE DHT11 // Sensor DHT11
#define DHTPIN 2 // Pino do Arduino no Sensor (Data)

DHT_Unified dht(DHTPIN, DHTTYPE); // configurando o Sensor DHT - pino e tipo
uint32_t delayMS = 500; // variável para atraso no tempo

// Exemplo 13 – Arduino Sensor de umidade do solo e Sensor de chuva
// Apostila Eletrogate - KIT MAKER
// Gustavo Murta
int sensorUmidadeSolo = A0; // Sensor de umidade do solo pino A0 conectado no A0 do Arduino
int sensorChuva = A5; // Sensor de chuva pino A0 conectado no A1 do Arduino
int sensorUmidadeSolo2 = A1; // Sensor de chuva pino A0 conectado no A1 do Arduino
int portaRele = 4; // porta de controle do relé conectada no D4 do Arduino
int valorLimiteUmidade = 500; // valor da tensão de comparação do sensor / valor máximo = 1024
int valorLimiteChuva = 500; // valor da tensão de comparação do sensor máximo = 1024
bool chuva; // condição de chuva
bool soloUmido; // condição de solo úmido

const float solo_max_1 = 0.0;
const float solo_min_1 = 4.1;
const float solo_max_2 = 3.3;
const float solo_min_2 = 0.0;

void setup() {
  pinMode(sensorUmidadeSolo, INPUT); // Sensor de umidade do solo - porta A0 é entrada
  pinMode(sensorUmidadeSolo2, INPUT);
  
  // pinMode(sensorChuva, INPUT); // Sensor de chuva - porta A1 é entrada
  // pinMode(portaRele, OUTPUT); // Porta de controle do Relé - D4 é saída
  // digitalWrite(portaRele, HIGH); // Mantenha relé desligado
  Serial.begin(9600); // Monitor console 9600 Bps

  dht.begin(); // inicializa a função
  sensor_t sensor;
}

void SensorDeChuva ()
{
  int valorSensorChuva = analogRead(sensorChuva); // fazendo a leitura do Sensor de chuva
  Serial.print(" Sensor de chuva = "); // imprime mensagem
  Serial.print(valorSensorChuva); // imprime o valor do sensor de chuva
  if (valorSensorChuva < valorLimiteChuva) // se o valor for menor do que o limite
  {
  Serial.println(" => Esta chovendo"); // imprime a mensagem
  chuva = 1 ; // esta chovendo
  }
  else // senão
  {
  Serial.println(" => O tempo esta seco"); // imprime a mensagem
  chuva = 0 ; // não esta chovendo
  }
}

void SensorDeUmidade ()
{

  int valorSensorUmidadeSolo = analogRead(sensorUmidadeSolo); // leitura do Sensor de umidade do solo
  // Serial.print(" Sensor de umidade do solo = "); // imprime mensagem
  // Serial.print(valorSensorUmidadeSolo); // valor do sensor de umidade do solo

  Serial.print("{'umidade_solo': ");
  Serial.print(valorSensorUmidadeSolo); // valor do sensor de umidade do solo
  
  if (valorSensorUmidadeSolo < valorLimiteUmidade) // se o valor for menor do que o limite
  {
    // Serial.println(" ...... O solo esta úmido      :)"); // imprime a mensagem
    soloUmido = 1 ; // solo esta úmido
  }
  else // senão
  {
    // Serial.println(" ...... O solo esta seco      :("); // imprime a mensagem
    soloUmido = 0 ; // solo não esta úmido
  }

}

void SensorDeTemperatura(){
  sensors_event_t event; // inicializa o evento da Temperatura
  dht.temperature().getEvent(&event); // faz a leitura da Temperatura
  
  if (isnan(event.temperature)) // se algum erro na leitura
  {
    Serial.println("Erro na leitura da Temperatura!");
  }
  else // senão
  {
    Serial.print(", 'temperatura ambiente': ");
    Serial.print(event.temperature); // valor do sensor de umidade do solo

    // Serial.print("Temperatura: "); // imprime a Temperatura
    // Serial.print(event.temperature);
    // Serial.println(" *C");
  }
  
  dht.humidity().getEvent(&event); // faz a leitura de umidade
  if (isnan(event.relative_humidity)) // se algum erro na leitura
  {
    Serial.println("Erro na leitura da Umidade!");
  }
  else // senão
  {
    Serial.print(", 'umidade ambiente': ");
    Serial.print(event.relative_humidity); // valor do sensor de umidade do solo

    Serial.println("}");

    // Serial.print("Umidade: "); // imprime a Umidade
    // Serial.print(event.relative_humidity);
    // Serial.println("%");
  }
}

void ControleDoRele() // ajuste o tempo de acionamento da bomba
{
  digitalWrite(portaRele, HIGH); // relé desligado
  digitalWrite(portaRele, LOW); // relé ligado
  Serial.println(" Relé acionado "); // imprime a mensagem
  delay (1000); // tempo de acionamento da bomba dágua = 1 segundo
  digitalWrite(portaRele, HIGH); // relé desligado
}

void loop()
{

  delay(2000); // atraso de 5 segundos

  // Sensor umidade 1
  int valorSensorUmidadeSolo = analogRead(sensorUmidadeSolo); // leitura do Sensor de umidade do solo
  float umidade1 = (float(analogRead(valorSensorUmidadeSolo))/1023.0)*4.1;
  float valor_umidade1 = map(umidade1, solo_min_1, solo_max_1, 100, 0);
  
  // Sensor umidade 1
  int valorSensorUmidadeSolo2 = analogRead(sensorUmidadeSolo2); // leitura do Sensor de umidade do solo
  float umidade2 = (float(analogRead(valorSensorUmidadeSolo2))/1023.0)*3.3;
  float valor_umidade2 = map(umidade2, solo_min_2, solo_max_2, 100, 0);
  
  // Sensor temperatura
  sensors_event_t event; // inicializa o evento da Temperatura
  dht.temperature().getEvent(&event); // faz a leitura da Temperatura

  Serial.print("{'umidade_solo': ");
  Serial.print(umidade1); // valor do sensor de umidade do solo
  Serial.print(", 'per_solo': ");
  Serial.print(valor_umidade1); // valor do sensor de umidade do solo

  Serial.print(", 'umidade_solo2': ");
  Serial.print(umidade2); // valor do sensor de umidade do solo
  Serial.print(", 'per_solo2': ");
  Serial.print(valor_umidade2); // valor do sensor de umidade do solo


  Serial.print(", 'temperatura ambiente': ");
  Serial.print(event.temperature); // valor do sensor de umidade do solo
  Serial.println("}");    

}