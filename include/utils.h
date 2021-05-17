#ifndef _UTILS_H_
#define _UTILS_H_


size_t get_length(const char *const _filename);

char **create_students_array(const size_t _length, const char *const _src_filename);
uint32_t *create_yielded_array(const size_t _length);

int32_t load_args(input_t *const _input, const int _argc, char *_argv[]);

void print_error(FILE *const _output_stream, const int32_t _error_code);
void print_distr(FILE *const _output_stream, char *const *const _array, const uint32_t _idx, const uint32_t _ticket);

int32_t hash_student(uint128_t *const _hash, const char* _msg);


#endif

