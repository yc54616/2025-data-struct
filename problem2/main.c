#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 1000

typedef struct {
    char data[MAX];
    int top;
} CharStack;

typedef struct {
    double data[MAX];
    int top;
} DoubleStack;

void initCharStack(CharStack* s) {
    s->top = -1;
}

int isCharEmpty(CharStack* s) {
    return s->top == -1;
}

void pushChar(CharStack* s, char c) {
    s->data[++(s->top)] = c;
}

char popChar(CharStack* s) {
    if (isCharEmpty(s)) {
        printf("문자 스택 언더플로우\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

char peekChar(CharStack* s) {
    if (isCharEmpty(s)) {
        return '\0';
    }
    return s->data[s->top];
}

void initDoubleStack(DoubleStack* s) {
    s->top = -1;
}

int isDoubleEmpty(DoubleStack* s) {
    return s->top == -1;
}

void pushDouble(DoubleStack* s, double d) {
    s->data[++(s->top)] = d;
}

double popDouble(DoubleStack* s) {
    if (isDoubleEmpty(s)) {
        printf("숫자 스택 언더플로우\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void infixToPostfix(const char* infix, char* postfix) {
    CharStack opStack;
    initCharStack(&opStack);
    int j = 0;
    int len = strlen(infix);

    for (int i = 0; i < len; i++) {
        char c = infix[i];

        if (isspace(c)) continue;

        if (isdigit(c)) {
            while (isdigit(c) || c == '.') {
                postfix[j++] = c;
                c = infix[++i];
            }
            postfix[j++] = ' ';
        }
        else if (c == '(') {
            pushChar(&opStack, c);
        }
        else if (c == ')') {
            while (!isCharEmpty(&opStack) && peekChar(&opStack) != '(') {
                postfix[j++] = popChar(&opStack);
                postfix[j++] = ' ';
            }
            if (isCharEmpty(&opStack)) {
                printf("오류: 짝이 맞지 않는 괄호\n");
                exit(1);
            }
            popChar(&opStack); // '(' 제거
        }
        else if (isOperator(c)) {
            while (!isCharEmpty(&opStack) && precedence(peekChar(&opStack)) >= precedence(c)) {
                postfix[j++] = popChar(&opStack);
                postfix[j++] = ' ';
            }
            pushChar(&opStack, c);
        }
        else {
            printf("오류: 지원하지 않는 문자 '%c'\n", c);
            exit(1);
        }
    }

    while (!isCharEmpty(&opStack)) {
        if (peekChar(&opStack) == '(') {
            printf("오류: 짝이 맞지 않는 괄호\n");
            exit(1);
        }
        postfix[j++] = popChar(&opStack);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

double evaluatePostfix(const char* postfix) {
    DoubleStack valStack;
    initDoubleStack(&valStack);
    int len = strlen(postfix);

    for (int i = 0; i < len; i++) {
        char c = postfix[i];

        if (isspace(c)) continue;

        if (isdigit(c)) {
            double num = 0;
            int decimal = 0;
            double frac = 0.1;

            while (isdigit(c) || c == '.') {
                if (c == '.') {
                    decimal = 1;
                }
                else {
                    if (!decimal)
                        num = num * 10 + (c - '0');
                    else {
                        num += (c - '0') * frac;
                        frac *= 0.1;
                    }
                }
                c = postfix[++i];
            }
            pushDouble(&valStack, num);
            i--;
        }
        else if (isOperator(c)) {
            double b = popDouble(&valStack);
            double a = popDouble(&valStack);
            double result = 0;
            switch (c) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if (b == 0) {
                        printf("오류: 0으로 나누기\n");
                        exit(1);
                    }
                    result = a / b; 
                    break;
                case '^': result = pow(a, b); break;
            }
            pushDouble(&valStack, result);
        }
        else {
            printf("오류: 지원하지 않는 문자 '%c' (후위표기식)\n", c);
            exit(1);
        }
    }

    if (valStack.top != 0) {
        printf("오류: 잘못된 수식 (남은 데이터 있음)\n");
        exit(1);
    }

    return popDouble(&valStack);
}

int main() {
    char infix[MAX];
    char postfix[MAX];

    printf("수식 입력 (예: 3 + 4 * (2 - 1)^2 ) : ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = '\0'; // 줄바꿈 제거

    infixToPostfix(infix, postfix);
    printf("후위표기식: %s\n", postfix);

    double result = evaluatePostfix(postfix);
    printf("계산 결과: %.6lf\n", result);

    return 0;
}
