## Sesión 2: Llamadas al sistema de SA

## 2.1 Llamada al sistema umask

Umask establece la máscara de permisos a ficheros antes de haberlos crearlo (#include <sys/types.h>#include <sys/stat.h>). La función mode_t umask(mode_t mask), establece la máscara
a mask & 0777. La máscara es usada por open como parámetro, si creamos un archivo con campo mode= 0666  y tenemos el valorcomún por defecto de umask=022, este archivo se creará con permisos: 0666 & ~022 = 0644.

## 2.2 Llamadas al sistema chmod y fchmod

Fchmod opera con un archivo ya existente y abierto con open(). La definición de la función va seguida de los siguientes parámetros:

    #include <sys/types.h>
    #include <sys/stat.h>
    int chmod(const char *path, mode_t mode);
    int fchmod(int fildes, mode_t mode);
