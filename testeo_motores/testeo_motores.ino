/*
 * Testeo de Motores - Seguidor de Línea
 * Funciones:
 * - Control de velocidad y dirección de los motores DC (para las ruedas del robot).
 * - Habilidad de detener los motores.
 */

const int motorDC_pin1 = 9;  // Pin PWM para control de velocidad
const int motorDC_pin2 = 8;  // Pin de dirección
const int motorDC_enable = 7; // Pin enable

// Variables globales
int velocidad_motor = 255;  // Velocidad máxima del motor (0-255)
bool direccion = true;      // true = adelante, false = atrás

void setup() {
  Serial.begin(9600);
  Serial.println("=== TESTEO DE MOTORES ===");

  pinMode(motorDC_pin1, OUTPUT);
  pinMode(motorDC_pin2, OUTPUT);
  pinMode(motorDC_enable, OUTPUT);

  // Estado inicial: Habilitar motor
  digitalWrite(motorDC_enable, HIGH);
  mostrarMenu();
}

void loop() {
  if (Serial.available() > 0) {
    char opcion = Serial.read();

    switch (opcion) {
      case '1':
        moverAdelante();
        break;
      case '2':
        moverAtras();
        break;
      case '3':
        detenerMotores();
        break;
      case 'm':
      case 'M':
        mostrarMenu();
        break;
      default:
        Serial.println("Opción no válida. Presiona 'M' para ver el menú.");
        break;
    }
  }

  delay(100);
}

void mostrarMenu() {
  Serial.println("\n=== MENÚ DE TESTEO ===");
  Serial.println("1. Mover adelante");
  Serial.println("2. Mover atrás");
  Serial.println("3. Detener motores");
  Serial.println("M. Mostrar Menú");
  Serial.println("Selecciona una opción:");
}

void moverAdelante() {
  Serial.println("\nMoviendo adelante...");
  digitalWrite(motorDC_pin2, HIGH);
  analogWrite(motorDC_pin1, velocidad_motor);
}

void moverAtras() {
  Serial.println("\nMoviendo atrás...");
  digitalWrite(motorDC_pin2, LOW);
  analogWrite(motorDC_pin1, velocidad_motor);
}

void detenerMotores() {
  Serial.println("\nDeteniendo motores...");
  analogWrite(motorDC_pin1, 0);
  digitalWrite(motorDC_enable, LOW);
  delay(1000); // Pausa de 1 segundo
  digitalWrite(motorDC_enable, HIGH);
  Serial.println("Motores reactivados.");
}

