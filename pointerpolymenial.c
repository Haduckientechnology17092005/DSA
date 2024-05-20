#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
//Linked lists pointer array
struct Node {
    int coeff;
    int expo;
    struct Node *next;
};

typedef struct Node *polynomial;
typedef struct Node *Position;

polynomial createpolynomial()
{
    polynomial headerNode = malloc(sizeof(struct Node));
    headerNode->next = NULL;
    headerNode->expo=INT_MAX;
    return headerNode;
}

void add_polynomial(polynomial poly, int coeff, int expo)
{
    Position prev = poly;
    while(poly->next != NULL && poly->next->expo > expo)
    {
        prev = poly;
        poly = poly->next;
    }

    // Find position p to insert into linked lists
    if(poly->next != NULL && poly->next->expo == expo)
    {
        poly->next->coeff += coeff;
    }
    else
    {
        // Create new node
        Position newItem = malloc(sizeof(struct Node));
        newItem->coeff = coeff;
        newItem->expo = expo;

        // Insert into the linked list
        newItem->next = poly->next;
        poly->next = newItem;./
    }
}

void display(polynomial poly)
{
    poly = poly->next;
    polynomial headerNode = poly;
    while(poly!=NULL)
    {
        if (poly->coeff!=0){
			if (poly->coeff<0)
				if (poly!=headerNode)
					printf(" - ");
				else
					printf("-");
			else if (poly!=headerNode)
				printf(" + ");
			if (abs(poly->coeff)!=1)
				printf("%d",abs(poly->coeff));
			if (poly->expo>1)
				printf("x^%d",poly->expo);
			else if (poly->expo==1)
				printf("x");
		}
        poly = poly->next;
        headerNode = headerNode->next;
    }
}
void sum_polynomial(polynomial poly1, polynomial poly2, polynomial poly_sum)
{
    poly1 = poly1->next;
    poly2 = poly2->next;
    while(poly1!=NULL)
    {
        add_polynomial(poly_sum, poly1->coeff, poly1->expo);
        poly1 = poly1->next;
    }
    while (poly2 != NULL)
    {
        add_polynomial(poly_sum, poly2->coeff, poly2->expo);
        poly2 = poly2->next;
    }
}

void mul_polynomial(polynomial poly1, polynomial poly2, polynomial poly_multiply) {
    poly1 = poly1->next;
    poly2 = poly2->next;
    while (poly1 != NULL) 
    {
        polynomial temp = poly2; 
        // Temp pointer to traverse poly2 for each term in poly1
        while (temp != NULL) 
        {
            int coeff = poly1->coeff * temp->coeff;
            int expo = poly1->expo + temp->expo;
            add_polynomial(poly_multiply, coeff, expo);
            temp = temp->next;
        }
        poly1 = poly1->next;
    }
}

int main ()
{
    polynomial poly1 = createpolynomial();
    polynomial poly2 = createpolynomial();
    polynomial poly_sum = createpolynomial();
    polynomial poly_multiphy = createpolynomial();

    add_polynomial(poly1, 10, 10);
    add_polynomial(poly1, 20, 35);

    add_polynomial(poly2, 10, 30);
    add_polynomial(poly2, -200, 10);
    add_polynomial(poly2, 20, 3);

    //cong 2 ma tran
    sum_polynomial(poly1, poly2, poly_sum);
    mul_polynomial(poly1, poly2, poly_multiphy);
    display(poly1);
    printf("\n");
    display(poly2);
    printf("\n");
    display(poly_sum);
    printf("\n");
    display(poly_multiphy);

    return 0;
}
//duyet qua cac phan tu poly 1 -> poly_sum
//Tuong tu voi cac phan tu poly 2 van hoat dong tuong tu