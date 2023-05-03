#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct string{
    char* str;
    int len;
} string;

typedef struct literal{
    double val;
    int type;
} literal;

typedef enum literal_type {
  BRACK = 1,
  INT = 2,
  OPER = 4,
  FUNC = 5
} literal_type;

// 'c',    's',   't',   'a',    'o',    'u',    'q',    'l', 'g',
// "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"

string validation(string str, int* err);
double validVal(char* input, int *err);

string cut_brackers(string input);
string cut_words(string input);
string cut_spaces(string input);
int chrbrk(char simb, char *str);
char* make_unar_copy(string input, int j);
int compare_liter(char *str1, char *str2);
string change_wrd(string input, int i, char* func);
string cut_liter(string input, int i, char* literal);
string delete_matches(string input, char** literal, int amount);

void pn(string input, literal* output, double xval);
double calc(string input, double xval);

void push(literal obj, literal* stack);
literal pop(literal* stack, int* end);
literal pick(literal* stack, int* empty);
int get_priority(literal obj);

void DrawDouble(double val, int err);
void DrawGraph(string input, double err, double xMax, double xMin, double yMax, double yMin, char* xMaxText, char* xMinText, char* yMaxText,char* yMinText);
void initRange(char* xMaxText, char* xMinText, char* yMaxText,char* yMinText);

#endif
