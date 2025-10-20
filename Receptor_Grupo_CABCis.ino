#include <esp_now.h>
#include <WiFi.h>
#include "esp_wifi.h"

typedef struct struct_mensaje {
  int id;
  float temperatura;
} struct_mensaje;

struct_mensaje datoEntrante;

void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  memcpy(&datoEntrante, data, sizeof(datoEntrante));
  Serial.print("ID: ");
  Serial.println(datoEntrante.id);
  Serial.print("Temperatura: ");
  Serial.println(datoEntrante.temperatura);
}

void setup() {
  Serial.begin(115200);

  // Poner WiFi en modo estación (STA)
  WiFi.mode(WIFI_STA);

  // Fijar canal WiFi al 1 (igual que el transmisor)
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  // Inicializar ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error al inicializar ESP-NOW");
    return;
  }

  // Registrar callback de recepción
  esp_now_register_recv_cb(onDataRecv);
}

void loop() {
  // No es necesario hacer nada aquí, la recepción se maneja por callback
}
