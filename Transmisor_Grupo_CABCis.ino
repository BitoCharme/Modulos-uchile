#include <esp_now.h>
#include <WiFi.h>
#include "esp_wifi.h"

// Dirección MAC de broadcast (envía a todos)
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct struct_mensaje {
  int id;
  float temperatura;
} struct_mensaje;

struct_mensaje miDato;

void onDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  Serial.print("Estado del último paquete: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Éxito" : "Fallo");
}

void setup() {
  Serial.begin(115200);

  // Poner WiFi en modo estación (STA)
  WiFi.mode(WIFI_STA);

  // Fijar canal WiFi al 1 (ambos dispositivos deben usar el mismo)
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  // Inicializar ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error al inicializar ESP-NOW");
    return;
  }

  // Registrar callback de envío
  esp_now_register_send_cb(onDataSent);

  // Configurar peer (destino) - broadcast en este caso
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 1;   // Canal igual que el fijado arriba
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Error al agregar peer");
    return;
  }

  // Datos a enviar
  miDato.id = 1;
  miDato.temperatura = 24.5;
}

void loop() {
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&miDato, sizeof(miDato));
  if (result == ESP_OK) {
    Serial.println("Dato enviado con éxito");
  } else {
    Serial.println("Error al enviar dato");
  }
  delay(2000);
}
