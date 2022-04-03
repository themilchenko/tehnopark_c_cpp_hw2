#ifndef HW2_LIST_H
#define HW2_LIST_H

#include "file_handler.h"

char *concatenate(const char *left, const char *right);

typedef struct {
  unsigned int _value;
  char *_filename;
} Element;

typedef struct Set {
    Element *_set;
    unsigned int _size;
    unsigned int _capacity;
} Set;

Set *init_set();

Set *create_set(const char *filename, const char *expected_word, size_t left, size_t right);

void insert(Set *set, unsigned int value, char *filename);

//Element *pop_back(Set *set);

void print_set(Set *set);

void delete_set(Set *set);

#endif // HW2_LIST_H
