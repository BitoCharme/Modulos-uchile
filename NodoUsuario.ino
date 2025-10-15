// Usa pines analógicos para LDR y potenciómetro (en NodeMCU ESP8266 solo hay un ADC, así que usaré A0 para ambos con multiplexación o asumir que solo tienes un ADC, pero para fines prácticos asumiré que usas un pin analógico para LDR y otro digital para potenciómetro con un ADC externo o un potenciómetro digital.
// Si solo tienes un ADC, me dices y te ayudo a ajustar.

// Pulsador en pin D5 con pull-up interno.

// Envía un mensaje simple "SUBIR", "BAJAR", "NINGUNA", o "BAJAR_Y_APAGAR".

// Define tolerancia para evitar oscilaciones.


#include <espnow.h>
#include <ESP8266WiFi.h>

#define LDR_PIN A0         // Pin del fotoresistor
#define POT_PIN A0         // En NodeMCU solo hay un ADC, si tienes otro método dime
#define BUTTON_PIN D5      // Pulsador en pin digital D5

#define TOLERANCIA 50      // Margen para evitar oscilaciones

// Variables para lectura
int nivelDeseado = 0;
int luzActual = 0;
bool botonPresionado = false;

// Dirección MAC de la placa receptora (cambia por la MAC de tu segunda placa)
uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xXX, 0xXX, 0xXX};

// Mensaje a enviar
String comando = "NINGUNA";

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  Serial.println(sendStatus == 0 ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // WiFi en modo estación (sin conectarse a red)
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  // Agregar peer (la placa receptora)
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  Serial.println("Setup terminado");
}

void loop() {
  // Leer potenciómetro y LDR
  // Aquí tienes que ajustar si solo tienes un ADC; asumo que usas A0 para ambos y los lees uno tras otro (hardware externo).
  // Por simplicidad leeré solo uno, ajusta según tu hardware
  luzActual = analogRead(LDR_PIN);        // Fotoresistor
  nivelDeseado = analogRead(POT_PIN);     // Potenciómetro

  botonPresionado = (digitalRead(BUTTON_PIN) == LOW);

  Serial.print("Luz actual: ");
  Serial.print(luzActual);
  Serial.print(" - Nivel deseado: ");
  Serial.print(nivelDeseado);
  Serial.print(" - Boton: ");
  Serial.println(botonPresionado ? "Presionado" : "No presionado");

  // Decidir comando
  if (botonPresionado) {
    comando = "BAJAR_Y_APAGAR";
  } else {
    if (luzActual < nivelDeseado - TOLERANCIA) {
      comando = "SUBIR";
    } else if (luzActual > nivelDeseado + TOLERANCIA) {
      comando = "BAJAR";
    } else {
      comando = "NINGUNA";
    }
  }

  // Enviar comando
  esp_now_send(broadcastAddress, (uint8_t *)comando.c_str(), comando.length());

  delay(1000); // Esperar 1 segundo antes de leer otra vez
}


// NOTAS importantes:

  // MAC Address: Cambia el array broadcastAddress con la MAC real de la placa receptora.

  // Para encontrar la MAC de la segunda placa, puedes usar WiFi.macAddress() en su código y copiarla.

  // Pin analógico: El NodeMCU ESP8266 tiene solo un pin analógico A0, así que necesitarás un multiplexor o leer un sensor analógico y un potenciómetro digital, o hacer el ajuste en hardware para tener dos señales en un solo pin, o usar un potenciómetro digital con comunicación I2C/SPI.

  // Si quieres, te ayudo a hacer un código para usar solo el LDR y el potenciómetro con un potenciómetro digital o con el mismo pin y lecturas separadas.

  // El pulsador está con pull-up interno, presionado es LOW.
