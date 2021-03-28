#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>

#include "../include/define.h"
#include "../include/utils.h"



size_t get_length(const char *const filename)
{
    size_t length = 1;

    FILE *src = fopen(filename, "r");
    for (char c = getc(src); c != EOF; c = getc(src))
    {
        if (c == '\n')
        {
            length++;
        }
    }
    fclose(src);
    
    return length;
}

char **create_students_array(const size_t length, const char *const src_filename)
{
    char **array = (char **)calloc(length, sizeof(char *));
    if (!array)
    {
        return array;
    }

    FILE *src = fopen(src_filename, "r");
    
    char newline;
    for (size_t i = 0; i < length; i++)
    {
        char temp[MAX_STRING_LENGTH] = { 0 }; 
        fscanf(src, "%[^\n]", temp);

        array[i] = (char *)calloc(strlen(temp), sizeof(char));
        if (!array[i])
        {
            for (size_t k = 0; k < i; k++)
            {
                free(array[i]);
            }
            free(array);
            return NULL;
        }

        strcpy(array[i], temp);
        fscanf(src, "%c", &newline);  // Jump to the next line
    }

    fclose(src);
    return array;
}

uint32_t *create_yielded_array(const size_t length)
{
    return (uint32_t *)calloc(length, sizeof(uint32_t));
}

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
        
        case ALLOCATION_ERROR:
            fprintf(stream, "ERROR: failed to allocate data!\n");
            break;

        default:
            fprintf(stream, "Oops!\nUnknown error!\n");
    }
}

void print_distr(FILE *const stream, char *const *const array, const uint32_t idx, const uint32_t ticket)
{
    fprintf(stream, "%-50s\t\t%d\n", array[idx], ticket);
}
