# Testeo de Sensores

Este módulo permite monitorear en tiempo real múltiples sensores y calcular la posición relativa del robot.

## Características

- **Sensor Ultrasónico**: Medición de distancia (HC-SR04)
- **Sensores de Línea**: Array de 5 sensores IR para seguimiento
- **Sensor de Luz**: Medición de intensidad lumínica (LDR)
- **Cálculo de Posición Relativa**: Basado en sensores de línea

## Conexiones

### Sensor Ultrasónico (HC-SR04)
- Pin 12: Trigger
- Pin 11: Echo

### Sensores de Línea
- Pin A0: Sensor 0 (izquierda)
- Pin A1: Sensor 1
- Pin A2: Sensor 2 (centro)
- Pin A3: Sensor 3
- Pin A4: Sensor 4 (derecha)

### Sensor de Luz
- Pin A5: Entrada analógica LDR

## Interfaz de Usuario

El programa muestra una **ventana organizada** en el Monitor Serie con:

- Valores individuales de cada sensor
- Representación gráfica en barras
- Posición relativa calculada (-2.0 a +2.0)
- Estado del sistema en tiempo real

## Comandos Interactivos

- `c`: Calibrar sensores de línea
- `r`: Reiniciar todas las lecturas
- `h`: Mostrar ayuda completa

## Cálculo de Posición Relativa

La posición se calcula usando un **promedio ponderado** de los sensores de línea:

- **-2.0**: Línea completamente a la izquierda
- **0.0**: Línea en el centro
- **+2.0**: Línea completamente a la derecha

## Uso

1. Abrir `testeo_sensores.ino` en Arduino IDE
2. Cargar el código al Arduino
3. Abrir Monitor Serie (9600 baud)
4. Observar los valores en tiempo real
5. Usar comandos para calibración y control

## Visualización

El programa utiliza caracteres especiales para crear una interfaz gráfica en el Monitor Serie, mostrando barras de progreso y marcos organizados para una mejor visualización de los datos.