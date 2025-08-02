

const int led = 13;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);  // Инициализация Serial-порта на скорости 9600 бод
  Serial.println("Эхо-программа готова. Отправьте данные...");
}

void loop() {

  char res = Serial.read();

  switch (res) {
    case '1' :
      digitalWrite(led, HIGH); break;
    
    case '0' :
      digitalWrite(led, LOW); break;
    
  }
  
  /* if (Serial.available() > 0) {  // Если есть данные в буфере
    char incomingByte = Serial.read();  // Читаем один байт
    Serial.print("Эхо: ");  // Добавляем метку перед ответом
    Serial.write(incomingByte);  // Отправляем обратно тот же байт
    Serial.println();  // Переход на новую строку */
}