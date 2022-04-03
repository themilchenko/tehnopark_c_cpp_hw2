#include <gtest/gtest.h>

extern "C" {
#include "dir_handler.h"
#include "file_handler.h"
#include "set.h"
}

#define Q(x) #x
#define QUOTE(x) Q(x)

TEST(FileTest, create_file) {
  //"/Users/admin/Tehnopark/first_sem_web/advanced_C-C++/tehnopark_c_cpp_hw2/dump/text.txt";
  //"/home/project/dump/test_file.txt";

  const char *text_eq = "so we have test file\n"
                        "i want to tell you about something\n"
                        "let's imagine about future\n"
                        "that's all for now\n"
                        "have a nice life and goodbye";

  MyFile *file = create_file(QUOTE(PATH_TO_FILE));

  ASSERT_STREQ(file->_buffer, text_eq);
  ASSERT_STREQ(file->_file_name, "test_file.txt");
  ASSERT_EQ(file->_words_counter, 0);

  delete_file(file);
}

TEST(FileTest, count_words) {
  MyFile *file = create_file(QUOTE(PATH_TO_FILE));

  count(file, "a");

  ASSERT_EQ(file->_words_counter, 10);

  delete_file(file);
}

TEST(DirTest, create_dir) {
  MyDir *directory = create_dir(QUOTE(PATH_TO_DIR));

  const char *dir_names[4] = {"Virus:Vibrance.txt", "bohemian_rapsody.txt",
                              "headhunter.txt", "test_file.txt"};

  ASSERT_EQ(directory->_size, 4);

  for (size_t i = 0; i < directory->_size; ++i) {
    ASSERT_STREQ(directory->_files[i], dir_names[i]);
  }

  delete_dir(directory);
}

TEST(Set, create_set) {
  const char *searching_word = "the";
  MyDir *directory = create_dir(QUOTE(PATH_TO_DIR));
  Set *set = create_set(QUOTE(PATH_TO_DIR), searching_word, 0, directory->_size);
  delete_dir(directory);

  print_set(set);

  ASSERT_EQ(set->_set[3]._value, 10);
  ASSERT_STREQ(set->_set[3]._filename, "Virus:Vibrance.txt");

  ASSERT_EQ(set->_set[2]._value, 8);
  ASSERT_STREQ(set->_set[2]._filename, "bohemian_rapsody.txt");

  ASSERT_EQ(set->_set[1]._value, 7);
  ASSERT_STREQ(set->_set[1]._filename, "headhunter.txt");

  ASSERT_EQ(set->_set[0]._value, 0);
  ASSERT_STREQ(set->_set[0]._filename, "test_file.txt");

  delete_set(set);
}
