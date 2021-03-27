#include <stdio.h>

#include "../include/define.h"
#include "../include/rng.h"
#include "../include/utils.h"

// Программа принимает три параметра командной строки, типа:

// ./program --file <filename> --numbilets 20 --parameter 42

// Параметры: имя файла с ФИО студентов, число билетов, параметр, меняющий распределение. Затем, программа равномерно и детерминировано выдает в консоль строку из файла + номер билета. Номера билетов детерминированно связаны с ФИО и параметром, меняющим распределение. 

// Входные данные (параметры командной строки):
// 1) файл, где каждая строка - это ФИО студента, типа:

// Иванов Иван Иванович
// Ярцев Ярослав Ярославович
// ...
// Петров Петр Петрович

// 2) число билетов N (билеты нумеруются с 1 до N (включая N))
// 3) численный параметр, детерминированно меняющий распределение (при его изменении распределение номеров билетов максимально изменяется). При использовании одного и того же параметра, одна и та же строка Фамилия-Имя из файла всегда генерирует один и тот же номер билета

// Выходные данные: вывод в STDOUT строк вида:

// Иванов Иван Иванович: 21
// Ярцев Ярослав Ярославович: 12
// ...
// Петров Петр Петрович: 11

int main(int argc, char *argv[])
{
    int32_t code;
    input_t usr_input = { .filename = { 0 } };

    if ((code = load_args(&usr_input, argc, argv)))
    {
        print_error(stderr, code);
        return code;
    }

    printf("INPUT: filename --- %s\n", usr_input.filename);
    printf("INPUT: n_tickets --- %d\n", usr_input.n_tickets);
    printf("INPUT: param --- %ld\n", usr_input.param);
    printf("sizeof(size_t) = %ld\n", sizeof(size_t));

    // printf("%lx\n", usr_input.param);
    // printf("%b\n", usr_input.param);

    char matrix[4][4] = { 0 };
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            printf("(BEFORE) MATRIX[%d][%d] = %d\n", i, j, matrix[i][j]);
    // prepare_matrix(matrix, usr_input.param);
    
    // printf("AES_LOOKUP = %d\n", AES_LOOKUP_TABLE[0]);
    rijndael_aes(usr_input.param);
    // proccess_data(&usr_input);

    return SUCCESS;
}
