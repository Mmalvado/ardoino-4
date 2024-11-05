#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

const int ledVerdePin = 3;       
const int ledVermelhoPin = 4;    
const int buzzerPin = 5;         
const int sensorPortaPin = 6;    

bool portaFechada = true;        
unsigned long tempoAberta = 0;   
const unsigned long tempoAlerta = 5000;  

void setup() {
  pinMode(ledVerdePin, OUTPUT);
  pinMode(ledVermelhoPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensorPortaPin, INPUT_PULLUP); 

  lcd.begin(16, 2);
   lcd.setBacklight(1);

  digitalWrite(ledVerdePin, HIGH);
  digitalWrite(ledVermelhoPin, LOW);
  digitalWrite(buzzerPin, LOW);
  
  lcd.setCursor(0, 0);
  lcd.print("Porta Fechada");
  lcd.setCursor(0, 1);
  lcd.print("Seguranca Ativada");
}

void loop() {
  bool estadoSensor = digitalRead(sensorPortaPin);

  if (estadoSensor == LOW) {
    if (!portaFechada) {
      portaFechada = true;
      fecharPorta();
    }
  } else {
    if (portaFechada) {
      portaFechada = false;
      abrirPorta();
    }

    
    if (millis() - tempoAberta > tempoAlerta) {
      alertaInvasao();
    }
  }
}


void fecharPorta() {
  
  digitalWrite(ledVerdePin, HIGH);
  digitalWrite(ledVermelhoPin, LOW);
  digitalWrite(buzzerPin, LOW);
  
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Porta Fechada");
  lcd.setCursor(0, 1);
  lcd.print("Seguranca Ativada");
}


void abrirPorta() {
  digitalWrite(ledVerdePin, LOW);
  digitalWrite(ledVermelhoPin, HIGH);
  digitalWrite(buzzerPin, HIGH); 
  
  tempoAberta = millis();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Porta Aberta");
  lcd.setCursor(0, 1);
  lcd.print("Cuidado!");
}

void alertaInvasao() {
  digitalWrite(ledVermelhoPin, HIGH);
  tone(buzzerPin, 1000); 

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alerta! Invasao");
  lcd.setCursor(0, 1);
  lcd.print("Porta forcada!");
  
  delay(3000); 

  noTone(buzzerPin); 
}
