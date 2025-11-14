/*  
En el tutorial 5, aprendimos a tener un control proporcional al error, para poder seguir la línea. 
El problema que tenemos ahora es que cuando aumentamos la velocidad base, el robot tiende a oscilar.

Para poder corregir este problema, debemos sumarle una corrección de la potencia del motor, 
que sea proporcional a la derivada del error.

correction_power = Kprop*error + kderiv*(error - error_pasado)/(delta_tiempo).

Como delta_tiempo es constante en el loop:
correction_power = Kprop*error + kderiv*(error - error_pasado).

La corrección derivativa nos ayuda a amortiguar las oscilaciones.
*/

#define PINBUZZER 10
#define PINBOTON  2
#define PINLED    13
#define PIN_Sensor_ON 11

int posicion_ideal = 0;

// cómo modificar el kprop: Comenzar con valores bajos, subir hasta que siga la línea y oscile.
// cómo modificar el kderiv: Comenzar con valores bajos, subir hasta que deje de oscilar.
float Kprop = 1.0;
float Kderiv = 6.0;

int base = 50;
int error_pasado = 0;

void setup() {
    Serial.begin(115200);
    Peripherals_init();
    TB6612FNG_init();
    Sensors_init();

    digitalWrite(PINLED, LOW);
    delay(500);

    Motores(0, 0);

    Serial.println("hola, Quinta y penúltima parte del tutorial");

    delay(500);
    WaitBoton();
    calibracion();

    WaitBoton();
    delay(1000);
}

void loop() {
    readSensors();
    hitos();

    int p = GetPos();
    int error = p - posicion_ideal;
    int d_error = error - error_pasado;

    int correction_power = int(Kprop * error) + int(Kderiv * d_error);

    if (correction_power > 255) {
        correction_power = 255;
    }
    else if (correction_power < -255) {
        correction_power = -255;
    }

    Motores(base + correction_power, base - correction_power);

    error_pasado = error;

    delay(1);
}
