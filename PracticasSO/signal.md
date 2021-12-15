Hay dos ficheros envio señal y recibo señal.

recibo_signal.c

    #include <sys/types.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <signal.h>
    #include <errno.h>
    static void sig_USR_hdlr(int sigNum)
    {
      if(sigNum == SIGUSR1) printf("\nRecibida la señal SIGUSR1\n\n");
      else if(sigNum == SIGUSR2) printf("\nRecibida la señal SIGUSR2\n\n");
    }
    
    int main(int argc, char *argv[])
    {
      struct sigaction sig_USR_nact;
      
      if(stvbuf(stdout, NULL, _IONBF, 0))
        perror("\nError en setvbuf");
       
       //Inicializar la estructura sig_USR_na para especificar la nueva acción para la señal
       sig_USR_nact.sa_handler = sig_USR_hdlr;
       
       //'sigemptyset' inicia el conjunto deseñales dado al conjunto vacio
       sigemptyset(&sig_USR_nact.sa_mask);
       sig_USR_nact.sa_flags = 0;
       
       //Establecer mi manejador particular de señal para SIGUSR1
       if(sigaction(SIGUSR1.&sig_USR_nact.NULL) < 0)
       {
          perror("Error al intentar establecer el manejador de señal para SIGUSR1");
          exit(-1);
       }
       
       //Establecer mi manejador particular de señal para SIGUSR2
       if(sigaction(SIGUSR2.&sig_USR_nact.NULL) < 0)
       {
          perror("Error al intentar establecer el manejador de señal para SIGUSR2");
          exit(-1);
       }
       
       
    }



envio_signal.c


      #include <sys/types.h> //POSIX Standard: 2.6 Primitive System Data Types
      // <sys/types.h>
      #include<limits.h> //Incluye <bits/posix1_lim.h> POSIX Standard: 2.9.2 //Minimum
      //Values Added to <limits.h> y <bits/posix2_lim.h>
      #include <unistd.h> //POSIX Standard: 2.10 Symbolic Constants <unistd.h>
      #include <sys/stat.h>
      #include <stdio.h>
      #include <stdlib.h>
      #include <signal.h>
      #include <errno.h>
      int main(int argc, char *argv[])
       {
       long int pid;
       int signal;
       if(argc<3) {
       printf("\nSintaxis de ejecución: envioSignal [012] <PID>\n\n");
       exit(-1);
       }
       pid= strtol(argv[2],NULL,10);
       if(pid == LONG_MIN || pid == LONG_MAX)
       {
       if(pid == LONG_MIN)
       printf("\nError por desbordamiento inferior LONG_MIN %d",pid);
       else
       printf("\nError por desbordamiento superior LONG_MAX %d",pid);
       perror("\nError en strtol");
       exit(-1);
       }
       signal=atoi(argv[1]);
       switch(signal) {
       case 0: //SIGTERM
       kill(pid,SIGTERM); break;
       case 1: //SIGUSR1
       kill(pid,SIGUSR1); break;
       case 2: //SIGUSR2
       kill(pid,SIGUSR2); break;
       default : // not in [012]
       printf("\n No puedo enviar ese tipo de señal");
       }
      }
























