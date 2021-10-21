# Módulo 2: Uso de la api de linux

## Notas importantes sobre el módulo dos
- Las bibliotecas que se usan en c para la administración de llamadas al sistema es la libreria libc y glibc (https://github.com/lattera/glibc)
- Todas las funciones del sistema en caso de error devuelven en la variable errno el código de error producido, el cual se puede imprimir con la ayuda de la función perro. Hay que hacer un include a la librería <errno.h>
- Una orden util para rastrear la ejecución de un programa es strace

## 1. Entrada/Salida de archivos regulares

- Pueden realizarse utilizando solamente cinco llamadas: open, read, write, lseeky close (unbuffered I/O), tienes que crear tú el buffer. 

- Cuando abrimos un archivo o lo creamos el kernel devuelve un descriptor de archivo que nos indica en el d.0 la entrad estándar de un proceso, en el d.1 la salida éstandar y en el d.3 la salida de error. Para ver los descriptores debemos usar las siguientes constantes incluidas en <unistd.h>: STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO.

- Cada archivo abierto tiene una posicion de lectura/escritura actual (current file offset) que inicialmente está a 0 a menos que indiquemos la opción O_APPEND cuando se abre el archivo. Podemos consultar la posición actual usando la llamada al sistema lseek 

