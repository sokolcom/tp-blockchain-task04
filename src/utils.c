#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>

#include "../include/define.h"
#include "../include/utils.h"
// #include "../include/utils.h"


student_t *create_array(const int32_t length)
{
    return (student_t *)calloc(length, sizeof(student_t));
}

void free_array(student_t *const array)
{
    free(array);
}

static int32_t file_exists(const char *const filename)
{
  struct stat buffer;   
  return (stat(filename, &buffer) == 0);
}

char *parse_argv(const int argc, char *argv[], const char *const key)
{
    int32_t idx = 0;
    int32_t flag = TRUE;

    while (flag && (++idx < argc))
    {
        if (!strcmp(argv[idx], key))
        {
            flag = FALSE;
        }
    }

    return (idx + 1 < argc) ? argv[idx + 1] : NULL;
}

int32_t load_args(input_t *const usr_input, const int argc, char *argv[])
{
    // ./program --file <filename> --numbilets 20 --parameter 42

    if (argc != N_ARGS)
    {
        return N_ARGS_ERROR;
    }   

    char* filename = parse_argv(argc, argv, PARAM_FILE);
    if (!file_exists(filename))
    {
        return FILE_NOT_FOUND_ERROR;
    }

    char *n_tickets = parse_argv(argc, argv, PARAM_NTICKETS);
    if (atoi(n_tickets) < 1)
    {
        return N_TICKETS_ERROR;
    }

    char *param = parse_argv(argc, argv, PARAM_PARAMETER);
    
    strcat(usr_input->filename, filename);
    usr_input->n_tickets = atoi(n_tickets);
    usr_input->param = atoi(param);

    return SUCCESS;
}

void print_error(FILE *const stream, const int32_t error_code)
{
    switch (error_code)
    {
        case N_ARGS_ERROR:
            fprintf(stream, "ERROR: invalid amout of the arguments!\n");
            break;
        
        case FILE_NOT_FOUND_ERROR:
            fprintf(stream, "ERROR: source file wasn't found!\n");
            break;
        
        case N_TICKETS_ERROR:
            fprintf(stream, "ERROR: invalid amout of the arguments!\n");
            break;

        default:
            fprintf(stream, "Oops!\nUnknown error!\n");
    }
}