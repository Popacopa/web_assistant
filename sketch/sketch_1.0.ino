
const int led = 13;
unsigned char* buffer = new unsigned char;



void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);  // Инициализация Serial-порта на скорости 9600 бод
}

void loop() {

 if (Serial.available()) {
    Serial.readBytes(buffer, 1);
    Serial.write(*buffer);


    switch (*buffer) {
      case 0x01: digitalWrite(led, HIGH); break;
      case 0x00: digitalWrite(led, LOW); break;
    }
  }
}