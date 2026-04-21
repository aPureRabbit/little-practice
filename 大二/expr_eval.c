#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 256

typedef struct {
    double data[MAX_TOKENS];
    int top;
} NumStack;

typedef struct {
    char data[MAX_TOKENS];
    int top;
} OpStack;

static void num_push(NumStack *s, double v) {
    if (s->top + 1 >= MAX_TOKENS) {
        fprintf(stderr, "Number stack overflow\n");
        exit(1);
    }
    s->data[++s->top] = v;
}

static double num_pop(NumStack *s) {
    if (s->top < 0) {
        fprintf(stderr, "Number stack underflow\n");
        exit(1);
    }
    return s->data[s->top--];
}

static void op_push(OpStack *s, char v) {
    if (s->top + 1 >= MAX_TOKENS) {
        fprintf(stderr, "Operator stack overflow\n");
        exit(1);
    }
    s->data[++s->top] = v;
}

static char op_pop(OpStack *s) {
    if (s->top < 0) {
        fprintf(stderr, "Operator stack underflow\n");
        exit(1);
    }
    return s->data[s->top--];
}

static int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

static double apply(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0.0) {
                fprintf(stderr, "Division by zero\n");
                exit(1);
            }
            return a / b;
        default:
            fprintf(stderr, "Unknown operator %c\n", op);
            exit(1);
    }
}

static void dump_state(const NumStack *nums, const OpStack *ops, const char *info) {
    printf("%-20s | nums:", info);
    for (int i = 0; i <= nums->top; ++i) printf(" %.2f", nums->data[i]);
    printf(" | ops:");
    for (int i = 0; i <= ops->top; ++i) printf(" %c", ops->data[i]);
    printf("\n");
}

static void reduce_once(NumStack *nums, OpStack *ops) {
    double b = num_pop(nums);
    double a = num_pop(nums);
    char op = op_pop(ops);
    double r = apply(a, b, op);
    num_push(nums, r);
}

static double evaluate(const char *expr) {
    NumStack nums = {.top = -1};
    OpStack ops = {.top = -1};
    size_t i = 0;

    dump_state(&nums, &ops, "start");

    while (expr[i]) {
        if (isspace((unsigned char)expr[i])) {
            ++i;
            continue;
        }

        if (isdigit((unsigned char)expr[i]) || expr[i] == '.') {
            char buf[64];
            size_t j = 0;
            while (isdigit((unsigned char)expr[i]) || expr[i] == '.') {
                if (j + 1 >= sizeof(buf)) {
                    fprintf(stderr, "Number too long\n");
                    exit(1);
                }
                buf[j++] = expr[i++];
            }
            buf[j] = '\0';
            num_push(&nums, atof(buf));
            dump_state(&nums, &ops, "push num");
            continue;
        }

        if (strchr("+-*/", expr[i])) {
            char cur = expr[i];
            while (ops.top >= 0 && precedence(ops.data[ops.top]) >= precedence(cur)) {
                reduce_once(&nums, &ops);
                dump_state(&nums, &ops, "reduce");
            }
            op_push(&ops, cur);
            ++i;
            dump_state(&nums, &ops, "push op");
            continue;
        }

        if (expr[i] == '(') {
            op_push(&ops, expr[i]);
            ++i;
            dump_state(&nums, &ops, "push (");
            continue;
        }

        if (expr[i] == ')') {
            while (ops.top >= 0 && ops.data[ops.top] != '(') {
                reduce_once(&nums, &ops);
                dump_state(&nums, &ops, "reduce");
            }
            if (ops.top < 0) {
                fprintf(stderr, "Mismatched parentheses\n");
                exit(1);
            }
            op_pop(&ops);  // pop '('
            ++i;
            dump_state(&nums, &ops, "pop (");
            continue;
        }

        fprintf(stderr, "Unexpected char: %c\n", expr[i]);
        exit(1);
    }

    while (ops.top >= 0) {
        if (ops.data[ops.top] == '(') {
            fprintf(stderr, "Mismatched parentheses\n");
            exit(1);
        }
        reduce_once(&nums, &ops);
        dump_state(&nums, &ops, "reduce");
    }

    if (nums.top != 0) {
        fprintf(stderr, "Invalid expression\n");
        exit(1);
    }
    dump_state(&nums, &ops, "done");
    return nums.data[0];
}

int main(void) {
    char line[512];
    printf("Input expression: ");
    if (!fgets(line, sizeof(line), stdin)) return 0;
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';

    double result = evaluate(line);
    printf("Result = %.6f\n", result);
    return 0;
}
