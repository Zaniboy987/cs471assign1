#include <stdlib.h>
#include <stdio.h>

char token; /* holds the current input character for the parse */

/* declarations to allow arbitrary recursion */
void command(void);
int expr(void);
int term(void);
int factor(void);
int number(void);
int digit(void);

int isadigit(char c) {
  return (c >= '0' && c <= '9');
}

void error(void) { 
  printf("parse error\n");
  exit(1);
}

void getToken(void) { 
  /* tokens are characters */
  token = getchar();
  if (token == '\t' || token ==' ') { 
    getToken();  /* removes whitespaces on input line */
  }
}

void match(char c) { 
  if (token == c) {
    getToken();
  } else {
    error();
  }
}

void command(void) {
  int result = expr();
  if (token == '\n') {
    printf("The result is: %d\n", result);
  } else {
    error();
  }
}

int expr(void) { 
  int result = term();
  while (token == '+' || token == '-') { 
    char op = token;
    match(token);
    int right = term();
    if (op == '+') {
      result += right;
    } else {
      result -= right;  // Subtraction
    }
  }
  return result;
}

int term(void) { 
  int result = factor();
  while (token == '*' || token == '/') { 
    char op = token;
    match(token);
    int right = factor();
    if (op == '*') {
      result *= right;
    } else {
      result /= right;  // Division
    }
  }
  return result;
}

int factor(void) { 
  int result;
  if (token == '(') { 
    match('(');
    result = expr();
    match(')');
  } else {
    result = number();
  }
  return result;
}

int number(void) { 
  int result = digit();
  while (isadigit(token)) {
    result = 10 * result + digit();
  }
  return result;
}

int digit(void) { 
  int result = 0;
  if (isadigit(token)) { 
    result = token - '0';
    match(token);
  } else {
    error();
  }
  return result;
}

void parse(void) { 
  getToken(); /* get the first token */
  command(); /* call the parsing procedure for the start symbol */
}

int main() { 
  printf("Type an arithmetic expression and hit enter: ");
  parse();
  return 0;
}