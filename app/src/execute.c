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

void execute_command(int numberInput, char **inputs, int bBackground){
	pid_t child_pid;
  	pid_t pid;
  	int status = 0;
  	struct timespec start_time, end_time;

  	child_pid = fork();

  	if ( child_pid == 0 ) {

  		/* get start timer*/
  		clock_gettime(CLOCK_REALTIME, &start_time);

	    execvp(inputs[0], inputs);
	    perror("fork child process error condition!" );
  	} else {
  		
  		if(!bBackground){
  			pid = wait(&child_pid);
  		}
  		clock_gettime(CLOCK_REALTIME, &end_time);
  		get_process_status(start_time, end_time);
  	}
}

int read_input(){
	char ** res = NULL;
	char * p = NULL;
	char pchCommand[MAX_COMMAND_LENGTH];
	int nTokens = 0;
	int bBackground = FALSE;

	printf("Digite um comando: \n");
	
	fgets(pchCommand, sizeof(pchCommand), stdin);
    p = strtok (pchCommand, "\r\n\r\n");
	p = strtok (pchCommand, " ");

	while (p != NULL) {
		res = realloc (res, sizeof (char*) * ++nTokens);

		if (res == NULL){
			perror("Alloc memory failed");
		}

		res[nTokens-1] = p;

		p = strtok (NULL, " ");
	}

	res = realloc (res, sizeof (char *) * (++nTokens));
	res[nTokens-1] = 0;

	for(int i = 0; i < nTokens-1; ++i){
		char *aux = res[i];
		if(aux[0] == EOF){
			return FALSE;
		}
		if(strcmp("exit", res[i]) == 0){
			return FALSE;
		}

		if(strncmp(res[i], "cd", 2) == 0){
			char * path = res[i];
			path += 2;
			chdir(path);
			free(res);
			return TRUE;
		}

		if(strcmp("&", res[i]) == 0){
			bBackground = TRUE;
		}

	}

	execute_command(nTokens, res, bBackground);
	free(res);
	return TRUE;
}

int main(int argc, char **argv) {

	if(argc > 1){
		execute_command(argc, &argv[1], FALSE);
	} else {
		while(read_input());
	}

	return EXIT_SUCCESS;
}
