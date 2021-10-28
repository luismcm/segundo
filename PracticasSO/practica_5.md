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

## Ejercicio 1: ¿Qué hace este programa?

    #include<sys/types.h>#include<unistd.h>
    #include<stdlib.h>
    #include<sys/stat.h>
    #include<fcntl.h>
    #include<stdio.h>
    #include<errno.h>
    
        int main(int argc, char *argv[]){
            int fd1,fd2;
            struct stat atributos;
        
            //CREACION DE ARCHIVOS
            if( (fd1=open("archivo1",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0){
                printf("\nError %d en open(archivo1,...)",errno);
                perror("\nError en open");
                exit(-1);
            }
            
             umask(0);
             
            if( (fd2=open("archivo2",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0){
                printf("\nError %d en open(archivo2,...)",errno);
                perror("\nError en open");
                exit(-1);
            }
            
            //CAMBIO DE PERMISOS
            if(stat("archivo1",&atributos) < 0) {
            printf("\nError al intentar acceder a los atributos de archivo1");
            perror("\nError en lstat");
            exit(-1);
            }
            
            if(chmod("archivo1", (atributos.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
            perror("\nError en chmod para archivo1");
            exit(-1);
            }
            
            if(chmod("archivo2",S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH) < 0) {
            perror("\nError en chmod para archivo2");
            exit(-1);
            }
            
            close(fd1);
            close(fd2);
            return 0;
         }
            
* El programa habre el archivo 1:

    int open(const char *pathname, int flags, mode_t mode);

    Como podemos observar en el parámetro flags = O_CREAT|O_TRUNC|O_WRONLY, lo que hace es que si el archivo no está creado; lo crea, si existe lo pone con una       longitud 0 y le pone de access mode write only. En el parámetro mode_t mode = S_IRGRP|S_IWGRP|S_IXGRP, primero le da al grupo permisos de de lectura, de           escritura o de ejecución.

* Se repite el procedimiento con el archivo 2

* Para el cambio de permisos de los archivos necesitamos acceso a los atributos de los mismos. Para ello completaremos la estructura de atributos definida arriba con la función stat de la siguiente manera:

        int stat(const char *restrict pathname, struct stat *restrict statbuf);
    
* Ahora cambiamos los permisos del archivo con chmod:

        int chmod(const char *pathname, mascara);

    Para establecer la máscara le quitamos al archivo los permisos de ejecucion en el grupo, para ello realizaciomos la siguiente operación *atributos.st_mode &       ~S_IXGRP* después le añadimos los permisos que tenía antes haciendo un *OR a S_ISGID*





            
            
            
            
            
            
            
            
            
