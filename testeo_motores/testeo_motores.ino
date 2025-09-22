/*
 * Testeo de Motores - Seguidor de Línea
 * Este código prueba el funcionamiento de los motores DC en un robot seguidor de línea.
 * 
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

/*
 * Testeo de Sensores - Seguidor de Línea
 * Este código prueba el funcionamiento de los sensores de línea (IR) para detectar la línea.
 * 
 * Funciones:
 * - Leer valores de los sensores IR.
 * - Mostrar los valores en el monitor serial y decidir el comportamiento del robot.
 */

const int sensorIzquierdo = A0;  // Pin para sensor izquierdo
const int sensorDerecho = A1;    // Pin para sensor derecho

int valorIzquierdo = 0;
int valorDerecho = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("=== TESTEO DE SENSORES IR ===");

  pinMode(sensorIzquierdo, INPUT);
  pinMode(sensorDerecho, INPUT);

  mostrarMenu();
}

void loop() {
  if (Serial.available() > 0) {
    char opcion = Serial.read();

    switch (opcion) {
      case '1':
        testearSensores();
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
  Serial.println("\n=== MENÚ DE TESTEO DE SENSORES ===");
  Serial.println("1. Testear Sensores");
  Serial.println("M. Mostrar Menú");
  Serial.println("Selecciona una opción:");
}

void testearSensores() {
  valorIzquierdo = analogRead(sensorIzquierdo);
  valorDerecho = analogRead(sensorDerecho);

  Serial.print("Izquierdo: ");
  Serial.print(valorIzquierdo);
  Serial.print("  Derecho: ");
  Serial.println(valorDerecho);

  // Definir un umbral para la detección de línea (esto dependerá de tu sensor)
  int umbral = 500; // Ajusta este valor según tu sensor

  // Detectar si el sensor izquierdo está sobre la línea (valor bajo indica línea detectada)
  if (valorIzquierdo < umbral) {
    Serial.println("Sensor izquierdo detecta la línea.");
  } else {
    Serial.println("Sensor izquierdo no detecta la línea.");
  }

  // Detectar si el sensor derecho está sobre la línea
  if (valorDerecho < umbral) {
    Serial.println("Sensor derecho detecta la línea.");
  } else {
    Serial.println("Sensor derecho no detecta la línea.");
  }
}

