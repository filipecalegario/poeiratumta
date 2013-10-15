/*
  Graph
 
 A simple example of communication from the Arduino board to the computer:
 the value of analog input 0 is sent out the serial port.  We call this "serial"
 communication because the connection appears to both the Arduino and the
 computer as a serial port, even though it may actually use
 a USB cable. Bytes are sent one after another (serially) from the Arduino
 to the computer.
 
 You can use the Arduino serial monitor to view the sent data, or it can
 be read by Processing, PD, Max/MSP, or any other program capable of reading 
 data from a serial port.  The Processing code below graphs the data received 
 so you can see the value of the analog input changing over time.
 
 The circuit:
 Any analog input sensor is attached to analog in pin 0.
 
 created 2006
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe and Scott Fitzgerald
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Graph
 */

float valor = 0;
float valorAnterior = 0;
float variacao = 0;
float variacaoAnterior = 0;
float variacaoDaVariacao = 0;
long lastDebounceTime = 0;
boolean estadoParado = false;

int buttonPin = 12;

void setup() {
  // initialize the serial communication:
  Serial.begin(57600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // send the value of analog input 0:
  
  float foiPico = 0;
  
  float potValor = analogRead(A5);
  float potValor2 = analogRead(A4);
  
  float limiteVarDeVar = map(potValor, 0, 1023, 0, 15);
  float tamanhoJanela = map(potValor2, 0, 1023, 0, 400); 

  valorAnterior = valor;
  valor = analogRead(A0);

  variacaoAnterior = variacao;
  variacao = valor - valorAnterior;

  variacaoDaVariacao = variacao - variacaoAnterior;

  if(variacaoDaVariacao > limiteVarDeVar){
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > tamanhoJanela) {
    estadoParado = false;
    // Nao encontrou um pico
  } 
  else {
    estadoParado = true;
    // Encontrou um pico
  }

  if (estadoParado) {
    //valor = 0;
    foiPico = 512;
  } else {
    foiPico = 0;
  }

  if(digitalRead(buttonPin)){
    valor = 1023;
  }
  
  Serial.print(potValor);
  Serial.print('|');
  Serial.print(potValor2);
  Serial.print('|');
  Serial.print(foiPico);
  Serial.print('|');
  Serial.println(valor);


  // wait a bit for the analog-to-digital converter 
  // to stabilize after the last reading:
  delay(2);
}


