#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <string.h>

typedef struct Node {
    void* number;
    int isNum;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

int isFloat;

void* stackPop(Stack* s)
{
    if (s->top == ((void*)0)) {
        printf("Error: stack is empty, cannot pop");
        exit(-1);
    }
    void* tmp;
    Node* tmpNode = s->top;
    tmp = s->top->number;
    s->top = s->top->next;
    free(tmpNode);
    return tmp;
}

void stackPush(Stack* s, void* num, int isNum)
{
    Node* tmp = malloc(sizeof(Node));
    tmp->number = num;
    tmp->isNum = isNum;
    tmp->next = s->top;
    s->top = tmp;
    return;
}

typedef struct List {
    Node* start;
    Node* end;
} List;

int ExToken=0;

void listPush(List* l, void* n, int isNum)
{

    Node* tmp = malloc(sizeof(Node));
    tmp->number = n;
    tmp->isNum = isNum;
    tmp->next = NULL;
    if (l->start == NULL) {
        l->start = tmp;
        l->end = tmp;
        return;
    }
    l->end->next = tmp;
    l->end = tmp;
    return;
}

void* listPop(List* l)
{
    if (l->start == NULL) {
        printf("Error:list is empty, cannon pop");
        exit(-1);
    }
    Node* tmp = l->start;
    void* tmpNumb = l->start->number;
    l->start = l->start->next;
    free(tmp);
    return tmpNumb;
}

int opPriority(int op1, int op2)
{
    if ((op1 == '+' || op1 == '-') && (op2 == '+' || op2 == '-'))
        return 0;
    if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
        return 1;
    if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/'))
        return 2;
    if ((op1 == '*' || op1 == '/') && (op2 == '*' || op2 == '/'))
        return 0;
    return -1;
}

List parse()
{
    List list;
    list.start = ((void*)0);
    list.end = ((void*)0);
    Stack stack;
    stack.top = ((void*)0);
    long numb = 0;
    void* ptr;
    char tmp;
    int flagNumb = 0;
    do {
        tmp = getchar();
        switch (tmp) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (ExToken!=0)
                exit (-3);
            numb = numb * 10 + (tmp - '0');
            flagNumb = 1;
            break;
        case '(':
            if (flagNumb) {
                if (isFloat == 1) {
                    ptr = malloc(sizeof(double));
                    *(double*)ptr = numb;
                } else {
                    ptr = malloc(sizeof(long));
                    *(long*)ptr = numb;
                }
                listPush(&list, ptr, 1);
                numb = 0;
                flagNumb = 0;
                ExToken=1;
            }
            ptr = malloc(sizeof(char));
            *(char*)ptr = tmp;
            stackPush(&stack, ptr, 0);
            break;
        case ')':
            if (flagNumb) {
                if (isFloat == 1) {
                    ptr = malloc(sizeof(double));
                    *(double*)ptr = numb;
                } else {
                    ptr = malloc(sizeof(long));
                    *(long*)ptr = numb;
                }
                ExToken=1;
                listPush(&list, ptr, 1);
                numb = 0;
                flagNumb = 0;

            }
            while (stack.top != NULL && *(char*)stack.top->number != '(') {
                void* tNumb = stackPop(&stack);
                listPush(&list, tNumb, 0);
            }
            if (stack.top == NULL)
                exit(-2);
            if (stack.top != NULL) {
                stackPop(&stack);
            }
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            if (flagNumb) {
                if (isFloat == 1) {
                    ptr = malloc(sizeof(double));
                    *(double*)ptr = numb;
                } else {
                    ptr = malloc(sizeof(long));
                    *(long*)ptr = numb;
                }
                ExToken=1;
                listPush(&list, ptr, 1);
                numb = 0;
                flagNumb = 0;

            }
            if (ExToken==0)
                exit (-3);
            ExToken=0;
            while (stack.top != NULL && opPriority(*(char*)stack.top->number, tmp) != 2 && *(char*)stack.top->number != '(') {
                void* tNumb = stackPop(&stack);
                listPush(&list, tNumb, 0);
            }
            ptr = malloc(sizeof(char));
            *(char*)ptr = tmp;
            stackPush(&stack, ptr, 0);

            break;
        case EOF:
            if (flagNumb) {
                if (isFloat == 1) {
                    ptr = malloc(sizeof(double));
                    *(double*)ptr = numb;
                } else {
                    ptr = malloc(sizeof(long));
                    *(long*)ptr = numb;
                }
                listPush(&list, ptr, 1);
                numb = 0;
                flagNumb = 0;
                ExToken=1;
            }

            while (stack.top != NULL) {
                void* tNumb = stackPop(&stack);
                listPush(&list, tNumb, 0);
            }
            goto BREAK;
        case '\t':
        case '\r':
        case '\v':
        case '\f':
        case '\n':
        case ' ':
            if (flagNumb) {
                if (isFloat == 1) {
                    ptr = malloc(sizeof(double));
                    *(double*)ptr = numb;
                } else {
                    ptr = malloc(sizeof(long));
                    *(long*)ptr = numb;
                }
                listPush(&list, ptr, 1);
                numb = 0;
                flagNumb = 0;
                ExToken=1;
            }
            break;
        default:
            printf("Ne rabotaet?ny xz, zaplach`");
            exit(-1);
        }

    } while (tmp != -1);
BREAK:
    return list;
}

