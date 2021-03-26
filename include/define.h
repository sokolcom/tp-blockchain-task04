#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <stdint.h>


#define SUCCESS 0
#define N_ARGS_ERROR 10
#define FILE_NOT_FOUND_ERROR 20
#define N_TICKETS_ERROR 30

#define PARAM_FILE "--file"
#define PARAM_NTICKETS "--numbilets"
#define PARAM_PARAMETER "--parameter"

#define MAX_STRING_LENGTH 128
#define N_ARGS 7


enum bool_t
{
    FALSE = 0,
    TRUE
};

typedef struct 
{
    char name[MAX_STRING_LENGTH];
    uint32_t n;
} student_t;

typedef struct 
{
    char filename[MAX_STRING_LENGTH];
    uint32_t n_tickets;
    int32_t param;
} input_t;


#endif