
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define ARCHIVO_FIFO "Comunicacion FIFO"

int main()
{
  int fd;
  int leidos;
  char buffer[80];
  
  umask(0);
  mknod(ARCHIVO_FIFO, S_IFIFO|0666, 0);
  
  if((fd = open(ARCHIVO_FIFO, O_RDWR)) < 0)
  {
    perror("open");
    exit(-1);
  }
  
  // Aceptar datos a consu,ir a consumir hasta que se envíe la cadena fin
  while (1)
  {
    leidos = read(fd, buffer, 80);
    if (strcmp(buffer, "fin") == 0)
    {
      close(fd);
      return 0;
    }
    printf("\nMensaje recibido: %s", buffer);
  }
  return 0;
    
    
}
