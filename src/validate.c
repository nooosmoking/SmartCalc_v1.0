#include "calc.h"

//
// 1. проверяешь строку на совподение с построкой.
// 1-9 , sin, cos, + ,- ,/
// 2. str ->0 ++
// str = cos12+3
// ()
// sin cos  -> s, c
// for sub_str in [ (, 3, "sin", "cos",]:
//      strstr(str, sub_str)
//      str+= len(sub_str)

int check_liter(string input) {
  char *liter[] = {"cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln",
                   "log", "(",   ")",   "*",    "/",    "mod",  "+",    "-",
                   "^",   "1",   "2",   "3",    "4",    "5",    "6",    "7",
                   "8",   "9",   "0",   "x",    ".",    " "};
  int err = 0, err1 = 0, err2 = 0;
  int match = 0;
  int func = 0;
  int bracket = 0;
  int start = 1;
  while (*(input.str) && !err) {
    match = 0;
    for (int i = 0; !match && i < 30 && !err; i++) {
      match = compare_liter(input.str, liter[i]);

      if (match) {
        if (i >= 0 && i <= 8) {
          func += 2;
          input.str += strlen(liter[i]);
          if (*(input.str) == '(') {
            func--;
            input.str++;
          } else if (*(input.str) == ' ' && input.str[1] == '(') {
            func--;
            input.str += 2;
          } else {
            err = 1;
          }
          continue;
        } else if (liter[i][0] == '(') {
          bracket++;
        } else if (liter[i][0] == ')') {
          if (func > 0)
            func--;
          else if (bracket > 0)
            bracket--;
          else
            err = 1;
        } else if (liter[i][0] == ' ') {
          if (!start) {
            input.str--;
            for (int j = 17; j < 29 && !err; j++) {
              err1 = compare_liter(input.str, liter[j]);
            }
            input.str++;
          }
          input.str++;
          for (int j = 17; j < 29 && !err; j++) {
            err2 = compare_liter(input.str, liter[j]);
          }
          input.str--;
          if (err1 && err2) err = 1;
        }
        start = 0;
        input.str += strlen(liter[i]);
      }
    }
    if (!match || func < 0 || bracket < 0) err = 1;
  }
  if (func || bracket) {
    err = 1;
  }
  return err;
}

int order_brackers(string input, char *operas, char *numbs) {
  int err = 0;
  int tmp = 0;
  for (int i = 0; !err && i < input.len; i++) {
    if (input.str[i] == '(') {
      if (i > 0) {
        err = !(chrbrk(input.str[tmp = i - 1], numbs));
      }
      if (!err && i < input.len - 1) {
        err = !(chrbrk(input.str[tmp = i + 1], operas));
      }
    } else if (input.str[i] == ')') {
      if (i > 0 && input.str[tmp = i - 1] != ')' &&
          ((input.str[tmp = i - 1] == '(') ||
           chrbrk(input.str[tmp = i - 1], numbs))) {
        err = 1;
      }
      if (!err && i < input.len - 1 && input.str[tmp = i + 1] != ')') {
        err = chrbrk(input.str[tmp = i + 1], operas);
      }
    }
  }

  return err;
}

int check_order(string input) {
  char funcs[] = {'c', 's', 't', 'a', 'o', 'u', 'q', 'l', 'g', '\0'};
  char operas[] = {'*', '/', 'm', '+', '-', '^', '\0'};
  char numbs[] = {'1', '2', '3', '4', '5', '6', '7',
                  '8', '9', '0', '.', 'x', '\0'};
  int err = 0;
  int dot = 0;
  int last = 0, next = 0;

  char copy[255] = {0};
  string s_copy = {.str = copy, input.len};

  for (int i = 0; i < s_copy.len; i++) {
    s_copy.str[i] = input.str[i];
  }
  err = order_brackers(s_copy, operas, numbs);
  if (!err) {
    s_copy = cut_brackers(s_copy);

    for (int i = 0; !err && i < s_copy.len; i++) {
      next = i + 1;
      last = i - 1;

      if (strchr(funcs, s_copy.str[i])) {
        dot = 0;

        if (i > 0) {
          err = !chrbrk(s_copy.str[last], numbs);
        }
        if (i == s_copy.len - 1) err = 1;
        if (!err && i < s_copy.len - 1) {
          err = !(chrbrk(s_copy.str[next], operas));
        }
      } else if (strchr(operas, s_copy.str[i])) {
        dot = 0;
        if (i == 0 || i == s_copy.len - 1)
          err = 1;
        else {
          err = chrbrk(s_copy.str[last], numbs);
        }
        if (!err && i < s_copy.len - 1) {
          err = !(chrbrk(s_copy.str[next], operas));
        }
      } else if (strchr(numbs, s_copy.str[i])) {
        if (i < s_copy.len - 1) {
          err = !(chrbrk(s_copy.str[next], funcs));
        }
        if (s_copy.str[i] == '.' && dot == 0)
          dot++;
        else if (s_copy.str[i] == '.' && dot > 0)
          err = 1;
      }
    }
  }

  return err;
}

string check_unars(string input) {
  int last = 0;
  char last_simb = 0;
  for (int i = 0; i < input.len; i++) {
    last = i - 1;
    if (i > 0) last_simb = input.str[last];
    if ((input.str[i] == '+' || input.str[i] == '-') &&
        (i == 0 || last_simb == '(')) {
      input.len = input.len + 1;
      input.str = make_unar_copy(input, i);
    }
  }
  return input;
}

string validation(string input, int *err) {
  *err = check_liter(input);
  if (!*err) {
    input = cut_words(input);
    input = cut_spaces(input);
    input = check_unars(input);
    *err = check_order(input);
  }
  return input;
}