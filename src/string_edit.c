#include "calc.h"

string cut_brackers(string input) {
  char *brackers[] = {"(", ")"};
  input = delete_matches(input, brackers, 2);
  return input;
};

string cut_words(string input) {
  char *funcs[] = {"cos",  "sin",  "tan", "acos", "asin",
                   "atan", "sqrt", "ln",  "log",  "mod"};
  input = delete_matches(input, funcs, 10);
  return input;
}

string cut_spaces(string input) {
  char *space[] = {" "};
  input = delete_matches(input, space, 1);
  return input;
};

int chrbrk(char simb, char *str) {
  char *p;
  int err = 1;
  for (p = str; *p != '\0' && err; ++p) {
    if (simb == *p) err = 0;
  }
  return err;
}

char *make_unar_copy(string input, int j) {
  char *copy = malloc(input.len * sizeof(char));
  int last = 0;
  if (copy) {
    for (int i = 0; i < input.len; i++) {
      last = i - 1;
      if (i < j)
        copy[i] = input.str[i];
      else if (i == j)
        copy[i] = '0';
      else if (i > j)
        copy[i] = input.str[last];
    }
  }
  return copy;
}

int compare_liter(char *str1, char *str2) {
  int match = 1;
  for (int x = 0; match == 1 && str2[x] != '\0'; x++)
    if (str1[x] != str2[x]) match = 0;

  return match;
}

string change_wrd(string input, int i, char *func) {
  if (!strcmp(func, "asin"))
    input.str[i] = 'o';
  else if (!strcmp(func, "atan"))
    input.str[i] = 'u';
  else if (!strcmp(func, "sqrt"))
    input.str[i] = 'q';
  else if (!strcmp(func, "log"))
    input.str[i] = 'g';
  return input;
}

string cut_liter(string input, int i, char *literal) {
  int len = strlen(literal);
  if (len > 1) {
    memmove(input.str + i + 1, input.str + i + len, input.len - i - len);
    for (int j = input.len - len + 1; j < input.len; j++) input.str[j] = 0;
    len--;
  } else {
    memmove(input.str + i, input.str + i + len, input.len - i - len);
    for (int j = input.len - len; j < input.len; j++) input.str[j] = 0;
  }
  input.len -= len;
  input = change_wrd(input, i, literal);
  return input;
}

string delete_matches(string input, char **literal, int amount) {
  int match = 0;
  char *tmp = NULL;
  for (int j = 0; j < input.len; j++) {
    for (int i = 0; !match && i < amount; i++) {
      match = compare_liter(tmp = input.str + j, literal[i]);
      if (match) {
        input = cut_liter(input, j, literal[i]);
        j--;
      }
    }
    match = 0;
  }
  return input;
}
