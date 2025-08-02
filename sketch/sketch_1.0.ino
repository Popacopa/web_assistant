

const int led = 13;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);  // Инициализация Serial-порта на скорости 9600 бод
}

void loop() {

  char res = Serial.read();

  switch (res) {
    case '1' :
      digitalWrite(led, HIGH); break;
    
    case '0' :
      digitalWrite(led, LOW); break;
    
  }
}