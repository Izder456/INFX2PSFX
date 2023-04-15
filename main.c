#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char item) {
  if (top >= MAX - 1) {
    printf("\nStack Overflow.");
  } else {
    stack[++top] = item;
  }
}

char pop() {
  if (top < 0) {
    printf("Stack Underflow.\n");
    exit(1);
  } else {
    return stack[top--];
  }
}

int precedence(char symbol) {
  switch (symbol) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  case '^':
    return 3;
  default:
    return 0;
  }
}

int isOperator(char symbol) {
  switch (symbol) {
  case '+':
  case '-':
  case '*':
  case '/':
  case '^':
    return 1;
  default:
    return 0;
  }
}
void infixToPostfix(char infix[], char postfix[]) {
    int i, j;
    char item, x;

    i = 0;
    j = 0;

    while (infix[i] != '\0') {
        item = infix[i];

        if (item == '(') {
            if (i > 0 && (isdigit(infix[i - 1]) || isalpha(infix[i - 1]))) {
                while (top != -1 && precedence(stack[top]) >= precedence('*')) {
                    x = pop();
                    postfix[j++] = x;
                }
                push('*');
            }
            push(item);
        } else if (isdigit(item)) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        } else if (isalpha(item)) {
            postfix[j++] = item;
        } else if (isOperator(item)) {
            while (top != -1 && precedence(stack[top]) >= precedence(item)) {
                x = pop();
                postfix[j++] = x;
            }
            push(item);
        } else if (item == ')') {
            x = pop();
            while (x != '(') {
                postfix[j++] = x;
                x = pop();
            }
        } else if (item == ' ') {
        } else {
            printf("\nInvalid infix expression.");
            exit(1);
        }
        i++;
    }

    while (top > -1) {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}
int main() {
  char infix[MAX], postfix[MAX];

  printf("Enter an infix expression: ");
  fgets(infix, MAX, stdin);
  infix[strcspn(infix, "\n")] = '\0';
  infixToPostfix(infix, postfix);

  printf("Postfix expression: %s\n", postfix);

  return 0;
}
