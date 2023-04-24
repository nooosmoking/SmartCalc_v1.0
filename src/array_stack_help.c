#include "calc.h"

void push(literal obj, literal* stack) {
  int i = 0;
  for (; stack[i].type; i++) {
  };
  stack[i].val = obj.val;
  stack[i].type = obj.type;
}

literal pop(literal* stack, int* empty) {
  int i = 0;
  literal obj = {0};
  for (; stack[i].type; i++) {
  };
  if (i == 0) {
    *empty = 1;
  } else {
    i--;
    obj.val = stack[i].val;
    obj.type = stack[i].type;
    stack[i].val = 0;
    stack[i].type = 0;
  }
  return obj;
}

literal pick(literal* stack, int* empty) {
  int i = 0;
  literal obj = {0};
  for (; stack[i].type; i++) {
  };
  if (i == 0) {
    *empty = 1;
  } else {
    i--;
    obj.val = stack[i].val;
    obj.type = stack[i].type;
  }
  return obj;
}

int get_priority(literal obj) {
  int priority = 0;
  if ((char)obj.val == '(') {
    priority = 1;
  } else if ((char)obj.val == '+' || (char)obj.val == '-') {
    priority = 2;
  } else if ((char)obj.val == '*' || (char)obj.val == '/' ||
             (char)obj.val == 'm') {
    priority = 3;
  } else if ((char)obj.val == '^') {
    priority = 4;
  } else if (obj.type == FUNC) {
    priority = 5;
  }

  return priority;
}