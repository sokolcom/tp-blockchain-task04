#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <stdint.h>
#include <stdlib.h>


#define SUCCESS 0
#define OPTION_ERROR 5
#define N_ARGS_ERROR 10
#define FILE_NOT_FOUND_ERROR 20
#define N_TICKETS_ERROR 30
#define ALLOCATION_ERROR 40
#define OPENSSL_ERROR 50

#define OPTION_FILE "--file"
#define OPTION_NTICKETS "--numbilets"
#define OPTION_PARAMETER "--parameter"

#define MAX_STRING_LENGTH 128
#define N_ARGS 7
#define BITS_PER_BYTE 8

#define AES_MATRIX_SIZE 4  // 4x4 matrix of 128bits (each cell = 1 byte)



enum bool_t
{
    FALSE = 0,
    TRUE
};

typedef struct
{
    uint8_t byte[16];
} uint128_t;

typedef struct 
{
    char filename[MAX_STRING_LENGTH];
    uint32_t n_tickets;
    size_t param;
} input_t;

#endif