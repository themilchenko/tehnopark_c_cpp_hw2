#include "dir_handler.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

typedef struct file_buf {
  char **str_;      /*matrix of names of files in folder*/
  size_t size_;     /*num of files in current folder*/
  size_t capacity_; /*capacity for reallocating*/
} file_buf;

void delete_buf(file_buf buffer) {
  if (!buffer.str_) {
    return;
  }
  for (size_t i = 0; i < buffer.size_; ++i) {
    if (buffer.str_[i]) {
      free(buffer.str_[i]);
    }
  }
  free(buffer.str_);
}

/*===================================================================*/

MyDir *create_dir(const char *dir_name) {
  DIR *directory = opendir(dir_name);
  if (!directory) {
    return NULL;
  }

  file_buf buffer = {NULL, 0, 0};

  struct dirent *dp;
  while ((dp = readdir(directory)) != NULL) {
    const char *file_name = dp->d_name;
    if (strcmp(file_name, ".") != 0 && strcmp(file_name, "..") != 0) {
      if (buffer.size_ == 0) {
        buffer.str_ = (char **)malloc(sizeof(char *));
        ++buffer.capacity_;
      } else if (buffer.size_ + 1 >= buffer.capacity_) {
        buffer.str_ =
            realloc(buffer.str_, buffer.capacity_ * 2 * sizeof(char *));
        buffer.capacity_ *= 2;
      }
      buffer.str_[buffer.size_] =
          (char *)malloc((strlen(file_name) + 1) * sizeof(char));
      if (!buffer.str_[buffer.size_]) {
        delete_buf(buffer);
        return NULL;
      }
      buffer.str_[buffer.size_] =
          strncpy(buffer.str_[buffer.size_], file_name,
                  (strlen(file_name) + 1) * sizeof(char));
      ++buffer.size_;
    }
  }
  closedir(directory);

  MyDir *result = (MyDir *)malloc(sizeof(MyDir));
  if (!result) {
    for (size_t i = 0; i < buffer.size_; ++i) {
      free(buffer.str_[i]);
    }
    free(buffer.str_);
    return NULL;
  }

  result->_size = buffer.size_;
  result->_files = buffer.str_;
  return result;
}

void delete_dir(MyDir *dir) {
  if (!dir) {
    return;
  }
  if (dir->_files) {
    for (size_t i = 0; i < dir->_size; ++i) {
      if (dir->_files[i]) {
        free(dir->_files[i]);
      }
    }
    free(dir->_files);
  }
  free(dir);
}
