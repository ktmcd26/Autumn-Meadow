/**
 * CS3600, Spring 2013
 * Project 1 Starter Code
 * (c) 2013 Alan Mislove
 *
 * You should use this (very simple) starter code as a basis for 
 * building your shell.  Please see the project handout for more
 * details.
 */

#include "3600sh.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

#define USE(x) (x) = (x)
#define CMDLEN 40

char*getLine(size_t*size);

int main(int argc, char*argv[]) {
  // Code which sets stdout to be unbuffered
  // This is necessary for testing; do not change these lines
  USE(argc);
  USE(argv);
  setvbuf(stdout, NULL, _IONBF, 0); 
  struct passwd pwd;
  const struct passwd* uidata = getpwuid(getuid());
  char*name =(char*) uidata->pw_name;
  char*command; //will be char** later
  size_t*size;
  *size = 0;
  // Main loop that reads a command and executes it
  while (1) {         
    // You should issue the prompt here
      printf("%s :",name);
	  command = getLine(size);
	  printf("%d %s\n",*size,command);
    // You should read in the command and execute it here
    
    // You should probably remove this; right now, it
    // just exits
    do_exit();
  }
	free(command);
  return 0;
}



// Function which exits, printing the necessary message
//
void do_exit() {
  printf("So long and thanks for all the fish!\n");
  exit(0);
}

//collects line of user input

char*getLine(size_t*size){
	int c, args = 0;
	char*dest = (char*) malloc(CMDLEN);
	char*destPt = dest;
	if(dest == NULL)
		return 0;
	
	size_t lenmax = CMDLEN, count = lenmax;
	for(;;){
		c = fgetc(stdin);
		if(c==EOF)
			c = '\n';
		count--;
		if(count == 0)
			break;
		if(c ==' '||c == '\t')
			args++;
		
		if((*dest++ = c) == '\n')
			break;
	}
	*dest = '\0';
	*size = args;
	return destPt;
}