void* Calculate(List* list)
{
    Node* tmp = list->start;
    long cl;
    double cf;
    Stack stack;
    stack.top = NULL;
    while (tmp != NULL) {
        if (tmp->isNum) {
            stackPush(&stack, tmp->number, 1);
        } else {
            if (stack.top != NULL && stack.top->next != NULL) {
                void* a = stackPop(&stack); // 2
                void* b = stackPop(&stack); // 1
                long l1, l2;
                double f1, f2;
                if (isFloat) {
                    f1 = *(double*)b;
                    f2 = *(double*)a;
                    if (*(char*)tmp->number == '+')
                        cf = f1 + f2;
                    if (*(char*)tmp->number == '-')
                        cf = f1 - f2;
                    if (*(char*)tmp->number == '*')
                        cf = f1 * f2;
                    if (*(char*)tmp->number == '/')
                        cf = f1 / f2;
                    void* t = malloc(sizeof(double));
                    *(double*)t = cf;
                    stackPush(&stack, t, 1);

                } else {
                    l1 = *(long*)b;
                    l2 = *(long*)a;
                    if (*(char*)tmp->number == '+')
                        cl = l1 + l2;
                    if (*(char*)tmp->number == '-')
                        cl = l1 - l2;
                    if (*(char*)tmp->number == '*')
                        cl = l1 * l2;
                    if (*(char*)tmp->number == '/')
                        cl = l1 / l2;
                    void* t = malloc(sizeof(long));
                    *(long*)t = cl;
                    stackPush(&stack, t, 1);
                }
            } else {
                printf("Error: wrong expression");
                exit(-2);
            }
        }
        tmp = tmp->next;
    }

    void* res = stack.top->number;
    while (stack.top != NULL && stack.top->next != NULL) {
        Node* tmp = stack.top;
        stack.top = stack.top->next;
        free(tmp->number);
        free(tmp);
    }
    return res;
}

#ifndef GTEST
int main(int argc, char** argv)
{

    if (argc == 1)
        isFloat = 0;
    else if (argc >= 2) {
        if (!strcmp(argv[1], "--float"))
            isFloat = 1;
        else {
            isFloat = 0;
        }
    } else
        isFloat = 0;
    List list = parse();
    void* res = Calculate(&list);
    if (!isFloat)
        printf("%ld", *(long*)res);
    else
        printf("%0.5f", *(double*)res);
    Node* current = list.start;
    while (current != NULL) {
        Node* next = current->next;
        free(current->number);
        free(current);
        current = next;
    }
    list.start = NULL;
    list.end = NULL;

    return 0;
}
#endif
