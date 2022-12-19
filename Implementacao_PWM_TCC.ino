// Felipe de Freitas e Silva
// Trabalho de conclusão de curso - Engenharia de computação
// Aprovado em 30/11/2022

// Implementação do PWM e leitura de tensão 
const int pinoSensor = 36; //PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO
const int ledPin = 16;  // 16 corresponde a GPIO16

// PROPRIEDADES DO PWM
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
float tensaoEntrada = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DE TENSÃO DE ENTRADA DO SENSOR
float tensaoMedida = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DA TENSÃO MEDIDA PELO SENSOR

float valorR1 = 11000.0; //VALOR DO RESISTOR 1 DO DIVISOR DE TENSÃO
float valorR2 = 1000.0; // VALOR DO RESISTOR 2 DO DIVISOR DE TENSÃO
int leituraSensor = 0; //VARIÁVEL PARA ARMAZENAR A LEITURA DO PINO ANALÓGICO

void setup(){
   pinMode(pinoSensor, INPUT); //DEFINE O PINO COMO ENTRADA
   Serial.begin(9600); //INICIALIZA A SERIAL
     // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
}
void loop(){
   leituraSensor = analogRead(pinoSensor); //FAZ A LEITURA DO PINO ANALÓGICO E ARMAZENA NA VARIÁVEL O VALOR LIDO
   tensaoEntrada = (leituraSensor * 5.0) / 1024.0; //VARIÁVEL RECEBE O RESULTADO DO CÁLCULO
   tensaoMedida = tensaoEntrada / (valorR2/(valorR1+valorR2)); //VARIÁVEL RECEBE O VALOR DE TENSÃO DC MEDIDA PELO SENSOR
   delay(500); //INTERVALO DE 500 MILISSEGUNDOS
     // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);   
    delay(15);
  }
}
