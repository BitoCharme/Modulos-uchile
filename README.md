# Pendiente
Codigo no verificado ni probado aún.

Cambia los valores de MAC en ambos códigos con los reales de tus placas (puedes obtenerlos con WiFi.macAddress()).
NOTAS importantes:

MAC Address: Cambia el array broadcastAddress con la MAC real de la placa receptora.

Para encontrar la MAC de la segunda placa, puedes usar WiFi.macAddress() en su código y copiarla.

Pin analógico: El NodeMCU ESP8266 tiene solo un pin analógico A0, así que necesitarás un multiplexor o leer un sensor analógico y un potenciómetro digital, o hacer el ajuste en hardware para tener dos señales en un solo pin, o usar un potenciómetro digital con comunicación I2C/SPI.

Si quieres, te ayudo a hacer un código para usar solo el LDR y el potenciómetro con un potenciómetro digital o con el mismo pin y lecturas separadas.

El pulsador está con pull-up interno, presionado es LOW.
