 /* 
# * Author: David Vela Tirado
# * Software Developer
# * email:  david.vela.tirado@gmail.com
# * 
  */

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


#define TAM 100



#define LONG_MAX_MENSAJE 127
#define MAX_INTENTOS 10
#define ACK 0



void mostrarErrorSalir (char *mensaje) 
{
   perror(mensaje);
   exit (-1);
}

int main() 
{
  //int master_line[2], line_master[2];
   //int slave_line[2], line_slave[2];
   //int pipe_ret = 0;
   int pid1, pid2,pid3;

   //int status;
umask(0);
mknod(master_line,S_IFIFO|0666,0);
mknod(line_master,S_IFIFO|0666,0);
mknod(slave_line,S_IFIFO|0666,0);
mknod(line_slave,S_IFIFO|0666,0);



char *path;
	path=(char*) malloc(256*sizeof (char));
char *arg[TAM];
arg[0]=path;
   int status;



 if ((pid1 = fork()) == 0)
		 { /* Proceso MASTER */
     			
		strcat(path,"./master");
		execv(path,arg);




		   } /* Fin Proceso master */

	   else if ((pid2=fork()) == 0)
		 { /* Proceso SLAVE */
      
			strcat(path,"./slave");
		execv(path,arg);


		   } /* Fin Proceso slave */

	     else if ((pid3=fork()) == 0)
 		{ 
		strcat(path,"./line");

		execv(path,arg);
	
 
		  } /* Fin Proceso line */



 wait (&status);
 wait (&status);
 wait (&status);
exit(0);

}
