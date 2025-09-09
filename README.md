# Módulos Universidad de Chile

Proyecto de módulos de testeo para robótica - Universidad de Chile

## Estructura del Proyecto

Este repositorio contiene dos módulos principales para testeo de componentes robóticos:

### 📁 testeo_motores/
Módulo para probar diferentes tipos de motores:
- Motores DC con control de velocidad y dirección
- Servomotores con control de posición
- Motores paso a paso con control preciso
- Interfaz interactiva por Monitor Serie
- Funciones de seguridad y parada de emergencia

### 📁 testeo_sensores/
Módulo para monitoreo de sensores en tiempo real:
- Sensor ultrasónico para medición de distancia
- Array de 5 sensores de línea IR
- Sensor de luz ambiente
- **Cálculo de posición relativa** basado en sensores
- **Interfaz gráfica organizada** con ventanas en Monitor Serie
- Visualización de valores individuales y representación gráfica

## Características Principales

✅ **Código Arduino completo y funcional**  
✅ **Organización en carpetas automáticas** (compatible con Arduino IDE)  
✅ **Interfaz de usuario con ventanas organizadas**  
✅ **Monitoreo de valores individuales**  
✅ **Cálculo de posición relativa**  
✅ **Documentación completa en español**  

## Uso

1. Clona el repositorio
2. Abre cualquier módulo en Arduino IDE:
   - `testeo_motores/testeo_motores.ino`
   - `testeo_sensores/testeo_sensores.ino`
3. Conecta los componentes según la documentación
4. Carga el código al Arduino
5. Usa el Monitor Serie para interactuar

## Requisitos

- Arduino IDE
- Arduino Uno/Nano/compatible
- Componentes según el módulo a usar
- Monitor Serie configurado a 9600 baudios

Para más detalles sobre cada módulo, consulta el README.md en cada carpeta.
