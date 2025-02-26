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


void listPush(List* l, void* n, int isNum);
void* listPop(List* l);
void* Calculate(List* list);
}

TEST(CalculateTest, TestC)
{
    List list;
    list.start = NULL;
    list.end = NULL;
    void* a = malloc(sizeof(long));
    void* b = malloc(sizeof(long));
    void* c = malloc(sizeof(long));
    void* d = malloc(sizeof(char));
    void* e = malloc(sizeof(char));
    *(long*)a = 1;
    *(long*)b = 2;
    *(long*)c = 3;
    *(char*)d = '+';
    *(char*)e = '*';
    listPush(&list, a, 1);
    listPush(&list, b, 1);
    listPush(&list, c, 1);
    listPush(&list, d, 0);
    listPush(&list, e, 0);
    void* res = Calculate(&list);
    EXPECT_EQ(*(int*)res, 5) << "Error in calculate";
    Node* current = list.start;
    while (current != NULL) {
        Node* next = current->next;
        free(current->number);
        free(current);
        current = next;
    }
    list.start = NULL;
    list.end = NULL;
}
