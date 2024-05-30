#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MIN_CAPACITY 5
#define EMPTY_POS -1
#define EMPTY_VALUE 65

struct ElementType {
    char value;
};

struct StackRecord {
    unsigned int capacity;
    int tos;// top on stack
    struct ElementType *stack_array;
};
typedef struct StackRecord *Stack;

Stack create_Stack(unsigned int capacity) {
    if(capacity < MIN_CAPACITY) {
        printf("The stack's capacity is at least %d!!!", MIN_CAPACITY);
        return NULL;
    }
    Stack S = malloc(sizeof(struct StackRecord));
    if(S == NULL) {
        printf("Out of space!!\n");
        return NULL;
    }
    S->stack_array = malloc(sizeof(struct ElementType)*capacity);
    if(S->stack_array == NULL) {
        printf("Out of space!!\n");
        return NULL;
    }
    S->tos = EMPTY_POS;
    S->capacity = capacity;
    return S;
}

int is_empty(Stack S) {
    return S->tos == EMPTY_POS;
}

void make_null(Stack S) {
    S->tos = EMPTY_POS;
}

void dispose(Stack S) {
    if(S != NULL) {
        free(S->stack_array);
        free(S);
    }
}

int is_full(Stack S) {
    return S->tos == S->capacity - 1;
}

void push(Stack S, struct ElementType e) {
    if(is_full(S)) {
        printf("The stack is full, you can't push anymore!!!\n");
        return;
    }
    S->stack_array[++S->tos] = e;
}

struct ElementType pop(Stack S) {
    if(is_empty(S)) {
        printf("The stack is empty, you can't pop an element from it!!\n");
        struct ElementType e;
        e.value = EMPTY_VALUE;
        return e;
    }
    return S->stack_array[S->tos--];
}

struct ElementType top(Stack S) {
    if (is_empty(S)) {
		printf("The stack is empty, you can't top an element from it!!!\n");
		struct ElementType e;
        e.value = EMPTY_VALUE;
        return e;
	}
    return S->stack_array[S->tos];
}

void show_stack(Stack S) {
    if(is_empty(S)) {
        printf("The stack is EMPTY!!\n");
    } else {
        printf("\nCurrent state of the stack is: ");
        for(int i = S->tos; i >= 0; i--) 
            printf("%c ", S->stack_array[i].value);
        printf("\n");
    }
}

void Infix_To_Postfix(char infix[], char PostFix[]) {
    Stack S = create_Stack(100);
    int current = 0;
    for(int i = 0; i < strlen(infix); i++) {
        if(infix[i] == ' ') continue;
        if((infix[i] >= 65 && infix[i] <= 90) || (infix[i] >= 97 && infix[i] <= 122) || isdigit(infix[i])) {// Chữ cái
            PostFix[current++] = infix[i]; //printf("%c", infix[i]);
        } else {
            struct ElementType e, open, close;
            e.value = infix[i];
            if(infix[i] == '(') push(S, e);// (
            else if(infix[i] == '+' || infix[i] == '-') {// + -
                if(is_empty(S)) push(S, e);
                else {
                    open = top(S);
                    while(open.value != '(') {
                        PostFix[current++] = pop(S).value; //printf("%c", pop(S).value);
                        if(is_empty(S)) break;
                        open = top(S);
                    }
                    push(S, e);
                }
            } else if(infix[i] == '*' || infix[i] == '/') {// * /
                if(is_empty(S)) push(S, e);
                else {
                    open = top(S);
                    if(open.value == '*' || open.value == '/') {
                        PostFix[current++] = pop(S).value; //printf("%c", pop(S).value);
                    }
                    push(S, e);
                } 
            } else {// )
                close = pop(S);
                while(close.value != '(') {
                    PostFix[current++] = close.value; //printf("%c", close.value);
                    close = pop(S);
                }
            }
        }  //show_stack(S);
    }  
    while (!is_empty(S)) {
        PostFix[current++] = pop(S).value; //printf("%c", pop(S).value);
    }
}

int main() {
    char infix[] = "(3*A + B*(C + D*E)/F) - G";
    char PostFix[100];

    Infix_To_Postfix(infix, PostFix);printf("\n");
    printf("%s", PostFix);

}