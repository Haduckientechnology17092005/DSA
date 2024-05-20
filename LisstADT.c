#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct ElementType {
    unsigned long ID;
    char *name;
};

struct Node {
    struct ElementType value;
    struct Node* next;
};

typedef struct Node* List;
typedef struct Node* Position;

Position insert(List *pL, Position p, struct ElementType e){
    Position newItem = malloc(sizeof(struct Node));
    newItem -> value = e;
    newItem -> next = p->next;
    p->next = newItem;
    return newItem;
}

List create_list(){
    List headerNode = malloc(sizeof(struct Node));
    headerNode -> next = NULL;
    return headerNode;
}

void delete_list(List *pL, int key){
    Position temp = *pL;
    Position prev = NULL;
    //Xóa node đầu tiên
    if(temp != NULL && temp->value.ID == key){
        *pL = temp->next;
        free(temp);
        return;
    }
    //Duyệt anh sách để tìm nút cần xóa
    while(temp != NULL && temp->value.ID != key){
        prev = temp;
        temp = temp -> next;
    }
    if(temp == NULL)
        return;
    //Xóa node cuối cùng
    if(temp->next == NULL){
        prev -> next = NULL;
        free(temp);
        return;
    }
    //Loại bỏ node temp
    prev -> next = temp -> next;
    free(temp);
}

void display(List pL){
    int count = 1;
    pL = pL->next;
    while(pL != NULL){
        printf("%d. %lu %s\n", count, pL->value.ID, pL->value.name);
        pL = pL->next;
        count++;
    }
}

int main(){
    List pL = create_list();
    struct ElementType e1,e2,e3,e4;
    e1.ID = 1; e1.name = "e1";
    e2.ID = 2; e2.name = "e2";
    e3.ID = 3; e3.name = "e3";
    e4.ID = 4; e4.name = "e4";

    Position p;
    p = insert(&pL, pL, e1);
    p = insert(&pL, p, e2);
    p = insert(&pL, p, e3);
    p = insert(&pL, p, e4);

    display(pL);
    delete_list(&pL, 3);
    display(pL);
    free(pL);
    return 0;
}