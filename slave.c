 /* 
# * Author: David Vela Tirado
# * Software Developer
# * email:  david.vela.tirado@gmail.com
# * 
  */

/* Proceso SLAVE */

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
      char mensaje[LONG_MAX_MENSAJE + 1];
      int longMensaje, checksum, checksumAct, resp, nbytes, i;


   //int master_line[2], line_master[2];
   //int slave_line[2], line_slave[2];

      
/* 3.3 */
      close (0); /* Sólo el proceso master leerá de la consola     */
                 /* Cerramos la entrada aquí para no robarle datos */

	
//open(slave_line[1]); open(line_slave[0]);

int f3,f4;
if ( (f3= open(slave_line,O_WRONLY)) <0)  //CADA UNA CON SUS CORRESPONDIENTES DESCRIPTORES (F1,F2,F3,F4)
{
       perror("open");
       exit(-1);
   }
if ( (f4= open(line_slave,O_RDONLY)) <0)
{
       perror("open");
       exit(-1);
   }






	
	



      if ((nbytes = read (f4, &longMensaje, sizeof (longMensaje))) == -1)
         mostrarErrorSalir ("Error al leer en line_slave[0]");

      while (nbytes) {
         mensaje [0] = 0;

         if (read (f4, mensaje, longMensaje) == -1)
            mostrarErrorSalir ("Error al leer en line_slave[0]");

         if (read (f4, &checksum, sizeof (checksum)) == -1)
            mostrarErrorSalir ("Error al leer en line_slave[0]");

         for (i=0, checksumAct = 0; i < longMensaje; i++)
            checksumAct += mensaje[i];

         if (checksumAct != checksum)
	    resp = !ACK;
         else {
            resp = ACK;
            printf ("%s\n", mensaje);
         }

         if (write (f3, &resp, sizeof (resp)) == -1)
            mostrarErrorSalir ("Error al escribir en slave_line[1]");

         if ((nbytes = read (f4, &longMensaje, sizeof (longMensaje))) == -1)
            mostrarErrorSalir ("Error al leer en line_slave[0]");

      } /* while */

      /* 3.4 */
       

	close(f3); close(f4);



	exit (0);
}
