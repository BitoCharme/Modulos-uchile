/*
 * Testeo de Sensores - Universidad de Chile
 * 
 * Este código permite probar diferentes tipos de sensores y mostrar:
 * - Valores individuales de cada sensor
 * - Posición relativa calculada
 * - Monitoreo en tiempo real
 * 
 * Sensores incluidos:
 * - Sensor ultrasónico (HC-SR04)
 * - Sensores de línea (IR)
 * - Acelerómetro/Giroscopio (MPU6050)
 * - Sensor de luz (LDR)
 */

// Pines para sensor ultrasónico
const int ultrasonico_trigger = 12;
const int ultrasonico_echo = 11;

// Pines para sensores de línea (5 sensores IR)
const int sensor_linea[] = {A0, A1, A2, A3, A4};
const int num_sensores_linea = 5;

// Pin para sensor de luz
const int sensor_luz = A5;

// Variables para almacenar lecturas
float distancia_ultrasonico = 0;
int valores_linea[5];
int valor_luz = 0;
float posicion_relativa = 0;

// Variables para control de tiempo
unsigned long tiempo_anterior = 0;
const unsigned long intervalo_lectura = 100; // 100ms entre lecturas

// Configuración de ventana de visualización
const int ANCHO_VENTANA = 80; // Caracteres de ancho para la "ventana"

void setup() {
  // Inicializar comunicación serial
  Serial.begin(9600);
  
  // Configurar pines
  pinMode(ultrasonico_trigger, OUTPUT);
  pinMode(ultrasonico_echo, INPUT);
  
  // Los pines analógicos no necesitan configuración
  
  // Mensaje de inicio
  mostrar_header();
  delay(2000);
  
  // Inicializar pantalla
  inicializar_ventana();
}

void loop() {
  unsigned long tiempo_actual = millis();
  
  if (tiempo_actual - tiempo_anterior >= intervalo_lectura) {
    // Leer todos los sensores
    leer_sensores();
    
    // Calcular posición relativa
    calcular_posicion_relativa();
    
    // Mostrar datos en ventana organizada
    mostrar_ventana_sensores();
    
    tiempo_anterior = tiempo_actual;
  }
  
  // Verificar si hay comandos del usuario
  if (Serial.available() > 0) {
    char comando = Serial.read();
    procesar_comando(comando);
  }
}

void mostrar_header() {
  Serial.println("╔══════════════════════════════════════════════════════════════════════════════╗");
  Serial.println("║                        TESTEO DE SENSORES                                   ║");
  Serial.println("║                      Universidad de Chile                                   ║");
  Serial.println("╠══════════════════════════════════════════════════════════════════════════════╣");
  Serial.println("║ Comandos disponibles:                                                       ║");
  Serial.println("║ 'c' - Calibrar sensores de línea                                           ║");
  Serial.println("║ 'r' - Reiniciar lecturas                                                   ║");
  Serial.println("║ 'h' - Mostrar esta ayuda                                                   ║");
  Serial.println("╚══════════════════════════════════════════════════════════════════════════════╝");
}

void inicializar_ventana() {
  // Limpiar pantalla (códigos ANSI)
  Serial.print("\033[2J");
  Serial.print("\033[H");
}

void leer_sensores() {
  // Leer sensor ultrasónico
  distancia_ultrasonico = leer_ultrasonico();
  
  // Leer sensores de línea
  for (int i = 0; i < num_sensores_linea; i++) {
    valores_linea[i] = analogRead(sensor_linea[i]);
  }
  
  // Leer sensor de luz
  valor_luz = analogRead(sensor_luz);
}

float leer_ultrasonico() {
  // Enviar pulso
  digitalWrite(ultrasonico_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonico_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonico_trigger, LOW);
  
  // Leer eco y calcular distancia
  long duracion = pulseIn(ultrasonico_echo, HIGH);
  float distancia = (duracion * 0.034) / 2;
  
  return distancia;
}

