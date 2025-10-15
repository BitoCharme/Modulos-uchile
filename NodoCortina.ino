#include <espnow.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

#define SERVO_PIN D4       // Pin de control del servo (ajusta según conexión)

Servo servoMotor;

unsigned long tiempoMovimiento = 2000;  // Tiempo que gira el servo en ms

// Velocidades para el servo continuo (ajusta según tu servo)
int velocidadSubir = 130;  // Giro en sentido horario (valores 0-180, 90 es stop)
int velocidadBajar = 50;   // Giro en sentido antihorario
int velocidadStop = 90;    // Parar el servo

// MAC de la placa emisora (la de usuario)
uint8_t peerAddress[] = {0x24, 0x6F, 0x28, 0xXX, 0xXX, 0xXX};

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  String comando = "";
  for (int i = 0; i < len; i++) {
    comando += (char)incomingData[i];
  }
  Serial.print("Comando recibido: ");
  Serial.println(comando);

  if (comando == "SUBIR") {
    servoMotor.write(velocidadSubir);
    delay(tiempoMovimiento);
    servoMotor.write(velocidadStop);
  } else if (comando == "BAJAR") {
    servoMotor.write(velocidadBajar);
    delay(tiempoMovimiento);
    servoMotor.write(velocidadStop);
  } else if (comando == "BAJAR_Y_APAGAR") {
    servoMotor.write(velocidadBajar);
    delay(tiempoMovimiento);
    servoMotor.write(velocidadStop);
    // Aquí puedes agregar lógica para "apagar" (modo sleep o similar)
    Serial.println("Modo noche activado");
  } else if (comando == "NINGUNA") {
    // No hacer nada
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);

  servoMotor.attach(SERVO_PIN);
  servoMotor.write(velocidadStop);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error inicializando ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
  esp_now_add_peer(peerAddress, ESP_NOW_ROLE_CONTROLLER, 1, NULL, 0);

  Serial.println("Nodo Cortina listo");
}

void loop() {
  // Nada que hacer aquí, la acción se ejecuta al recibir comandos
}



// Cambia los valores de MAC en ambos códigos con los reales de tus placas (puedes obtenerlos con WiFi.macAddress()).
