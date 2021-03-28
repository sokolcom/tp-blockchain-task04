#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../include/define.h"
#include "../include/aes.h"
#include "../include/utils.h"



int32_t distribute_tickets(const input_t *const usr_input)
{
    size_t amount = get_length(usr_input->filename);
    uint32_t max_same_tickets = amount / usr_input->n_tickets;
    max_same_tickets += (amount % usr_input->n_tickets) ? 1 : 0;
    
    char **students_array = (char **)create_students_array(amount, usr_input->filename);
    if (!students_array)
    {
        return ALLOCATION_ERROR;
    }

    uint32_t *yielded_array = create_yielded_array(usr_input->n_tickets);
    if (!yielded_array)
    {
        return ALLOCATION_ERROR;
    }

    int32_t ticket_counter = 0;
    uint32_t student = 0;
    while (student < amount)
    {
        uint32_t ticket_no = rijndael_aes(usr_input->param) % usr_input->n_tickets;

        // Check if all tickets were already distributed && if so check if max_same_tickets were exceeded
        if (((ticket_counter < usr_input->n_tickets) && !yielded_array[ticket_no]) ||
            ((ticket_counter >= usr_input->n_tickets) && (yielded_array[ticket_no] < max_same_tickets)))
        {
            print_distr(stdout, students_array, student, ticket_no + 1);
            yielded_array[ticket_no]++;
            student++;
            ticket_counter++;
        }
    }

    free(students_array);
    free(yielded_array);

    return SUCCESS;
}
