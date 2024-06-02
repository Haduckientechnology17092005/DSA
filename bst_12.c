#include <stdio.h>
#include <stdlib.h>

struct TreeNodeRecord {
	int key;
	struct TreeNodeRecord *left;
	struct TreeNodeRecord *right;
	struct TreeNodeRecord *parent;
};

typedef struct TreeNodeRecord *BST;
typedef struct TreeNodeRecord *TreeNode;

BST create_bst() {
	BST T = malloc(sizeof(struct TreeNodeRecord));
	if (T == NULL) {
		printf("Not enough memory!\n");
		return NULL;
	}
}

void preoder_travesal(BST T) {
	if (T!=NULL) {
		printf("%d ",T->key);
		preoder_travesal(T->left);
		preoder_travesal(T->right);
	}
}

void inoder_travesal(BST T) {
	if (T!=NULL) {
		inoder_travesal(T->left);
		printf("%d ",T->key);
		inoder_travesal(T->right);
	}
}

void postoder_travesal(BST T) {
	if (T!=NULL) {
		postoder_travesal(T->left);
		postoder_travesal(T->right);
		printf("%d ",T->key);
	}
}

TreeNode tree_search(BST T, int key) {
	if (T == NULL || T->key == key) 
		return T;
	else {
		if (T->key>key)
			return tree_search(T->left,key);
		else
			return tree_search(T->right,key);
	}
}

TreeNode tree_minimum(BST T) {
	if (T == NULL) {
		printf("The tree is empty!\n");
		return NULL;
	}
	while (T->left!=NULL)
		T = T->left;
	return T;
}

TreeNode tree_maximum(BST T) {
	if (T == NULL) {
		printf("The tree is empty!\n");
		return NULL;
	}
	while (T->right!=NULL)
		T = T->right;
	return T;
}

TreeNode tree_successor(TreeNode x) {
	if (x == NULL)
		return NULL;
	if (x->right!=NULL)
		return tree_minimum(x->right);
	TreeNode y = x->parent;
	while (y!=NULL && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

void tree_insert(BST *T,int key) {
	TreeNode newNode = malloc(sizeof(struct TreeNodeRecord));
	if (newNode==NULL){
		printf("\nNot enough memory!");
		return NULL;
	}
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;
	TreeNode x,y;
	y = NULL;
	x = *T;
	while (x!=NULL) {
		y = x;
		if (newNode->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	newNode->parent = y;
	if (y==NULL)
		*T = newNode;
	else if (newNode->key<y->key)
		y->left = newNode;
	else
		y->right = newNode;
}

TreeNode tree_predecessor(TreeNode x) {
	if (x == NULL)
		return NULL;
	if (x->left!=NULL)
		return tree_maximum(x->left);
	TreeNode y = x->parent;
	while (y!=NULL && x == y->left) {
		x = y;
		y = y->parent;
	}
	return y;
}

void tree_delete(BST *T,TreeNode z) {
	TreeNode x, y;
	if (z->left==NULL || z->right==NULL)
		y = z;
	else
		y = tree_successor(z);
	if (y->left!=NULL)
		x = y->left;
	else
		x = y->right;
	if (x!=NULL)
		x->parent = y->parent;
	if (y->parent==NULL)
		*T = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	if (y!=z)
		z->key = y->key;
	free(y);
}

int main() {
	BST T = NULL;
	int tree_data[] = {6,3,9,2,5,4,8};
	for (int i=0;i<sizeof(tree_data)/sizeof(tree_data[0]);i++)
		tree_insert(&T,tree_data[i]);
	printf("Preorder traversal: ");
	preoder_travesal(T);
	printf("\nInorder traversal: ");
	inoder_travesal(T);
	printf("\nPostorder traversal: ");
	postoder_travesal(T);
	
	TreeNode x;
	x = tree_search(T,5);
	if (x!=NULL)
		printf("\n%d found!",x->key);
	else
		printf("\nNot found!");
	TreeNode min,max;
	min = tree_minimum(T);
	printf("\nMin = %d",min->key);
	max = tree_maximum(T);
	printf("\nMax = %d",max->key);
	
	TreeNode successor, predecessor;
	x = tree_search(T,2);
	successor = tree_successor(x);
	if (successor!=NULL)
		printf("\nSuccessor of %d is %d",x->key,successor->key);
	else
		printf("\nNode %d does not have a successor!");
	predecessor = tree_predecessor(x);
	if (predecessor!=NULL)
		printf("\nPredecessor of %d is %d",x->key,predecessor->key);
	else
		printf("\nNode %d does not have a predecessor!", x->key);	
	
	x = tree_search(T,6);
	tree_delete(&T,x);
	printf("\nPreorder traversal: ");
	preoder_travesal(T);
	
	return 0;
}