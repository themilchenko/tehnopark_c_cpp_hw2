#ifndef HW_2_FILE_HANDLER_H
#define HW_2_FILE_HANDLER_H

#include <stdio.h>

typedef struct {
    char *_file_name;
    char *_buffer;                  /*buffer with content of file*/
    unsigned int _words_counter;    /*variable that counts num of requestrd word*/
} MyFile;

MyFile *create_file(const char *file_name);
unsigned int count(MyFile *file, const char *finding_word);
void delete_file(MyFile *file);

#endif // HW_2_FILE_HANDLER_H