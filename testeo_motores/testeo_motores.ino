/*
 * Testeo de Motores - Universidad de Chile
 * 
 * Este código permite probar diferentes tipos de motores:
 * - Motores DC
 * - Servomotores  
 * - Motores paso a paso
 * 
 * Funciones incluidas:
 * - Control de velocidad
 * - Control de dirección
 * - Pruebas de funcionamiento
 */

// Pines para motores DC
const int motorDC_pin1 = 9;  // Pin PWM para control de velocidad
const int motorDC_pin2 = 8;  // Pin de dirección
const int motorDC_enable = 7; // Pin enable

// Pines para servomotor
const int servo_pin = 6;

// Pines para motor paso a paso (usando driver A4988)
const int stepper_step = 5;
const int stepper_dir = 4;
const int stepper_enable = 3;

// Variables globales
int velocidad_motor = 0;
bool direccion = true; // true = adelante, false = atrás
int posicion_servo = 90; // Posición inicial del servo (90 grados)

void setup() {
  // Inicializar comunicación serial
  Serial.begin(9600);
  Serial.println("=== TESTEO DE MOTORES ===");
  Serial.println("Universidad de Chile");
  Serial.println("------------------------");
  
  // Configurar pines como salidas
  pinMode(motorDC_pin1, OUTPUT);
  pinMode(motorDC_pin2, OUTPUT);
  pinMode(motorDC_enable, OUTPUT);
  
  pinMode(servo_pin, OUTPUT);
  
  pinMode(stepper_step, OUTPUT);
  pinMode(stepper_dir, OUTPUT);
  pinMode(stepper_enable, OUTPUT);
  
  // Estado inicial
  digitalWrite(motorDC_enable, HIGH); // Habilitar motor DC
  digitalWrite(stepper_enable, LOW);  // Habilitar motor paso a paso
  
  mostrarMenu();
}

void loop() {
  if (Serial.available() > 0) {
    char opcion = Serial.read();
    
    switch (opcion) {
      case '1':
        testear_motor_DC();
        break;
      case '2':
        testear_servomotor();
        break;
      case '3':
        testear_motor_paso_a_paso();
        break;
      case '4':
        parar_todos_motores();
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
  Serial.println("1. Testear Motor DC");
  Serial.println("2. Testear Servomotor");
  Serial.println("3. Testear Motor Paso a Paso");
  Serial.println("4. Parar Todos los Motores");
  Serial.println("M. Mostrar Menú");
  Serial.println("Selecciona una opción:");
}

void testear_motor_DC() {
  Serial.println("\n--- TESTEO MOTOR DC ---");
  
  // Prueba hacia adelante
  Serial.println("Moviendo hacia adelante...");
  digitalWrite(motorDC_pin2, HIGH);
  for (int vel = 0; vel <= 255; vel += 51) {
    analogWrite(motorDC_pin1, vel);
    Serial.print("Velocidad: ");
    Serial.print((vel * 100) / 255);
    Serial.println("%");
    delay(1000);
  }
  
  // Parar
  analogWrite(motorDC_pin1, 0);
  delay(1000);
  
  // Prueba hacia atrás
  Serial.println("Moviendo hacia atrás...");
  digitalWrite(motorDC_pin2, LOW);
  for (int vel = 0; vel <= 255; vel += 51) {
    analogWrite(motorDC_pin1, vel);
    Serial.print("Velocidad: ");
    Serial.print((vel * 100) / 255);
    Serial.println("%");
    delay(1000);
  }
  
  // Parar motor
  analogWrite(motorDC_pin1, 0);
  Serial.println("Motor DC detenido.");
}

void testear_servomotor() {
  Serial.println("\n--- TESTEO SERVOMOTOR ---");
  
  // Mover servo de 0 a 180 grados
  Serial.println("Moviendo servo de 0° a 180°...");
  for (int pos = 0; pos <= 180; pos += 30) {
    controlar_servo(pos);
    Serial.print("Posición: ");
    Serial.print(pos);
    Serial.println("°");
    delay(1000);
  }
  
  // Volver a posición central
  controlar_servo(90);
  Serial.println("Servo en posición central (90°)");
}

void testear_motor_paso_a_paso() {
  Serial.println("\n--- TESTEO MOTOR PASO A PASO ---");
  
  // Mover en sentido horario
  Serial.println("Moviendo en sentido horario (200 pasos)...");
  digitalWrite(stepper_dir, HIGH);
  for (int i = 0; i < 200; i++) {
    digitalWrite(stepper_step, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepper_step, LOW);
    delayMicroseconds(2000);
  }
  
  delay(1000);
  
  // Mover en sentido antihorario
  Serial.println("Moviendo en sentido antihorario (200 pasos)...");
  digitalWrite(stepper_dir, LOW);
  for (int i = 0; i < 200; i++) {
    digitalWrite(stepper_step, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepper_step, LOW);
    delayMicroseconds(2000);
  }
  
  Serial.println("Motor paso a paso detenido.");
}

void controlar_servo(int angulo) {
  // Control PWM manual para servomotor (1-2ms pulse width)
  int pulseWidth = map(angulo, 0, 180, 1000, 2000);
  
  for (int i = 0; i < 20; i++) { // Enviar señal durante 20ms
    digitalWrite(servo_pin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(servo_pin, LOW);
    delayMicroseconds(20000 - pulseWidth);
  }
}

void parar_todos_motores() {
  Serial.println("\n--- PARANDO TODOS LOS MOTORES ---");
  
  // Parar motor DC
  analogWrite(motorDC_pin1, 0);
  digitalWrite(motorDC_enable, LOW);
  
  // Parar servo (posición neutral)
  controlar_servo(90);
  
  // Parar motor paso a paso
  digitalWrite(stepper_enable, HIGH); // Deshabilitar motor
  
  Serial.println("Todos los motores han sido detenidos.");
  
  // Reactivar después de 2 segundos
  delay(2000);
  digitalWrite(motorDC_enable, HIGH);
  digitalWrite(stepper_enable, LOW);
  Serial.println("Motores reactivados y listos para uso.");
}