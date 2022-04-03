#include "file_handler.h"
#include <stdlib.h>
#include <string.h>

char *get_filename(const char *pathname) {
  size_t path_length = strlen(pathname);
  size_t index = path_length;

  for (size_t i = 0; i < path_length; ++i) {
    if (pathname[path_length - i - 1] == '/') {
      index = path_length - i - 1;
      break;
    }
  }

  if (index == path_length) {
    return NULL;
  }

  char *result_str = (char *)malloc((path_length - index) * sizeof(char));
  if (!result_str) {
    return NULL;
  }
  for (size_t i = index + 1; i < path_length; ++i) {
    result_str[i - (index + 1)] = pathname[i];
  }
  result_str[path_length - index - 1] = '\0';
  return result_str;
}

MyFile *create_file(const char *file_name) {
  FILE *file = fopen(file_name, "rb");
  if (!file) {
    return NULL;
  }

  MyFile *result = (MyFile *)calloc(1, sizeof(MyFile));
  if (!result) {
    fclose(file);
    return NULL;
  }

  result->_buffer = NULL;
  result->_file_name = get_filename(file_name);

  fseek(file, 0, SEEK_END);
  size_t file_size = (size_t)ftell(file);
  rewind(file);

  if (file_size) {
    result->_buffer = (char *)malloc((file_size + 1) * sizeof(char));
    if (!result->_buffer) {
      delete_file(result);
      fclose(file);
      return NULL;
    }
    fread(result->_buffer, file_size, 1, file);
    result->_buffer[file_size] = '\0';
  }
  fclose(file);

  return result;
}

void delete_file(MyFile *file) {
  if (!file) {
    return;
  }

  if (file->_file_name) {
    free(file->_file_name);
  }
  if (file->_buffer) {
    free(file->_buffer);
  }
  free(file);
}

unsigned int count(MyFile *file, const char *finding_word) {
  if (!file->_buffer || !finding_word) {
    return 0;
  }
  size_t word_index = 0;
  size_t buffer_size = strlen(file->_buffer);
  for (size_t i = 0; i < buffer_size; ++i) {
    if (file->_buffer[i] == finding_word[word_index]) {
      ++word_index;
    } else {
      word_index = 0;
    }

    if (word_index == strlen(finding_word)) {
      word_index = 0;
      ++file->_words_counter;
    }
  }
  return file->_words_counter;
}
