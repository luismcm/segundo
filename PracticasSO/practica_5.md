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

### Ejercicio 1: ¿Qué hace este programa?

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

### Ejercicio 2: Cambia los permisos de todos los archivos de un directorio


        #include<sys/types.h>
        #include<sys/stat.h>
        #include<fcntl.h>
        #include<stdio.h>
        #include<errno.h>
        #include<stdlib.h>
        #include<dirent.h>
        #include<string.h>

        void closedir_safe(DIR*);

        int main(int argc, char *argv[]){
          size_t name_len = strlen(argv[0])-2;
          char name[name_len];
          char *name_p = &argv[0][2];
          sprintf(name,"%.*s", (int)name_len, name_p);

          if(argc != 3){
            printf("Sintaxis de ejecucion: %s <nombre_directorio> <mascara_octal_4d>\n\n"
            , argv[0]);

            exit(EXIT_FAILURE);
          }

          long int mask;
          if((mask=strtol(argv[2], (char**)NULL, 8)) == 0 && argv[2] != 0 ){
            printf("Error %d en strtol(%s)\n",errno, argv[2]);
            perror("Error en strtol\n");
            exit(EXIT_FAILURE);
          }
          //printf("mask: %li\n", mask);

          DIR* dir;

          if( (dir=opendir(argv[1])) == NULL ){
            printf("Error %d en opendir(%s)\n",errno, argv[1]);
            perror("Error en opendir\n");
            exit(EXIT_FAILURE);
          }

          struct dirent *dirp;
          struct stat attr;
          unsigned int permisos_antiguos;

          int i = 0;
          for(errno = 0; (dirp=readdir(dir)) != NULL; errno = 0, ++i){
            if(errno != 0){
              printf("Error %d en readdir\n",errno);
              perror("Error en readdir\n");
              exit(EXIT_FAILURE);
            }

            if( strcmp(dirp->d_name, ".")!=0 && strcmp(dirp->d_name, "..")!=0 && strcmp(dirp->d_name, name)!=0){
              if(lstat(dirp->d_name, &attr) < 0){
                printf("Error %d al intentar acceder a los atributos de %s\n", errno, dirp->d_name);
                perror("Error en lstat\n");
              }else{
                permisos_antiguos = ((attr.st_mode & S_IRUSR)|(attr.st_mode & S_IWUSR)|(attr.st_mode & S_IXUSR)|/*owner*/
                (attr.st_mode & S_IRGRP)|(attr.st_mode & S_IWGRP)|(attr.st_mode & S_IXGRP)|/*group*/
                (attr.st_mode & S_IROTH)|(attr.st_mode & S_IWOTH)|(attr.st_mode & S_IXOTH));/*other*/
                if( chmod(dirp->d_name, mask) < 0 ){
                  printf("Error %d en chmod para %s\n", errno, dirp->d_name);
                  printf("%s : <%d> <%.4o>\n", dirp->d_name, errno, permisos_antiguos);
                }else{
                  printf("%s : <%.4o> <%.4o>\n", dirp->d_name, permisos_antiguos, (unsigned int)mask);
                }
              }
            }

          }


          closedir_safe(dir);
          return EXIT_SUCCESS;
        }

        void closedir_safe(DIR* dir){
          if(closedir(dir) < 0){
            printf("Error %d en closedir\n",errno);
            perror("Error en closedir\n");
            exit(EXIT_FAILURE);
          }
        }
            
 
### Uso de nftw
            
        #include<sys/types.h>
        #include<sys/stat.h>
        #include<fcntl.h>
        #include<stdio.h>
        #include<errno.h>
        #include<stdlib.h>
        #include<dirent.h>
        #include<string.h>
        #include <ftw.h>
        
        int visitar(const char* path, const struct stat* stat, int flags, struct FTW* ftw)
        {
            printf("\nPath: %s Modo: %o", path, stat->st_mode);
            return 0;
        }
        
        int main(int argc,char** argv)
        {
            if((nftw(argc >= 2 ? argv[1] : ".", visitar, 10, 0)) != 0)
            {
                perror("Error en nftw");
            }
        }
            
            
            
            
            
