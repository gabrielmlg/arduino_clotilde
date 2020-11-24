#include <Arduino.h>

// Exemplo 13 – Arduino Sensor de umidade do solo e Sensor de chuva
// Apostila Eletrogate - KIT MAKER
// Gustavo Murta
int sensorUmidadeSolo = A0; // Sensor de umidade do solo pino A0 conectado no A0 do Arduino
int sensorChuva = A1; // Sensor de chuva pino A0 conectado no A1 do Arduino
int portaRele = 4; // porta de controle do relé conectada no D4 do Arduino
int valorLimiteUmidade = 500; // valor da tensão de comparação do sensor / valor máximo = 1024
int valorLimiteChuva = 500; // valor da tensão de comparação do sensor máximo = 1024
bool chuva; // condição de chuva
bool soloUmido; // condição de solo úmido

void setup() {
  pinMode(sensorUmidadeSolo, INPUT); // Sensor de umidade do solo - porta A0 é entrada
  // pinMode(sensorChuva, INPUT); // Sensor de chuva - porta A1 é entrada
  // pinMode(portaRele, OUTPUT); // Porta de controle do Relé - D4 é saída
  // digitalWrite(portaRele, HIGH); // Mantenha relé desligado
  Serial.begin(9600); // Monitor console 9600 Bps
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

  Serial.print(", 'temperatura ambiente': ");
  Serial.print(valorSensorUmidadeSolo); // valor do sensor de umidade do solo

  Serial.println("}");
  
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

  for (int i = 1; i < 4321; i++) // contagem de 1 a 4320 ( 4320 x 5 segundos = 6 horas)
  {
    // SensorDeChuva (); // faz medição do sensor de chuva
    SensorDeUmidade (); // faz medição do sensor de umidade do solo
    
    // if (chuva == 0 && soloUmido == 0 && i == 1) 
      // Serial.println("LIGA A BOMBA DE AGUA");// ControleDoRele(); // aciona a bomba dágua a cada 6 horas se tempo e solo estiverem secos
    
    // Serial.print(i*5); // imprime tempo em segundos
    // Serial.println(" segundos"); 
    // Serial.println(); // imprime mensagem e uma linha
  
    delay(2000); // atraso de 5 segundos
  }

}