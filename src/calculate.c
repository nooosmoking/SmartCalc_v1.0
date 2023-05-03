#include "calc.h"

void make_array(string input, literal *literal_array, double xval) {
  char funcs[] = {'c', 's', 't', 'a', 'o', 'u', 'q', 'l', 'g', '\0'};
  char operas[] = {'*', '/', 'm', '+', '-', '^', '\0'};
  char numbs[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', '\0'};
  int match = 0;
  int i = 0;
  char simbol = '\0';

  while (*input.str) {
    if (chrbrk(*input.str, numbs) == match) {
      sscanf(input.str, "%lf", &(literal_array[i].val));
      literal_array[i].type = INT;
      while (chrbrk(*input.str, numbs) == match) input.str++;
      input.str--;
    } else if (chrbrk(*input.str, operas) == match) {
      sscanf(input.str, "%c", &simbol);
      literal_array[i].val = (double)simbol;
      literal_array[i].type = OPER;
    } else if (chrbrk(*input.str, funcs) == match) {
      sscanf(input.str, "%c", &simbol);
      literal_array[i].val = (double)simbol;
      literal_array[i].type = FUNC;
    } else if (*input.str == 'x' || *input.str == 'X') {
      literal_array[i].val = xval;
      literal_array[i].type = INT;
    } else if (*input.str == '(' || *input.str == ')') {
      sscanf(input.str, "%c", &simbol);
      literal_array[i].val = (double)simbol;
      literal_array[i].type = BRACK;
    }
    input.str++;
    i++;
  }
}

void make_stack(literal *literal_array, literal *output) {
  int empty = 0;
  literal support[255] = {0};

  for (int i = 0; literal_array[i].type; i++) {
    if (literal_array[i].type == INT) {
      push(literal_array[i], output);
    } else if (literal_array[i].type == OPER || literal_array[i].type == FUNC) {
      if (get_priority(literal_array[i]) >
          get_priority(pick(support, &empty))) {
        push(literal_array[i], support);
      } else {
        while (get_priority(literal_array[i]) <=
               get_priority(pick(support, &empty))) {
          push(pop(support, &empty), output);
        }
        push(literal_array[i], support);
      }
    } else if (literal_array[i].val == ')') {
      while ((char)pick(support, &empty).val != '(') {
        push(pop(support, &empty), output);
      }
      pop(support, &empty);
    } else if (literal_array[i].val == '(') {
      push(literal_array[i], support);
    }
  }
  empty = 0;
  while (!empty) {
    push(pop(support, &empty), output);
  }
}

void pn(string input, literal *output, double xval) {
  literal literal_array[255] = {0};
  make_array(input, literal_array, xval);
  make_stack(literal_array, output);
}

double calc(string input, double xval) {
  double result = 0;
  literal output[255] = {0};
  double val1 = 0;
  double val2 = 0;
  int j = 0;
  int k = 0;
  int z = 0;

  pn(input, output, xval);

  for (int i = 0; output[i].type; i++) {
    if (i != 0) {
      j = i;
      do {
        j--;
      } while (output[j].type != INT);
      val1 = output[j].val;
    }

    if (output[i].type == OPER) {
      k = j;
      do {
        k--;
      } while (output[k].type != INT);
      val2 = output[k].val;
      output[j].type = 6;
      output[k].type = 6;

      switch ((char)output[i].val) {
        case '+':
          output[i].val = val1 + val2;
          break;
        case '-':
          output[i].val = val2 - val1;
          break;
        case '*':
          output[i].val = val1 * val2;
          break;
        case '/':
          output[i].val = val2 / val1;
          break;
        case '^':
          output[i].val = pow(val2, val1);
          break;
        case 'm':
          output[i].val = fmod(val2, val1);
          break;
      }
      output[i].type = INT;
    } else if (output[i].type == FUNC) {
      output[j].type = 6;
      switch ((char)output[i].val) {
        case 'c':
          output[i].val = cos(val1);
          break;
        case 's':
          output[i].val = sin(val1);
          break;
        case 't':
          output[i].val = tan(val1);
          break;
        case 'a':
          output[i].val = acos(val1);
          break;
        case 'o':
          output[i].val = asin(val1);
          break;
        case 'u':
          output[i].val = atan(val1);
          break;
        case 'q':
          output[i].val = sqrt(val1);
          break;
        case 'l':
          output[i].val = log(val1);
          break;
        case 'g':
          output[i].val = log10(val1);
          break;
      }
      output[i].type = INT;
    }
  }

  while (output[z].type) z++;
  result = output[--z].val;
  return result;
}
