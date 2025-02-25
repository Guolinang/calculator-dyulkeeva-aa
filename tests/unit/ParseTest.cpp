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

TEST(ParseTest, pTest)
{

    const char* input = "3+4*2";
    FILE* stream = fmemopen((void*)input, strlen(input), "r");
    stdin = stream;

    List list = parse();
    fclose(stream);

    Node* current = list.start;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(*(long*)current->number, 3);
    current = current->next;

    ASSERT_NE(current, nullptr);
    EXPECT_EQ(*(long*)current->number, 4);
    current = current->next;

    ASSERT_NE(current, nullptr);
    EXPECT_EQ(*(long*)current->number, 2);
    current = current->next;

    ASSERT_NE(current, nullptr);
    EXPECT_EQ(*(char*)current->number, '*');
    current = current->next;

    ASSERT_NE(current, nullptr);
    EXPECT_EQ(*(char*)current->number, '+');

    Node* cur = list.start;
    while (cur != NULL) {
        Node* next = cur->next;
        free(cur->number);
        free(cur);
        cur = next;
    }
    list.start = NULL;
    list.end = NULL;
}
