#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN_CAPACITY 5
#define empty_pos -1

struct ElementType {
    char value;
};

struct StackRecord {
    unsigned int capacity;
    int tos;
    struct ElementType *stack_array;
};

typedef struct StackRecord *Stack;

// Function to create a stack
Stack create_stack(unsigned int capacity) {
    if (capacity < MIN_CAPACITY) {
        printf("The Stack's capacity is at least %d\n", MIN_CAPACITY);
        return NULL;
    }
    Stack S = malloc(sizeof(struct StackRecord));
    if (S == NULL) {
        printf("Out of space\n");
        return NULL;
    }
    S->stack_array = malloc(capacity * sizeof(struct ElementType));
    if (S->stack_array == NULL) {
        printf("Out of space\n");
        free(S);
        return NULL;
    }
    S->capacity = capacity;
    S->tos = empty_pos;
    return S;
}

bool is_empty(Stack S) {
    return (S->tos == empty_pos);
}

bool is_full(Stack S) {
    return (S->tos == S->capacity - 1);
}

void push(Stack S, struct ElementType e) {
    if (is_full(S)) {
        printf("The Stack is full\n");
        return;
    } else {
        S->stack_array[++S->tos] = e;
    }
}
struct ElementType pop(Stack S) {
    struct ElementType empty_element = {'\0'};
    if (is_empty(S)) {
        printf("The Stack is empty\n");
        return empty_element;
    } else {
        return S->stack_array[S->tos--];
    }
}

struct ElementType top(Stack S) {
    struct ElementType empty_element = {'\0'};
    if (is_empty(S)) {
        printf("The Stack is empty\n");
        return empty_element;
    } else {
        return S->stack_array[S->tos];
    }
}

void display(Stack S) {
    if (is_empty(S)) {
        printf("The Stack is empty\n");
        return;
    } else {
        int i;
        for (i = S->tos; i >= 0; i--) {
            printf("%c\n", S->stack_array[i].value);
        }
    }
}

bool isBalanced(char exp[]) {
    Stack stack = create_stack(strlen(exp));
    int i = 0;
    while (exp[i] != '\0') {
        if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
            struct ElementType element = {exp[i]};
            push(stack, element);
        } else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') {
            if (is_empty(stack))
                return false;
            struct ElementType popped = pop(stack);
            if ((exp[i] == ')' && popped.value != '(') ||
                (exp[i] == ']' && popped.value != '[') ||
                (exp[i] == '}' && popped.value != '{'))
                return false;
        }
        i++;
    }
    return is_empty(stack);
}

int main() {
    char exp[100];
    printf("Enter expression: ");
    fgets(exp, sizeof(exp), stdin);
    if (isBalanced(exp)) {
        printf("The expression is balanced.\n");
    } else {
        printf("The expression is not balanced.\n");
    }
    return 0;
}
