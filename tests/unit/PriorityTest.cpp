#include <gtest/gtest.h>


extern "C"{

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

TEST(TestPrioritry,TestisOP){
    int a='+';
    int b='*';
    EXPECT_EQ(2,opPriority(a,b))<<"Error in operation priority";

}

