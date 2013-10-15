// Processing code for this example

// Graphing sketch


// This program takes ASCII-encoded strings
// from the serial port at 9600 baud and graphs them. It expects values in the
// range 0 to 1023, followed by a newline, or newline and carriage return

// Created 20 Apr 2005
// Updated 18 Jan 2008
// by Tom Igoe
// This example code is in the public domain.

import processing.serial.*;
import themidibus.*;

Serial myPort;
MidiBus myBus;

int xPos = 1;         // horizontal position of the graph

//PrintWriter output;
long startTime;
long nanoTime;
boolean travaPico1;
boolean travaPico2;
int ultimoMilli = 0;

int[] valores;
float[] valoresTela;

void setup () {
  // set the window size:
  size(1000, 600);        

  // List all the available serial ports
  println(Serial.list());
  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[0], 57600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  //output = createWriter("log_dia"+day()+"_"+month()+"_hora"+hour()+"_"+minute()+".csv");
  //output.println("sep=,");
  startTime = System.nanoTime();

  MidiBus.list();
  myBus = new MidiBus(this, -1, 0);

  // set inital background:
  background(0);
}
void draw () {
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {

    String[] pieces = split(inString, '|');

    valores = new int[pieces.length];
    valoresTela = new float[pieces.length];

    for (int i=0; i < pieces.length;i++) {
      pieces[i] = trim(pieces[i]);
      valores[i] = int(pieces[i]);
      valoresTela[i] = map(valores[i], 0, 1023, 0, height);
    }

    //nanoTime = (System.nanoTime() - startTime)/1000;
    //output.println(nanoTime + "," + valores[0]);

    // draw the line:

    for (int i=0; i < valoresTela.length; i++) {
      colorMode(HSB, 100);
      stroke((100/valoresTela.length)*i, 100, 100, 50);
      line(xPos, height, xPos, height - valoresTela[i]);
      escala();
    }

    tocarNota(valores[0], 1);
    tocarNota(valores[2], 2);

    //stroke(255, 0, 0);
    //line(xPos, height, xPos, height - valoresTela[0]);

    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      background(0);
    } 
    else {
      // increment the horizontal position:
      xPos++;
    }
  }
}

void escala() {
  int subDivisoes = 50; //coloca linhas de divisao da tela na escala de 0 a 1023
  float passo = 1023/subDivisoes;
  float passoTela = passo*height/1023;
  for (int i=0;i<subDivisoes;i++) {
    stroke(60);
    if (i*passo%100 == 0) stroke(100);
    line(0, height - i * passo, width, height - i * passo);
    //    text(i*passo, width - 40, height - i*passo - 2);
  }
}

void tocarNota(int pico, int i) {

  boolean trava = false;

  if (i == 1) {
    trava = travaPico1;
  } 
  else if (i == 2) {
    trava = travaPico2;
  }

  if (pico == 512 && !trava) {
    myBus.sendNoteOn(0, 60, 127);
    ultimoMilli = millis();
    if (i == 1) {
      travaPico1 = true;
    } 
    else if (i == 2) {
      travaPico2 = true;
    }
  }

  if ((millis() - ultimoMilli) > 500) {
    myBus.sendNoteOff(0, 60, 127);
  }

  if (pico == 0) {
    if (i == 1) {
      travaPico1 = false;
    } 
    else if (i == 2) {
      travaPico2 = false;
    }
  }
}

void keyPressed() {
  //output.flush(); // Writes the remaining data to the file
  //output.close(); // Finishes the file
  //exit(); // Stops the program
}

