#include <stdio.h>

#include "../include/define.h"
#include "../include/rng.h"
#include "../include/utils.h"


int main(int argc, char *argv[])
{
    int32_t code = SUCCESS;
    input_t usr_input = { .filename = { 0 } };

    if ((code = load_args(&usr_input, argc, argv)))
    {
        print_error(stderr, code);
        return code;
    }

    if ((code = distribute_tickets(&usr_input)))
    {
        print_error(stderr, code);
    }

    return code;
}
