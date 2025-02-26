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
}

TEST(TestList, TestPush)
{

    List l;
    l.start = NULL;
    l.end = NULL;
    void* a = malloc(sizeof(long));
    void* b = malloc(sizeof(long));
    void* c = malloc(sizeof(long));
    *(long*)a = 1;
    *(long*)b = 2;
    *(long*)c = 3;
    listPush(&l, a, 1);
    listPush(&l, b, 1);
    listPush(&l, c, 1);
    EXPECT_EQ(l.start->number, a) << "Error in push in list";
    EXPECT_EQ(l.start->next->number, b) << "Error in push in list";
    EXPECT_EQ(l.start->next->next->number, c) << "Error in push in list";
    Node* current = l.start;
    while (current != NULL) {
        Node* next = current->next;
        free(current->number);
        free(current);
        current = next;
    }
    l.start = NULL;
    l.end = NULL;
}

TEST(TestList, TestPop)
{

    List l;
    l.start = NULL;
    l.end = NULL;
    void* a = malloc(sizeof(long));
    void* b = malloc(sizeof(long));
    void* c = malloc(sizeof(long));
    *(long*)a = 1;
    *(long*)b = 2;
    *(long*)c = 3;
    listPush(&l, a, 1);
    listPush(&l, b, 1);
    listPush(&l, c, 1);
    void* a1;
    void* b1;
    void* c1;
    a1 = listPop(&l);
    b1 = listPop(&l);
    c1 = listPop(&l);
    EXPECT_EQ(a1, a) << "Error in pop in list";
    EXPECT_EQ(b1, b) << "Error in pop in list";
    EXPECT_EQ(c1, c) << "Error in pop in list";
    Node* current = l.start;
    while (current != NULL) {
        Node* next = current->next;
        free(current->number);
        free(current);
        current = next;
    }
    l.start = NULL;
    l.end = NULL;
}
