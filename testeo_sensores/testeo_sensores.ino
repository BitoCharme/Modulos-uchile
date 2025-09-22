/*
 * Testeo de 6 Sensores IR - Seguidor de Línea
 * 
 * ¿Que hace?:
 * - Muestra valores individuales de 6 sensores IR.
 * - Detecta línea blanca sobre fondo negro.
 * - Muestra la posición relativa de la línea.
 */

// Pines de sensores (A0 a A5)
const int numSensores = 6;
const int sensores[numSensores] = {A0, A1, A2, A3, A4, A5};

// Variables para los valores de los sensores
int valores[numSensores];

// Umbral para detección de línea blanca
const int umbral = 700; //Aca se puede ajustar el umbral al valor que se quiera

void setup() {
  Serial.begin(9600);
  Serial.println("=== TESTEO DE 6 SENSORES IR ===");
  Serial.println("Detectando línea BLANCA sobre fondo NEGRO...");
  delay(1000);
}

void loop() {
  // Leer sensores
  for (int i = 0; i < numSensores; i++) {
    valores[i] = analogRead(sensores[i]);
  }

  // Mostrar valores individuales
  Serial.print("Valores: ");
  for (int i = 0; i < numSensores; i++) {
    Serial.print(valores[i]);
    if (i < numSensores - 1) Serial.print(" | ");
  }

  // Mostrar detección de línea por cada sensor
  Serial.print("  =>  Detección: ");
  for (int i = 0; i < numSensores; i++) {
    if (valores[i] > umbral) {
      Serial.print("1"); // 1 = Línea detectada
    } else {
      Serial.print("0"); // 0 = Fondo detectado
    }
  }

  // Calcular posición relativa
  String posicion = determinarPosicion(valores);
  Serial.print("  => Posición: ");
  Serial.println(posicion);

  delay(500);
}

String determinarPosicion(int vals[]) {
  bool detecta[numSensores];
  int suma = 0;
  int totalPeso = 0;

  // Asignar pesos de posición (-5 a +5) para los 6 sensores
  // Ejemplo:   S0   S1   S2   S3   S4   S5
  // Pesos:    -5   -3   -1   +1   +3   +5
  int pesos[numSensores] = {-5, -3, -1, 1, 3, 5};

  for (int i = 0; i < numSensores; i++) {
    detecta[i] = vals[i] > umbral;
    if (detecta[i]) {
      suma += pesos[i];
      totalPeso++;
    }
  }

  if (totalPeso == 0) {
    return "LÍNEA PERDIDA";
  }

  float promedio = (float)suma / totalPeso;

  // Interpretar posición
  if (promedio < -3) return "MUY IZQUIERDA";
  else if (promedio < -1.5) return "IZQUIERDA";
  else if (promedio < -0.5) return "LIGERAMENTE IZQUIERDA";
  else if (promedio <= 0.5) return "CENTRADO";
  else if (promedio <= 1.5) return "LIGERAMENTE DERECHA";
  else if (promedio <= 3) return "DERECHA";
  else return "MUY DERECHA";
}
