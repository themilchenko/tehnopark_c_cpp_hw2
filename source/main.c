#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "dir_handler.h"
#include "set.h"

int main(int argc, char *argv[]) {
  char *name_of_dir = NULL;
                      // "/Users/admin/Tehnopark/first_sem_web/advanced_C-C++/tehnopark_c_cpp_hw2/dump";
  char *request = NULL;
  int c = 0;

  while ((c = getopt(argc, argv, "f:d:")) != -1) {
    switch (c) {
    case 'd':
      name_of_dir = optarg;
      break;
    case 'f':
      request = optarg;
      break;
    default:
      return (EXIT_FAILURE);
    }
  }

  if (!name_of_dir) {
    fprintf(stderr, "Can't find this folder\n");
    return EXIT_FAILURE;
  }

  if (!request) {
    fprintf(stderr, "Error");
    return EXIT_FAILURE;
  }

  MyDir *dir = create_dir(name_of_dir);
  if (!dir) {
    return EXIT_FAILURE;
  }
  Set *result = create_set(name_of_dir, request, 0, dir->_size);
  if (!result) {
    return EXIT_FAILURE;
  }
  print_set(result);
  delete_dir(dir);
  delete_set(result);

  return EXIT_SUCCESS;
}
