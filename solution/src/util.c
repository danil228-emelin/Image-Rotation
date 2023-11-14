// working with file
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
char *argv[];
struct file {
  FILE *open_file;
  bool valid;
};

struct file new_empty_file() {
  return (struct file){0};
}
struct file new_file(char *fileName, char *privileges) {
  struct file file = new_empty_file();
  file.open_file = fopen(argv[1], privileges);
  if (file.open_file)
    file.valid = true;
}
bool fclose_file(struct file file) {
  if (!file.valid)
    return false;
  int res = fclose(file);
  if (!res)
    return true;
  else
    return false;
}