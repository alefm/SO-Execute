/********************************************************
*
* Author: Alef Martins
* Sistema Operacionais - UNIVALI
*
********************************************************/

#include <execute.h>

void get_process_status(struct timespec start_time, struct timespec end_time){
	struct rusage usage;

	getrusage(RUSAGE_CHILDREN, &usage);

	double user_millis = (usage.ru_utime.tv_sec) * 1000 + (usage.ru_utime.tv_usec) / 1000;
	double system_millis = (usage.ru_stime.tv_sec) * 1000 + (usage.ru_stime.tv_usec) / 1000;
	
	double elapsedTime = (end_time.tv_sec - start_time.tv_sec) * 1e6 + (end_time.tv_nsec - start_time.tv_nsec) / 1e3;

	printf("\n\n* Tempo de CPU utlizado usuario %.0fms sistema %.0fms\n", user_millis, system_millis);
	printf("* Tempo gasto para executar o comando %.0f microseconds\n", elapsedTime);
	printf("* Numero de vezes que o processo foi interrompido involuntariamente: %ld\n", usage.ru_nivcsw);
	printf("* Numero de vezes que o processo foi interrompido voluntariamente: %ld\n", usage.ru_nvcsw);
}

void execute_command(int numberInput, char **inputs){
	pid_t child_pid;
  	pid_t pid;
  	int status = 0;
  	struct timespec start_time, end_time;


  	child_pid = fork();

  	if ( child_pid == 0 ) {

  		/* get start timer*/
  		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);

	    execv("/bin/ls", &inputs[1]);
	    perror("fork child process error condition!" );
  	} else {
  		pid = wait(&child_pid);
  		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
  		get_process_status(start_time, end_time);
  	}
}

int main(int argc, char **argv) {

	if(argc > 1){
		execute_command(argc, argv);
	} else {

	}

	return EXIT_SUCCESS;
}
