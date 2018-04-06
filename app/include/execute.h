/********************************************************
*
* Author: Alef Martins
* Sistema Operacionais - UNIVALI
*
********************************************************/
#ifndef __EXECUTE_H__
#define __EXECUTE_H__

/**************************************************************************
 * INCLUDES
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>
#include <time.h>
#include <sys/resource.h>

/**************************************************************************
 * DEFINITIONS
 **************************************************************************/
#define EXIT_SUCCESS				0
#define TRUE 						1
#define FALSE						0
#define MAX_COMMAND_LENGTH			1024

#define PROGRAM_NAME				"execute"

/**************************************************************************
 * TYPEDEFS
 **************************************************************************/

/**************************************************************************
 * INTERNAL CALL FUNCTIONS
 **************************************************************************/

/* Metodo responsável por executar um comando */
void execute_command(int numberInput, char **inputs);

void get_process_status(struct timespec start_time, struct timespec end_time);

int read_input();

#endif
