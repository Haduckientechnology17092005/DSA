#include <stdio.h>
#include <stdlib.h>

struct StackNode {
    char data;
    struct StackNode* next;
};

struct StackNode* newNode(char data) {
    struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

int isEmpty(struct StackNode* root) {
    return !root;
}

void push(struct StackNode** root, char data) {
    struct StackNode* stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

char pop(struct StackNode** root) {
    if (isEmpty(*root))
        return '\0';
    struct StackNode* temp = *root;
    *root = (*root)->next;
    char popped = temp->data;
    free(temp);
    return popped;
}

int isBalanced(char exp[]) {
    struct StackNode* stack = NULL;
    int i = 0;
    while (exp[i]) {
        if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
            push(&stack, exp[i]);
        } else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') {
            if (isEmpty(stack))
                return 0;
            char popped = pop(&stack);
            if ((exp[i] == ')' && popped != '(') || (exp[i] == ']' && popped != '[') || (exp[i] == '}' && popped != '{'))
                return 0;
        }
        i++;
    }
    return isEmpty(stack);
}

int main() {
    char exp[100];
    printf("Enter expression: ");
    fgets(exp, sizeof(exp), stdin);

    if (isBalanced(exp))
        printf("The expression is balanced.\n");
    else
        printf("The expression is not balanced.\n");

    return 0;
}
