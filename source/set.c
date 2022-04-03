#include <stdlib.h>
#include <string.h>

#include "dir_handler.h"
#include "file_handler.h"
#include "set.h"

char *concatenate(const char *left, const char *right) {
  if (!left || !right) {
    return NULL;
  }
  size_t left_size = strlen(left);
  size_t right_size = strlen(right);
  char *result = (char *)calloc((left_size + right_size + 1), sizeof(char));
  for (size_t i = 0; i < left_size; ++i) {
    result[i] = left[i];
  }
  for (size_t i = 0; i < right_size; ++i) {
    result[i + left_size] = right[i];
  }
  result[left_size + right_size] = '\0';
  return result;
}

/*============================================================================*/

Set *init_set() {
  Set *set = (Set *)calloc(1, sizeof(Set));
  if (!set) {
    return NULL;
  }
  return set;
}

void insert(Set *set, unsigned int value, char *filename) {
  if (set->_size == 0) {
    set->_set = (Element *)malloc(sizeof(Element));
    ++set->_capacity;
    set->_set[0]._value = value;
    set->_set[0]._filename =
        (char *)malloc((strlen(filename) + 1) * sizeof(char));
    set->_set[0]._filename = strncpy(set->_set[0]._filename, filename,
                                     (strlen(filename) + 1) * sizeof(char));
    ++set->_size;
    return;
  } else if (set->_size + 1 >= set->_capacity) {
    set->_set = realloc(set->_set, 2 * set->_capacity * sizeof(Element));
    set->_capacity *= 2;
  }

  size_t index_to_insert = set->_size;
  for (unsigned int i = 0; i < set->_size - 1; ++i) {
    if (value >= set->_set[i]._value && value <= set->_set[i + 1]._value) {
      index_to_insert = i + 1;
      break;
    }
  }

  if (index_to_insert == set->_size) {
    if (value <= set->_set->_value &&
        value <= set->_set[set->_size - 1]._value) {
      index_to_insert = 0;
    } else {
      ++set->_size;
      set->_set[set->_size - 1]._value = value;
      set->_set[set->_size - 1]._filename =
          (char *)malloc((strlen(filename) + 1) * sizeof(char));
      set->_set[set->_size - 1]._filename =
          strncpy(set->_set[set->_size - 1]._filename, filename,
                  (strlen(filename) + 1) * sizeof(char));
      return;
    }
  }
  ++set->_size;
  for (size_t i = set->_size - 1; i > 0; --i) {
    set->_set[i] = set->_set[i - 1];
  }
  set->_set[index_to_insert]._value = value;
  set->_set[index_to_insert]._filename =
      (char *)malloc((strlen(filename) + 1) * sizeof(char));
  set->_set[index_to_insert]._filename =
      strncpy(set->_set[index_to_insert]._filename, filename,
              (strlen(filename) + 1) * sizeof(char));
}

// Element *pop_back(Set *set) {
//   if (!set) {
//     return NULL;
//   }
//   --set->_size;
//   return &set->_set[set->_size];
// }

Set *create_set(const char *filename, const char *expected_word, size_t left,
                size_t right) {
  MyDir *directory = create_dir(filename);
  if (!directory) {
    return NULL;
  }
  Set *set = init_set();
  if (!set) {
    delete_dir(directory);
    return NULL;
  }

  for (size_t i = left; i < right; ++i) {
    char *str = concatenate(filename, "/");
    char *path = concatenate(str, directory->_files[i]);
    MyFile *current_file = create_file(path);
//    current_file->_file_name =
//        (char *)malloc((strlen(directory->_files[i]) + 1) * sizeof(char));
    if (!current_file->_file_name) {
      free(path);
      free(str);
      delete_file(current_file);
      delete_dir(directory);
      delete_set(set);
      return NULL;
    }
//    current_file->_file_name =
//        strncpy(current_file->_file_name, directory->_files[i],
//                (strlen(directory->_files[i]) + 1) * sizeof(char));
    count(current_file, expected_word);
    insert(set, current_file->_words_counter, current_file->_file_name);
    free(path);
    free(str);
    delete_file(current_file);
  }

  delete_dir(directory);

  return set;
}

void print_set(Set *set) {
  if (!set) {
    return;
  }
  for (size_t i = 0; i < set->_size; ++i) {
    if (set->_set[set->_size - i - 1]._filename) {
      printf("%zu) Filename: %s, num of words: %u\n", i + 1,
             set->_set[set->_size - i - 1]._filename,
             set->_set[set->_size - i - 1]._value);
    }
  }
}

void delete_set(Set *set) {
  if (!set) {
    return;
  }
  for (size_t i = 0; i < set->_size; ++i) {
    if (set->_set[i]._filename) {
      free(set->_set[i]._filename);
    }
  }
  if (set->_set) {
    free(set->_set);
  }
  free(set);
}
