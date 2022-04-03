#ifndef HW2_DIR_HANDLER_H
#define HW2_DIR_HANDLER_H

#include <stdio.h>

typedef struct {
  char **_files;      /*matrix of titles of files*/
  size_t _size;          /*num of files in folder*/
} MyDir;

MyDir *create_dir(const char *dir_name);

void delete_dir(MyDir *dir);

#endif // HW2_DIR_HANDLER_H