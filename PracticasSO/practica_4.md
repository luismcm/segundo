# Módulo 2: Uso de la api de linux

## Notas importantes sobre el módulo dos
- Las bibliotecas que se usan en c para la administración de llamadas al sistema es la libreria libc y glibc (https://github.com/lattera/glibc)
- Todas las funciones del sistema en caso de error devuelven en la variable errno el código de error producido, el cual se puede imprimir con la ayuda de la función perro. Hay que hacer un include a la librería <errno.h>
- Una orden util para rastrear la ejecución de un programa es strace

## 1. Entrada/Salida de archivos regulares

- Pueden realizarse utilizando solamente cinco llamadas: open, read, write, lseeky close (unbuffered I/O), tienes que crear tú el buffer. 

- Cuando abrimos un archivo o lo creamos el kernel devuelve un descriptor de archivo que nos indica en el d.0 la entrad estándar de un proceso, en el d.1 la salida éstandar y en el d.3 la salida de error. Para ver los descriptores debemos usar las siguientes constantes incluidas en <unistd.h>: STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO.

- Cada archivo abierto tiene una posicion de lectura/escritura actual (current file offset) que inicialmente está a 0 a menos que indiquemos la opción O_APPEND cuando se abre el archivo. Podemos consultar la posición actual usando la llamada al sistema lseek 

### Actividad 1

Vamos a usar la llamada sobrecargada open:

    int open(const char *ruta, int flags);                  // Abre un archivo
    int open(const char *ruta, int flags, mode_t modo);     // Crea un archivo
    
También usaremos la llamada close

    /**
        fd es un entero pero por dentro guarada el file descriptor y el número de la dirección de memoria del archivo con el que estamos tratando
    **/
    
    int close(int fd)

### Ejercicio 1: ¿Qué hace el siguiente programa? Probad tras la ejecución del programa las siguientes órdenes del shell: $> cat archivo y $> od -c archivo


        /*
                tarea1.c
                Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
        */
        #include<unistd.h>
        #include<stdio.h>
        #include<stdlib.h>
        #include<sys/types.h>  	/* Primitive system data types for abstraction\
			                        of implementation-dependent data types.
			                        POSIX Standard: 2.6 Primitive System Data Types
			                        <sys/types.h>
			                    */
        #include<sys/stat.h>
        #include<fcntl.h>
        #include<errno.h>

        char buf1[]="abcdefghij";
        char buf2[]="ABCDEFGHIJ";

        int main(int argc, char *argv[])
        {
            int fd;

            if( (fd=open("archivo",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
	            printf("\nError %d en open",errno);
	            perror("\nError en open");
	            exit(EXIT_FAILURE);
            }
            if(write(fd,buf1,10) != 10) {
	            perror("\nError en primer write");
	            exit(EXIT_FAILURE);
            }

            if(lseek(fd,40,SEEK_SET) < 0) {
	            perror("\nError en lseek");
	            exit(EXIT_FAILURE);
            }

            if(write(fd,buf2,10) != 10) {
	            perror("\nError en segundo write");
	            exit(EXIT_FAILURE);
            }

            return EXIT_SUCCESS;
        }
	
Primero el programa abre un archivo de nombre archivo con los flags O_CREAT para crear el archivo en caso de que no exista, O_TRUNC para truncar el archivo a longitud 0 en caso de que ya exista, O_WRONLY para especificar el modo escritura, S_IRUSR y S_IWUSR para garantizar permiso de lectura y escritura, respectivamente, al usuario. Imprimiendo por la salida estándar el número de error en caso de error, almacenado en errno.

Luego escribimos en el archivo hasta 10B empezando por la posición a la que referencia buf1, en caso de que write() devuelva un valor distinto de 10 (el número de bytes que queremos escribir) notificamos el error en la salida de error.

Ahora situamos el offset del archivo a 40B desde el inicio del fichero, flag SEEK_SET, esta opción nos permite situarnos en una posición mayor a la longitud actual del fichero, que posteriormente si realizamos una escritura, rellenará las posiciones del fichero inexistentes con el carácter nulo \0.

Finalmente escribimos el buffer buff2 en el fichero.

### Ejercicio 2: Implementa un programa que realice la siguiente funcionalidad. El programa acepta como argumento el nombre de un archivo (pathname), lo abre y lo lee en bloques de tamaño 80 Bytes, y crea un nuevo archivo de salida, salida.txt.


	
	/*
		ejercicio2.c
	*/
	#include<unistd.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include<sys/types.h>
	#include<sys/stat.h>
	#include<fcntl.h>
	#include<errno.h>
	#include <string.h>

	#define BLOCK_SIZE 80
	char buf[BLOCK_SIZE];
	int read_blocks(int);

	int main(int argc, char *argv[]){
  		int fd;
  		int std_read = 1;
  		if(argc == 1){
    			printf("Se ha seleccionado la entrada estándar como archivo de entrada\n");
    			fd = STDIN_FILENO;
    			read_blocks(fd);
  		}
  		else{
    			if(argc == 2){
      				if( (fd=open(argv[1], O_RDONLY)) < 0){
        				printf("\nError %d en open",errno);
        				perror("\nError en open");
        				exit(EXIT_FAILURE);
      				}

      				read_blocks(fd);
      				if(close(fd) < 0){
        				printf("\nError %d en close",errno);
        				perror("\nError en close");
        				exit(EXIT_FAILURE);
      				}
    			}
    			else{
      				printf("\nError, invalid number of arguments\nUso: ejercicio2 [pathname_to_file]");
      				exit(EXIT_FAILURE);
    			}
  		}

  			return EXIT_SUCCESS;
	}
	
	int read_blocks(int _fd)
	{
		int fd_out;
		int count = 0;
		int eof = 0;
		if((fd_out=open("salida.txt", O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWRUSR)) < 0)
		{
			printf("\nError %d en open", errno);
			perror("\nError en open");
			exit(EXIT_FAILURE);
		}
		
		for (int i = 0; !eof; ++i)
		{
			char buf_w[BLOCK_SIZE+20];
			count = read(_fd, buf, BLOCK_SIZE);
			sprintf(buf_w, "\nBloque %i : \n", i, count, buf);
			
			if((write(fd_out, buf_w, strlen(bufw))) < 0)
			{
				printf("\nError en %d write", errno);
				perror("\nError en el write del fichero de salida");
				close_fd(fd_out)
				exit(EXIT_FAILURE);
			}
			
			if(count < BLOCK_SIZE)
				eof = 1;
		}
		
		close_fd(fd_out);
		return EXIT_SUCCESS;
		
	}


- Saca el número de bloques de un archivo:
	
	int size_fd = lseek(fd, 0, SEEK_END);
	int n_blocks = size_fd / BLOCK_SIZE ; // : )


### Ejercicio 3: ¿Qué hace el siguiente programa?

		/*
		tarea2.c
		Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
		*/

		#include<unistd.h>  /* POSIX Standard: 2.10 Symbolic Constants <unistd.h>
				     */
		#include<stdio.h>
		#include<stdlib.h>
		#include<sys/types.h>  /* Primitive system data types for abstraction	\
					   of implementation-dependent data types.
					   POSIX Standard: 2.6 Primitive System Data Types
					   <sys/types.h>
				       */
		#include<sys/stat.h>
		#include<stdio.h>
		#include<errno.h>
		#include<string.h>

		int main(int argc, char *argv[])
		{
		int i;
		struct stat atributos;
		char tipoArchivo[30];

		if(argc<2) {
			printf("\nSintaxis de ejecucion: tarea2 [<nombre_archivo>]+\n\n");
			exit(EXIT_FAILURE);
		}
		for(i=1;i<argc;i++) {
			printf("%s: ", argv[i]);
			if(lstat(argv[i],&atributos) < 0) {
				printf("\nError al intentar acceder a los atributos de %s",argv[i]);
				perror("\nError en lstat");
			}
			else {
				if(S_ISREG(atributos.st_mode)) strcpy(tipoArchivo,"Regular");
				else if(S_ISDIR(atributos.st_mode)) strcpy(tipoArchivo,"Directorio");
				else if(S_ISCHR(atributos.st_mode)) strcpy(tipoArchivo,"Especial de caracteres");
				else if(S_ISBLK(atributos.st_mode)) strcpy(tipoArchivo,"Especial de bloques");
				else if(S_ISFIFO(atributos.st_mode)) strcpy(tipoArchivo,"Tuberia con nombre (FIFO)");
				else if(S_ISLNK(atributos.st_mode)) strcpy(tipoArchivo,"Enlace relativo (soft)");
				else if(S_ISSOCK(atributos.st_mode)) strcpy(tipoArchivo,"Socket");
				else strcpy(tipoArchivo,"Tipo de archivo desconocido");
				printf("%s\n",tipoArchivo);
			}
		}

		return EXIT_SUCCESS;
		}

Mira los metadatos de los archivos pasados como parametro con lstat, guardando la información en la estructura de estado. Más tarde se comprueba el tipo de archivo con el atributo st_mode y se imprime el tipo por pantalla.