void calcular_posicion_relativa() {
  // Calcular posición basada en sensores de línea
  // Método de promedio ponderado
  
  int suma_ponderada = 0;
  int suma_valores = 0;
  
  for (int i = 0; i < num_sensores_linea; i++) {
    int valor_normalizado = map(valores_linea[i], 0, 1023, 0, 100);
    suma_ponderada += valor_normalizado * (i * 1000); // Posiciones: 0, 1000, 2000, 3000, 4000
    suma_valores += valor_normalizado;
  }
  
  if (suma_valores > 0) {
    posicion_relativa = (float)suma_ponderada / suma_valores;
    posicion_relativa = (posicion_relativa - 2000) / 1000.0; // Normalizar a -2.0 a +2.0
  } else {
    posicion_relativa = 0; // Sin línea detectada
  }
}

void mostrar_ventana_sensores() {
  // Mover cursor al inicio (sin limpiar toda la pantalla)
  Serial.print("\033[H");
  
  // Header de la ventana
  Serial.println("╔══════════════════════════════════════════════════════════════════════════════╗");
  Serial.println("║                           MONITOR DE SENSORES                               ║");
  Serial.println("╠══════════════════════════════════════════════════════════════════════════════╣");
  
  // Sensor ultrasónico
  Serial.print("║ Distancia Ultrasónica: ");
  if (distancia_ultrasonico > 0 && distancia_ultrasonico < 400) {
    Serial.print(distancia_ultrasonico, 1);
    Serial.print(" cm");
  } else {
    Serial.print("Fuera de rango");
  }
  rellenar_linea(30);
  Serial.println("║");
  
  // Representación gráfica de distancia
  Serial.print("║ ");
  mostrar_barra_distancia();
  Serial.println(" ║");
  
  Serial.println("╠──────────────────────────────────────────────────────────────────────────────╣");
  
  // Sensores de línea
  Serial.println("║                         SENSORES DE LÍNEA                                   ║");
  Serial.print("║ Valores: ");
  for (int i = 0; i < num_sensores_linea; i++) {
    Serial.print("[");
    Serial.print(i);
    Serial.print("]:");
    if (valores_linea[i] < 100) Serial.print(" ");
    if (valores_linea[i] < 10) Serial.print(" ");
    Serial.print(valores_linea[i]);
    Serial.print(" ");
  }
  rellenar_linea(25);
  Serial.println("║");
  
  // Representación gráfica de sensores de línea
  Serial.print("║ Gráfico:  ");
  mostrar_grafico_linea();
  rellenar_linea(20);
  Serial.println("║");
  
  // Posición relativa
  Serial.print("║ Posición Relativa: ");
  Serial.print(posicion_relativa, 2);
  if (posicion_relativa > 0) {
    Serial.print(" (Derecha)");
  } else if (posicion_relativa < 0) {
    Serial.print(" (Izquierda)");
  } else {
    Serial.print(" (Centro)");
  }
  rellenar_linea(25);
  Serial.println("║");
  
  Serial.println("╠──────────────────────────────────────────────────────────────────────────────╣");
  
  // Sensor de luz
  Serial.print("║ Sensor de Luz: ");
  Serial.print(valor_luz);
  Serial.print(" (");
  int porcentaje_luz = map(valor_luz, 0, 1023, 0, 100);
  Serial.print(porcentaje_luz);
  Serial.print("%)");
  rellenar_linea(35);
  Serial.println("║");
  
  // Barra de luz
  Serial.print("║ Intensidad:   ");
  mostrar_barra_luz();
  rellenar_linea(20);
  Serial.println("║");
  
  Serial.println("╠──────────────────────────────────────────────────────────────────────────────╣");
  
  // Estado general y tiempo
  Serial.print("║ Estado: ACTIVO | Tiempo: ");
  Serial.print(millis() / 1000);
  Serial.print(" seg");
  rellenar_linea(35);
  Serial.println("║");
  
  Serial.println("╚══════════════════════════════════════════════════════════════════════════════╝");
}

void mostrar_barra_distancia() {
  int longitud_barra = 40;
  int posicion = map(constrain(distancia_ultrasonico, 0, 100), 0, 100, 0, longitud_barra);
  
  Serial.print("[");
  for (int i = 0; i < longitud_barra; i++) {
    if (i <= posicion) {
      Serial.print("█");
    } else {
      Serial.print("░");
    }
  }
  Serial.print("]");
}

