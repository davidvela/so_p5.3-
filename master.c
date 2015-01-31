 /* 
# * Author: David Vela Tirado
# * Software Developer
# * email:  david.vela.tirado@gmail.com
# * 
  */

/* Proceso MASTER */

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
   
   //int master_line[2], line_master[2];
   //int slave_line[2], line_slave[2];   

char mensaje [LONG_MAX_MENSAJE + 1];
int checksum, i, resp, intentos, longMensaje;



      

/* 3.1 */
int f1,f2;
if ( (f1= open(master_line,O_WRONLY)) <0)  //CADA UNA CON SUS CORRESPONDIENTES DESCRIPTORES (F1,F2,F3,F4)
{
       perror("open");
       exit(-1);
   }
if ( (f2= open(line_master,O_RDONLY)) <0) 
{
       perror("open");
       exit(-1);
   }



	


//open(master_line[1]); open(line_master[0]);



      while (scanf ("%s", mensaje) != EOF) {
         intentos = MAX_INTENTOS;
         longMensaje = strlen (mensaje) + 1;

         do {
            if (write (f1, &longMensaje, sizeof (longMensaje)) == -1)
               mostrarErrorSalir ("Error al escribir en master_line[1]");

            if (write (f1, mensaje, longMensaje) == -1)
               mostrarErrorSalir ("Error al escribir en master_line[1]");

            for (i=0, checksum=0; i < longMensaje; i++)
               checksum += mensaje[i]; 

            if (write (f1, &checksum, sizeof (checksum)) == -1)
               mostrarErrorSalir ("Error al escribir en master_line[1]");

            intentos--;

            if (read (f2, &resp, sizeof (resp)) == -1)
               mostrarErrorSalir ("Error al leer en line_master[0]");

         } while ((resp != ACK) && intentos);

         if (resp != ACK) {
            fprintf (stderr, "Demasiados errores en la línea.\n");
            close (f1);
            close (f2);
            exit (2);
         } 

         mensaje [0] = 0;

      } /* while */

      /* 3.2 */

	close(f1); close(f2);




      exit (0); 


   } /* Fin Proceso master */
