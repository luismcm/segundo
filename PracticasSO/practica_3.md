# Práctica 3

## Monitorización del sistema

- Control y gestión de cpu/memoria
- Control de dispositivos
- Saber repartir los recursos del sistema
- Conocer metadatos de un archivo

## 1. Orden uptime

    uptime: muestra hora, tiempo que lleva encendido, nº usuarios, carga media del sistema los ultimos 1, 5 y 15 minutos
    w: uptime pero más detallado
  
 La carga normal de un sistema multicure es nº cores*1
 
## 2. Orden time

La orden time mide el tiempo de ejecución de un programa, el tiempo usado por el sistema y por el usuario.

    time nombre_programa => t.espera = t.real - t.user -t.sys
    
