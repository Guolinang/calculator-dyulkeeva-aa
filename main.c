#include "stdlib.h"
#include "stdio.h"


typedef struct Node {
	int number;
    int isNum;
	struct Node* next;
}Node;

typedef struct Stack{
	Node* top;
}Stack;

int stackPop(Stack* s) {
	if (s->top == ((void*)0)) {
		printf("Error: stack is empty, cannot pop");
		return -1;
	}
	int tmp;
	Node* tmpNode=s->top;
	tmp = s->top->number;
	s->top = s->top->next;
	free(tmpNode);
	return tmp;
}

void stackPush(Stack* s, int num,int isNum) {
	Node* tmp=malloc(sizeof(Node));
	tmp->number = num;
    tmp->isNum=isNum;
	tmp->next = s->top;
	s->top = tmp;
	return;
}

void stackPrint(Stack* s) {
	Node* tmpTop= s->top;
	while (tmpTop != ((void*)0)) {
		printf("%d\n", tmpTop->number);
		tmpTop = tmpTop->next;
	}
}

typedef struct List {
	Node* start;
	Node* end;
}List;

void listPush(List* l, int n,int isNum ){

	Node* tmp=malloc(sizeof(Node));
	tmp->number = n;
    tmp->isNum=isNum;
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

int listPop(List* l) {
	if (l->start == NULL) {
		printf("Error:list is empty, cannon pop");
		return -1;
	}
	Node* tmp=l->start;
	int tmpNumb = l->start->number;
	l->start = l->start->next;
	free(tmp);
	return tmpNumb;
}

int opPriority(int op1, int op2) {
	if ((op1 == '+' || op1 == '-') && (op2 == '+' || op2 == '-')) return 0;
	if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-')) return 1;
	if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) return 2;
	if ((op1 == '*' || op1 == '/') && (op2 == '*' || op2 == '/')) return 0;
}

List parse() {
	List list;
	list.start = ((void*)0);
	list.end = ((void*)0);
	Stack stack;
	stack.top = ((void*)0);
	int numb=0;
	char tmp;
	int flagNumb=0;
	do {
		tmp=getchar();
		switch (tmp) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			numb = numb * 10 + (tmp - '0');
			flagNumb = 1;
			break;
		case '(':
			if (flagNumb) {
				listPush(&list, numb, 1);
				numb = 0;
				flagNumb = 0;
			}
			stackPush(&stack, tmp, 0);
			break;
		case ')':
			if (flagNumb) {
				listPush(&list, numb, 1);
				numb = 0;
				flagNumb = 0;
			}
			while (stack.top!= NULL && stack.top->number != '(') {
				int tNumb = stackPop(&stack);
				listPush(&list, tNumb, 0);
			}
			if (stack.top != NULL)
				stackPop(&stack);
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			if (flagNumb) {
				listPush(&list, numb, 1);
				numb = 0;
				flagNumb = 0;
			}
			while (stack.top != NULL && opPriority(stack.top->number, tmp) != 2 && stack.top->number!='(') {
				int tNumb = stackPop(&stack);
				listPush(&list, tNumb, 0);
			}
			stackPush(&stack, tmp, 0);

			break;
        case '\n':
		case EOF:
			if (flagNumb) {
				listPush(&list, numb, 1);
				numb = 0;
				flagNumb = 0;			}

            while (stack.top != NULL) {
                int tNumb = stackPop(&stack);
                listPush(&list, tNumb,0);
            }
            goto BREAK;
		case ' ':
			if (flagNumb) {
				listPush(&list, numb, 1);
				numb = 0;
				flagNumb = 0;			}
			break;
		default:
			printf("Ne rabotaet?ny xz, zaplach`");
			break;

		}

	}while (tmp!=-1);
	BREAK:
	return list;
}

void Calculate(List* list) {
     Node* tmp=list->start;
     int c;
     Stack stack;
     stack.top=NULL;
     while (tmp!=NULL){
            if (tmp->isNum){
                stackPush(&stack,tmp->number,1);
            }
            else{
                if (stack.top!=NULL && stack.top->next!=NULL){
                    int a=stackPop(&stack);//2
                    int b=stackPop(&stack);//1
                    if (tmp->number=='+')
                        c=b+a;
                    if (tmp->number=='-')
                        c=b-a;
                    if (tmp->number=='*')
                        c=b*a;
                    if (tmp->number=='/')
                        c=b/a;
                    stackPush(&stack,c,1);
                }
                else {
                    printf ("Error: wrong expression");
                    return;
                }
            }
            tmp=tmp->next;
    }
    printf ("%d",stack.top->number);
}

void printList(List* l) {
	Node* s = l->start;
	while (s != NULL) {
        if (s->isNum)
            printf("%d\n", s->number);
		else
            printf("%c\n", s->number);
        s = s->next;
	}
}

int main() {
	List list = parse();
	//printList(&list);
    Calculate(&list);
	return 0;

}
