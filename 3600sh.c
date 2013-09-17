/**
 * CS3600, Spring 2013
 * Project 1 Starter Code
 * (c) 2013 Alan Mislove
 *
 * You should use this (very simple) starter code as a basis for 
 * building your shell.  Please see the project handout for more
 * details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#include "3600sh.h"

#define USE(x) (x) = (x)
#define CMDLEN 40

char*getLine(size_t*size);

int main(int argc, char*argv[]) {
  // Code which sets stdout to be unbuffered
  // This is necessary for testing; do not change these lines
  USE(argc);
  USE(argv);
  setvbuf(stdout, NULL, _IONBF, 0); 
  
  // Obtaining necessary information for cmd prompt
  char host[128];
  host[1027] = '\0';
  gethostname(host, 127);
  computer_name(host);
  struct passwd* user = getpwuid(getuid()); 
  char* usrname = user->pw_name;
  char* directory = user->pw_dir;
  
  char*command; //will be char** later
  size_t*size;
  *size = 0;
  // Main loop that reads a command and executes it
  while (1) {         
    // Issue the prompt
      printf("%s@%s:%s> ", usrname, host, directory);
      
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

// Function accepts a host name and edits to only 
// have the computer name
//
void computer_name(char* hostname) {
  int counter;

  for(counter = 0; hostname[counter] != '.'; counter++);

  hostname[counter] = '\0';
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