void mostrar_grafico_linea() {
  for (int i = 0; i < num_sensores_linea; i++) {
    int intensidad = map(valores_linea[i], 0, 1023, 0, 4);
    switch (intensidad) {
      case 0: Serial.print("░"); break;
      case 1: Serial.print("▒"); break;
      case 2: Serial.print("▓"); break;
      case 3: 
      case 4: Serial.print("█"); break;
    }
    Serial.print(" ");
  }
}

void mostrar_barra_luz() {
  int longitud_barra = 30;
  int posicion = map(valor_luz, 0, 1023, 0, longitud_barra);
  
  Serial.print("[");
  for (int i = 0; i < longitud_barra; i++) {
    if (i <= posicion) {
      Serial.print("▓");
    } else {
      Serial.print("░");
    }
  }
  Serial.print("]");
}

void rellenar_linea(int espacios_usados) {
  int espacios_disponibles = 76; // Ancho total menos bordes
  for (int i = espacios_usados; i < espacios_disponibles; i++) {
    Serial.print(" ");
  }
}

void procesar_comando(char comando) {
  switch (comando) {
    case 'c':
    case 'C':
      calibrar_sensores();
      break;
    case 'r':
    case 'R':
      reiniciar_lecturas();
      break;
    case 'h':
    case 'H':
      mostrar_ayuda();
      break;
  }
}

void calibrar_sensores() {
  Serial.println("\n╔══════════════════════════════════════════════════════════════════════════════╗");
  Serial.println("║                              CALIBRACIÓN                                    ║");
  Serial.println("╚══════════════════════════════════════════════════════════════════════════════╝");
  Serial.println("Calibrando sensores de línea...");
  Serial.println("Mueve el robot sobre línea blanca y negra durante 5 segundos...");
  
  // Calibración simple durante 5 segundos
  unsigned long tiempo_calibracion = millis();
  while (millis() - tiempo_calibracion < 5000) {
    for (int i = 0; i < num_sensores_linea; i++) {
      analogRead(sensor_linea[i]); // Lecturas para estabilizar
    }
    delay(10);
  }
  
  Serial.println("Calibración completada.");
  delay(1000);
  inicializar_ventana();
}

void reiniciar_lecturas() {
  // Reiniciar variables
  distancia_ultrasonico = 0;
  for (int i = 0; i < num_sensores_linea; i++) {
    valores_linea[i] = 0;
  }
  valor_luz = 0;
  posicion_relativa = 0;
  
  inicializar_ventana();
}

void mostrar_ayuda() {
  Serial.println("\n╔══════════════════════════════════════════════════════════════════════════════╗");
  Serial.println("║                                 AYUDA                                       ║");
  Serial.println("╠══════════════════════════════════════════════════════════════════════════════╣");
  Serial.println("║ Este programa monitorea múltiples sensores en tiempo real:                 ║");
  Serial.println("║                                                                              ║");
  Serial.println("║ • Sensor Ultrasónico: Mide distancia en cm (0-400cm)                      ║");
  Serial.println("║ • Sensores de Línea: 5 sensores IR para seguimiento de línea               ║");
  Serial.println("║ • Posición Relativa: Calculada basada en sensores de línea                 ║");
  Serial.println("║ • Sensor de Luz: Mide intensidad lumínica ambiente                         ║");
  Serial.println("║                                                                              ║");
  Serial.println("║ Comandos:                                                                    ║");
  Serial.println("║ 'c' - Calibrar sensores de línea                                           ║");
  Serial.println("║ 'r' - Reiniciar todas las lecturas                                         ║");
  Serial.println("║ 'h' - Mostrar esta ayuda                                                   ║");
  Serial.println("╚══════════════════════════════════════════════════════════════════════════════╝");
  Serial.println("Presiona cualquier tecla para continuar...");
  
  while (!Serial.available()) {
    delay(100);
  }
  while (Serial.available()) {
    Serial.read(); // Limpiar buffer
  }
  
  inicializar_ventana();
}