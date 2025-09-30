const int clockPin = 2; 
const int piezoPin = 8;
const int piezoPinIn = A0;
int clockState = HIGH;
int clockTime = 0;
const int tresholdPiezo = 40;

const int trigPin = 6;    // TRIG del HC-SR04
const int echoPin = 5;    // ECHO del HC-SR04
const int outputPin = 7;  // salida digital

long duration;
int distance;
const int threshold = 200; // distancia en cm para activar HIGH

void setup() {
  pinMode(clockPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(outputPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);

  Serial.begin(9600); 
}

void loop() {
  // Generar pulso de disparo
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Medir el tiempo de respuesta
  duration = pulseIn(echoPin, HIGH, 30000); 

  if (duration == 0) {
    distance = 999; // fuera de rango
  } else {
    distance = duration * 0.034 / 2; // convertir a cm
  }

  // Salida digital: HIGH dentro de rango, LOW fuera
  if (distance >= threshold) {
    digitalWrite(outputPin, HIGH);
  } else {
    digitalWrite(outputPin, LOW);
  }

  // Botón (piezo)
  int sensorValue = analogRead(piezoPinIn);
  if (sensorValue > tresholdPiezo) {
    digitalWrite(piezoPin, HIGH);
  } else {
    digitalWrite(piezoPin, LOW);
  }

  // Debug piezo
  //Serial.print("Piezo analog value: ");
  //Serial.print(sensorValue);
  //Serial.print(" | Piezo output: ");
  //Serial.println(digitalRead(piezoPin));

  // CLOCK, DONT TOUCH
  digitalWrite(clockPin, clockState);
  if (clockTime >= 100) {
    clockTime = 0;
    clockState = !clockState;

    // Debug clock
    Serial.print("Clock toggled, state: ");
    Serial.println(clockState);
  }
  delay(1);  // 1 ms
  clockTime += 1;
  // END CLOCK-------------
}
