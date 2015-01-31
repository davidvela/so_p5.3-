#/* 
# * Author: David Vela Tirado
# * Software Developer
# * email:  david.vela.tirado@gmail.com
# * 
# */

PHONY: all
CFLAGS=  -Wall 
all:   practica5.3  line master slave


line: line.c 
	gcc $(CFLAGS) line.c  -o line

master: master.c 
	gcc $(CFLAGS) master.c  -o master

slave: slave.c 
	gcc $(CFLAGS) slave.c  -o slave

practica5.3: ejer5.3.c 
	gcc $(CFLAGS) ejer5.3.c  -o practica5.3




clean: 
	-rm -f *.o
	-rm -f practica5.3 slave master line
	
