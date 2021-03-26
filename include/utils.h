#ifndef _UTILS_H_
#define _UTILS_H_

int32_t load_args(input_t *const _input, const int _argc, char *_argv[]);
void print_error(FILE *const _output_stream, const int32_t _error_code);

#endif

