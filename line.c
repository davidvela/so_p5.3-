 /* 
# * Author: David Vela Tirado
# * Software Developer
# * email:  david.vela.tirado@gmail.com
# * 
  */

/* Proceso LINE */
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sys/stat.h>
#include<stdlib.h>

#define master_line "master_line"
#define line_master "line_master"
#define slave_line "slave_line"
#define line_slave "line_slave"


#define LONG_MAX_MENSAJE 127
#define MAX_INTENTOS 10
#define ACK 0



void mostrarErrorSalir (char *mensaje) {
   perror(mensaje);
   exit (-1);
}



int main()
{
	int f1,f2,f3,f4;
	
//   int master_line[2], line_master[2];
 //  int slave_line[2], line_slave[2];

	char mensaje [LONG_MAX_MENSAJE + 1];
        int longMensaje, checksum, status, resp, nbytes, i, k;


      /* 3.5 */

	//open(line_slave[1]);   open(slave_line[0]);
	//open(line_master[1]);   open(master_line[0]);


	//close(line_slave[0]);   close(slave_line[1]);
	//close(line_master[0]);   close(master_line[1]);


if ( (f1= open(master_line,O_RDONLY)) <0)  //CADA UNA CON SUS CORRESPONDIENTES DESCRIPTORES (F1,F2,F3,F4)
{
       perror("open");
       exit(-1);
   }
if ( (f2= open(line_master,O_WRONLY)) <0)
{
       perror("open");
       exit(-1);
   }
if ( (f3= open(slave_line,O_RDONLY)) <0)  //CADA UNA CON SUS CORRESPONDIENTES DESCRIPTORES (F1,F2,F3,F4)
{
       perror("open");
       exit(-1);
   }
if ( (f4= open(line_slave,O_WRONLY)) <0)
{
       perror("open");
       exit(-1);
   }









      close (0);
      srand ((unsigned) time (NULL)); /* Inicializa el generador de numeros aleatorios */

      if ((nbytes = read (f1, &longMensaje, sizeof (longMensaje))) == -1)
         mostrarErrorSalir ("Error al leer en master_line[0]");

      while (nbytes) {
         if (write (f4, &longMensaje, sizeof (longMensaje)) == -1)
            mostrarErrorSalir ("Error al escribir en line_slave[1]");

         mensaje [0] = 0;

         if (read (f1, mensaje, longMensaje) == -1)
            mostrarErrorSalir ("Error al leer en master_line[0]");

         if (read (f1, &checksum, sizeof (checksum)) == -1)
            mostrarErrorSalir ("Error al leer en master_line[0]");

         k = rand () % 10;

         if (k < 3) {
            for (i = 0; i < k + 1; i++)
               mensaje [rand () % longMensaje] = 32 + rand () % 96;

         if (k == 3)
            checksum = rand ()% longMensaje * 128;
         } 

         if (write (f4, mensaje, longMensaje) == -1)
            mostrarErrorSalir ("Error al escribir en line_slave[1]");

         if (write (f4, &checksum, sizeof (checksum)) == -1)
            mostrarErrorSalir ("Error al escribir en line_slave[1]");

         








if (read (f3, &resp, sizeof (resp)) == -1)
            mostrarErrorSalir ("Error al leer en slave_line[0]");

         if (write (f2, &resp, sizeof (resp)) == -1)
            mostrarErrorSalir ("Error al escribir en line_master[1]");

         if ((nbytes=read (f1, &longMensaje, sizeof(longMensaje))) == -1)
            mostrarErrorSalir ("Error al leer en master_line[0]");

      } /* while */

      /* 3.6 */
     
	close(f1);   close(f2);
	close(f3);   close(f4);



   //   wait (&status); /* Esperar a que los procesos hijos */
    //  wait (&status); /* hayan finalizado                 */
	      
     // exit (0);
return 0;
}
