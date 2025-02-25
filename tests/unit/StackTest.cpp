#include <gtest/gtest.h>

extern "C" {

typedef struct Node {
    void* number;
    int isNum;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

typedef struct List {
    Node* start;
    Node* end;
} List;

void* stackPop(Stack* s);
void stackPush(Stack* s, void* num, int isNum);
void stackPrint(Stack* s);
void listPush(List* l, void* n, int isNum);
void* listPop(List* l);
int opPriority(int op1, int op2);
List parse();
void Calculate(List* list);
}

TEST(TestStack, TestPushPopPrint)
{
    void* a = malloc(sizeof(long));
    void* b = malloc(sizeof(long));
    void* c = malloc(sizeof(long));
    *(long*)a = 1;
    *(long*)b = 2;
    *(long*)c = 3;
    Stack s;
    stackPush(&s, a, 1);
    stackPush(&s, b, 1);
    stackPush(&s, c, 1);
    void* a1;
    void* b1;
    void* c1;
    c1 = stackPop(&s);
    b1 = stackPop(&s);
    a1 = stackPop(&s);
    EXPECT_EQ(a1, a) << "Error in push-pop in stack";
    EXPECT_EQ(b1, b) << "Error in push-pop in stack";
    EXPECT_EQ(c1, c) << "Error in push-pop in stack";
}
