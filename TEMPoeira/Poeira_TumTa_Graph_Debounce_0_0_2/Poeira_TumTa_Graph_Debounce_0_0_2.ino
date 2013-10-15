float valor[2] = {0,0};
float valorMedio[2] = {0,0};
float valorAnterior[2] = {0,0};
float variacao[2] = {0,0};
float variacaoAnterior[2] = {0,0};
float variacaoDaVariacao[2] = {0,0};
long lastDebounceTime[2] = {0,0};
boolean estadoParado[2] = {false,false};

int buttonPin = 12;

void setup() {
  // initialize the serial communication:
  Serial.begin(57600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // send the value of analog input 0:
  
  float foiPico[2] = {0,0};
  
  float potValor = analogRead(A5);
  float potValor2 = analogRead(A4);
  
  float limiteVarDeVar = map(potValor, 0, 1023, 0, 15);
  float tamanhoJanela = map(potValor2, 0, 1023, 0, 400); 

  //TUM
  valorAnterior[0] = valor[0];
  valor[0] = analogRead(A0);

  variacaoAnterior[0] = variacao[0];
  variacao[0] = valor[0] - valorAnterior[0];

  variacaoDaVariacao[0] = variacao[0] - variacaoAnterior[0];
//define a pisada quando a segunda derivada passar de um limite
  if(variacaoDaVariacao[0] > limiteVarDeVar){
    lastDebounceTime[0] = millis();
  }
//define a pisada quando a derivada passar de um limite
//  if(variacao[0] > limiteVarDeVar){
//    lastDebounceTime[0] = millis();
//  }

  if ((millis() - lastDebounceTime[0]) > tamanhoJanela) {
    estadoParado[0] = false;
    // Nao encontrou um pico
  } 
  else {
    estadoParado[0] = true;
    // Encontrou um pico
  }

  if (estadoParado[0]) {
    //valor = 0;
    foiPico[0] = 512;
  } else {
    foiPico[0] = 0;
  }

  
//TA
  valorAnterior[1] = valor[1];
  valor[1] = analogRead(A1);

  variacaoAnterior[1] = variacao[1];
  variacao[1] = valor[1] - valorAnterior[1];

  variacaoDaVariacao[1] = variacao[1] - variacaoAnterior[1];

//define a pisada quando a segunda derivada passar de um limite
  if(variacaoDaVariacao[1] > limiteVarDeVar){
    lastDebounceTime[1] = millis();
  }
  
//define a pisada quando a derivada passar de um limite
//  if(variacao[1] > limiteVarDeVar){
//    lastDebounceTime[1] = millis();
//  }

  if ((millis() - lastDebounceTime[1]) > tamanhoJanela) {
    estadoParado[1] = false;
    // Nao encontrou um pico
  } 
  else {
    estadoParado[1] = true;
    // Encontrou um pico
  }

  if (estadoParado[1]) {
    //valor = 0;
    foiPico[1] = 512;
  } else {
    foiPico[1] = 0;
  }


//BUTAO
  if(digitalRead(buttonPin)){
    valor[0] = 1023;
    valor[1] = 1023;
  }
  
  
//  Serial.print(potValor);
//  Serial.print('|');
//  Serial.print(potValor2);
//  Serial.print('|');

  Serial.print(foiPico[0]);
  Serial.print('|');
  Serial.print(valor[0]);
  //Serial.print(valor[0]);
  //Serial.print('|');
  //Serial.print(variacao[0]);
  //Serial.print('|');
  //Serial.println(variacaoDaVariacao[0]);
  

  Serial.print(foiPico[1]);
  Serial.print('|');
  Serial.println(valor[1]);
//  Serial.print('|');
//  Serial.println(variacao[1]);


  // wait a bit for the analog-to-digital converter 
  // to stabilize after the last reading:
  delay(2);
}


