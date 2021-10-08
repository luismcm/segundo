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
    
## 3. Orden nice

La orden nice altera el valor de prioridad por defecto de un proceso (heredado por su proceso padre). Acepta los valores desde el intervalo -20 al 19

    nice -valor(€ intervalo) nombre_proceso: aumenta/decrementa en valor el valor de prioridad del proceso. El - no afecta
    renice valor pid_of_proceso: modifica el valor durante la ejecucion del proceso
  
### Actividad nice

- Guión
    
        #! /bin/bash

        a=0
        declare -r MAXIMO=10000
        while [ "$a" -ne $MAXIMO ]
        do
            echo $a
            (( a++ ))
        done
        
        #for (( a=0; a<$MAXIMO; a++ ))
        do
            echo $a
        done

- Running script in background with priority

        sh ./ejercicio.sh num_veces 1000000 &
    
## 4. Orden pstree

Visualiza el árbol de procesos activos

## 5. Orden ps

Muestra la siguiente información sobre los procesos

- PID: nº de identificación del proceso
- USER: usuario que lo lanzó
- PPID: PID del proceso padre
- %CPU: porcentaje entre el tiempo usado realmente y el que lleva en ejecución
- %MEM: fraccion de memoria usada
- VSZ: tamaño virtual del proceso en KB
- RSS: memoria real en KB
- TTY: terminal asociada al proceso
- STAT: estado del proceso
    - R: running or ready
    - S: sleeping
    - T: sTopped
    - D: waiting
    - L: blocked in memory
    
### Actividad 3

    pstree -p : muestra la jerarquía hijo/padre
    ps --pid PID
    Cuando tty == ? => el proceso no está asociado a ningún terminal
    
















