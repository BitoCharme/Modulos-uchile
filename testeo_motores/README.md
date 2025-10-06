# Testeo de Motores

Este módulo permite realizar pruebas completas de diferentes tipos de motores utilizados en proyectos de robótica.

## Características

- **Motor DC**: Control de velocidad y dirección con PWM
- **Servomotor**: Control de posición angular (0-180°)
- **Motor Paso a Paso**: Control preciso de movimiento con driver A4988

## Conexiones

### Motor DC
- Pin 9 (PWM): Control de velocidad
- Pin 8: Control de dirección  
- Pin 7: Enable

### Servomotor
- Pin 6: Señal PWM

### Motor Paso a Paso
- Pin 5: Step (pulso)
- Pin 4: Direction (dirección)
- Pin 3: Enable

## Uso

1. Abrir el archivo `testeo_motores.ino` en Arduino IDE
2. Cargar el código al Arduino
3. Abrir el Monitor Serie (9600 baud)
4. Seguir el menú interactivo para probar cada motor

## Funciones Principales

- `testear_motor_DC()`: Prueba completa del motor DC
- `testear_servomotor()`: Movimiento del servo en diferentes posiciones
- `testear_motor_paso_a_paso()`: Rotación en ambos sentidos
- `parar_todos_motores()`: Detención segura de todos los motores

## Seguridad

- Todos los motores se detienen automáticamente al final de cada prueba
- Función de parada de emergencia disponible en el menú
- Control de habilitación para prevenir daños