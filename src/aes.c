#include <stdlib.h>
#include <stdio.h>

#include "../include/define.h"


// 256bit key: 0xD14A98557E9B6838C8A74BB62033E8198914D2B394405F96FC7C4B8F2A5DDCEF 
// 128bit key: 0xD14A98557E9B6838C8A74BB62033E81912FB244FD7F000CFDCEFC2D3FA
const char* AES_KEY_HEX[] = {
    "11010001", "01001010", "10011000", "01010101", \
    "01111110", "10011011", "01101000", "00111000", \
    "11001000", "10100111", "01001011", "10110110", \
    "00100000", "00110011", "11101000", "00011001" };
    // "10001001", "00010100", "11010010", "10110011", 
    // "10010100", "01000000", "01011111", "10010110", 
    // "11111100", "01111100", "01001011", "10001111", 
    // "00101010", "01011101", "11011100", "11101111" };

const uint32_t AES_LOOKUP_TABLE[] = { \
        0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, \
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, \
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, \
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, \
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, \
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, \
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, \
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, \
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, \
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, \
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, \
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, \
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, \
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, \
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, \
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

const uint8_t AES_MIXCOL_MATRIX[AES_MATRIX_SIZE][AES_MATRIX_SIZE] = {
    {2, 3, 1, 1},
    {1, 2, 3, 1},
    {1, 1, 2, 3},
    {3, 1, 1, 2}
};

static void xor(uint8_t matrix[][AES_MATRIX_SIZE], const uint128_t *const key)
{
    for (int32_t col = 0; col < AES_MATRIX_SIZE; col++)
    {
        for (int32_t row = 0; row < AES_MATRIX_SIZE; row++)
        {
            matrix[row][col] ^= key->byte[col * AES_MATRIX_SIZE + row];
        }
    }
}

static uint128_t create_key_128bit(const char *const *const key_string)
{
    uint128_t key;
    for (int32_t i = 0; i < 16; i++)
    {
        key.byte[i] = strtoull(key_string[i], NULL, 2);
    }
    return key;
}

static uint8_t mult(uint8_t a, uint8_t b)
{
    uint16_t result = 0x0;

    switch (a)
    {
        case 1:
            result = b;
            break;
        
        case 2:
            result = a * b;
            if (result > 0xFF)
            {
                result ^= 0x1B;
                result -= 0x100;
            }
            break;

        case 3:
            result = a * b;
            if (result > 0xFF)
            {
                result = result ^ b ^ 0x1B;
                result -= 0x100;
            }
            break;
    }

    return (uint8_t)result;
}

static void aes_matrix_m12n(
    uint8_t result[][AES_MATRIX_SIZE], 
    const uint8_t matrix_1[][AES_MATRIX_SIZE], uint8_t matrix_2[][AES_MATRIX_SIZE])
{
    for (int32_t i = 0; i < AES_MATRIX_SIZE; i++)
    {
        for (int32_t j = 0; j < AES_MATRIX_SIZE; j++)
        {
            uint8_t res = 0x0;
            for (int32_t mul = 0; mul < AES_MATRIX_SIZE; mul++)
            {
                res ^= mult(matrix_1[i][mul], matrix_2[mul][j]);
            }
            result[i][j] = res;
        }
    }
}

static void copy_matrix(uint8_t dest[][AES_MATRIX_SIZE], uint8_t src[][AES_MATRIX_SIZE])
{
    for (int32_t i = 0; i < AES_MATRIX_SIZE; i++)
    {
        for (int32_t j = 0; j < AES_MATRIX_SIZE; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}

static void prepare_matrix(uint8_t matrix[][AES_MATRIX_SIZE], const size_t seed)
{
    int32_t flag = TRUE;

    // Column-major ordering
    for (int32_t col = 0; col < AES_MATRIX_SIZE; col++)
    {
        for (int32_t row = 0; row < AES_MATRIX_SIZE; row++)
        {
            if (flag && (sizeof(size_t) - 1 < col * AES_MATRIX_SIZE + row))
            {
                flag = FALSE;
            }

            if (flag)
            {
                matrix[row][col] = (seed >> ((col * AES_MATRIX_SIZE + row) * sizeof(matrix[row][col]) * BITS_PER_BYTE)) & 0xFF;
            }
            else
            {
                matrix[row][col] = 0x0;
            }
            printf("MATRIX[%d][%d] = %d\n", row, col, matrix[row][col]);
        }
    }
}

static void sub_bytes(uint8_t matrix[][AES_MATRIX_SIZE])
{
    for (int32_t row = 0; row < AES_MATRIX_SIZE; row++)
    {
        for (int32_t col = 0; col < AES_MATRIX_SIZE; col++)
        {
            uint8_t i = matrix[row][col] >> 4;
            uint8_t j = matrix[row][col] & 0xF;
            matrix[row][col] = AES_LOOKUP_TABLE[i * 16 + j];
        }
    }
}

static void shift_rows(uint8_t matrix[][AES_MATRIX_SIZE])
{
    for (int32_t row = 1; row < AES_MATRIX_SIZE; row++)
    {
        for (int32_t shift = 0; shift < row; shift++)
        {
            uint8_t temp = matrix[row][0];
            for (int32_t i = 0; i < AES_MATRIX_SIZE - 1; i++)
            {
                matrix[row][i] = matrix[row][i + 1];
            }
            matrix[row][AES_MATRIX_SIZE - 1] = temp;
        }
    }
}

static void mix_columns(uint8_t matrix[][AES_MATRIX_SIZE])
{
    uint8_t result[AES_MATRIX_SIZE][AES_MATRIX_SIZE] = { 0 };
    aes_matrix_m12n(result, AES_MIXCOL_MATRIX, matrix);
    copy_matrix(matrix, result);
}

size_t rijndael_aes(const size_t seed)
{
    const uint128_t key = create_key_128bit(AES_KEY_HEX);
    // for (int i = 0; i < 32; i++)
    //     printf("%x", key.byte[i]);
    // printf("\n");
    // return 0;

    uint8_t state_matrix[AES_MATRIX_SIZE][AES_MATRIX_SIZE] = { 0 };
    prepare_matrix(state_matrix, seed);
    xor(state_matrix, &key);

    for (int32_t round = 0; round < 1; round++)
    {
        sub_bytes(state_matrix);
        // printf("(AFTER SUB_BYTES)\n");
        // for (int i = 0; i < 4; i++)
        // {
        //     for (int j = 0; j < 4; j++)
        //     {
        //         printf("%d ", state_matrix[i][j]);
        //     }
        //     printf("\n");
        // }

        shift_rows(state_matrix);
        // printf("(AFTER SHIFT_ROWS)\n");
        // for (int i = 0; i < 4; i++)
        // {
        //     for (int j = 0; j < 4; j++)
        //     {
        //         printf("%d ", state_matrix[i][j]);
        //     }
        //     printf("\n");
        // }
        (round < AES_ROUNDS_256 - 1) ? mix_columns(state_matrix) : NULL;
        // printf("(AFTER MIX_COLUMNS)\n");
        // for (int i = 0; i < 4; i++)
        // {
        //     for (int j = 0; j < 4; j++)
        //     {
        //         printf("%d ", state_matrix[i][j]);
        //     }
        //     printf("\n");
        // }
        // break;
        xor(state_matrix, &key);

    }

    // printf("(AFTER ALL)\n");
    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         printf("%d ", state_matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    return 0;
}