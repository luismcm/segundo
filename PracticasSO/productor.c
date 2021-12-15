#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define ARCHIVO_FIFO "Comunicacion FIFO"

int main(int argc, char *argv[])
{
  int fd;
  
  //Comprobar argumentos
  if(argc != 2)
  {
    printf("Productor FIFO: faltan argumentos. Hace falta una cadena de caracteres");
    exit(-1);
  } 
  
  //Intentar abrir para escritura el cauce FIFO
  if((fd = open(ARCHIVO_FIFO, O_WRONLY|O_CREAT)) < 0)
  {
    perror("\nError en el open");
    exit(-1);
  }
  
  //Escribir en el cauce FIFO el mensaje introducido como argumento
  if(write(fd, argv[1], strlen(argv[1]+1)) != strlen(argv[1]+1))
  {
    perror("\nError en write");
    exit(-1);
  }
  
  close(fd);
  return 0;
  
}
