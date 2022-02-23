#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

const float SUCCESS_RATE = 0.6;

const char* NAME_ARRAY[ ]= { "Alice", "Bob", "Cathy", "David"};

int waitTimeInSecs = 1;

int shouldRun = 1;

int nameIndex;

pid_t childPid;// Only used in partner1.c


//  PURPOSE:  To return a pseudo-random floating point number uniformly
//distributed in [0.0 .. 1.0) when drand48() is acting-up.  No parameters.

float rand0To1(){
  int remainder = rand() % 1024;
  return( ((float)remainder) / 1024 );
}


void sigUsr1Handler(int sigNum){
  // YOUR CODE HERE
  sleep(waitTimeInSecs);
  if (rand0To1() <= SUCCESS_RATE){
    printf("%s \"Caught it!  Here it comes, catch!\"\n",NAME_ARRAY[nameIndex]);
    printf("%s takes one step back.\n",NAME_ARRAY[nameIndex]);
    kill(getppid(), SIGUSR1);
    waitTimeInSecs++;
  }
  else{
    printf("%s (Splash!)\n",NAME_ARRAY[nameIndex]);
    printf("%s \"Dang!  I'm all wet!\"\n",NAME_ARRAY[nameIndex]);
    kill(getppid(), SIGUSR2);
    shouldRun = 0;
  }
}



void sigUsr2Handler(int sigNum){
  // YOUR CODE HERE
  printf("%s \"Okay, I'll go.\"\n",NAME_ARRAY[nameIndex]);
  shouldRun = 0;
}


int main(int argc, char* argv[]){
  srand(getpid());
  // YOUR CODE HERE
  if (argc != 2){ 
    fprintf(stderr,"Usage:\tpartner1 (nameIndex)\n"); 
    exit(EXIT_SUCCESS);
  }  

  int input = strtol(argv[1], NULL, 10);
  if (input >= 0 && input <= 2){
    nameIndex = input;
  }
  else {
    fprintf(stderr,"nameIndex must be in [0,1,2]"); 
    exit(EXIT_FAILURE);
  }
  
  struct sigaction sigact;
  memset(&sigact,'\0',sizeof(sigact));
  sigact.sa_handler = sigUsr1Handler;
  sigaction(SIGUSR1,&sigact,NULL);

  memset(&sigact,'\0',sizeof(sigact));
  sigact.sa_handler = sigUsr2Handler;
  sigaction(SIGUSR2,&sigact,NULL);

  while(shouldRun)
    {
      sleep(1);
    }

  return(EXIT_SUCCESS);
}
