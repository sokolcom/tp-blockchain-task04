#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>

#include "../include/define.h"
#include "../include/utils.h"
// #include "../include/utils.h"


// static student_t *create_array(const size_t length, const char *const src_filename)
// {
//     student_t *array = (student_t *)calloc(length, sizeof(student_t));
//     if (!array)
//     {
//         return array;
//     }

//     // FILE *src = fopen(src_filename, "r");
    
//     // for (size_t i = 0; i < length; i++)
//     // {
//     //     array[i] = { .name = , };
//     // }

//     // fclose(src);

//     return array;
// }

// static void free_array(student_t *const array)
// {
//     free(array);
// }

static int32_t file_exists(const char *const filename)
{
  struct stat buffer;   
  return (stat(filename, &buffer) == 0);
}

static char *parse_argv(const int argc, char *argv[], const char *const key)
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
    if (argc != N_ARGS)
    {
        return N_ARGS_ERROR;
    }   

    char* filename = parse_argv(argc, argv, OPTION_FILE);
    if (!filename)
    {
        return OPTION_ERROR;
    }
    else if (!file_exists(filename))
    {
        return FILE_NOT_FOUND_ERROR;
    }

    char *n_tickets = parse_argv(argc, argv, OPTION_NTICKETS);
    if (!n_tickets)
    {
        return OPTION_ERROR;
    }
    else if (atoi(n_tickets) < 1)
    {
        return N_TICKETS_ERROR;
    }

    char *param = parse_argv(argc, argv, OPTION_PARAMETER);
    if (!param)
    {
        return OPTION_ERROR;
    }
    
    strcat(usr_input->filename, filename);
    usr_input->n_tickets = atoi(n_tickets);
    usr_input->param = atoi(param);

    return SUCCESS;
}

// void process_data(const input_t *const usr_input)
// {
//     const size_t students_amount  = ;



//     student_t *distr_array = create_array(students_amount, usr_input->filename);

//     print_array(stdout, distr_array, students_amount);
//     free_array(distr_array);
// }

void print_array(FILE *const stream, const student_t *const array, const size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        fprintf(stream, "%s\t%d\n", array[i].name, array[i].n);
    }
}

void print_error(FILE *const stream, const int32_t error_code)
{
    switch (error_code)
    {
        case OPTION_ERROR:
            fprintf(stream, "ERROR: the unknown option(s) was found!\n");
            break;

        case N_ARGS_ERROR:
            fprintf(stream, "ERROR: invalid amout of the arguments!\n");
            break;
        
        case FILE_NOT_FOUND_ERROR:
            fprintf(stream, "ERROR: source file wasn't found!\n");
            break;
        
        case N_TICKETS_ERROR:
            fprintf(stream, "ERROR: invalid amout of the tickets (%s < 1)!\n", OPTION_NTICKETS);
            break;

        default:
            fprintf(stream, "Oops!\nUnknown error!\n");
    }
}