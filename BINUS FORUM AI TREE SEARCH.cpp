#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tree{
	int value;
	int height;
	struct tree *left;
	struct tree *right;
}*root=NULL;

int max(int a,int b)
{
    return a > b ? a : b;
}

int height(struct tree *leaf)
{
	if(leaf==NULL)return 0;	
	return leaf->height;
}

int balancfactor(struct tree *leaf)
{
	if(leaf==NULL)return 0;
    return height(leaf->left)-height(leaf->right);
	
}

void heightupdate(struct tree *leaf)
{
    if(leaf!=NULL)
        leaf->height=max(height(leaf->left),height(leaf->right))+1;
}

struct tree *newLeaf(int value)
{
    struct tree *ret =(struct tree*)malloc(sizeof(struct tree));
    ret->value=value;
    ret->height=1;
    ret->right=ret->left=NULL;

    return ret;
}

struct tree *rRotate(struct tree *root)
{
    struct tree *ret = root -> left;
    struct tree *temp = ret -> right;

    ret -> right = root;
    root -> left = temp;

	heightupdate(root);
    heightupdate(ret);
    return ret;
}

struct tree *lRotate(struct tree *root)
{
    struct tree *ret = root -> right;
    struct tree *temp = ret -> left;

    ret -> left = root;
    root -> right = temp;
    
    heightupdate(root);
    heightupdate(ret);
    return ret;
}

struct tree *balance(struct tree *leaf)
{
    int bal = balancfactor(leaf);
    if(bal > 1)
    {
        if(balancfactor(leaf -> left) < 0)
            leaf -> left = lRotate(leaf -> left);
        leaf = rRotate(leaf);
    }
    else if(bal<-1)
    {
        if(balancfactor(leaf->right)> 0)
            leaf->right=rRotate(leaf->right);
        leaf=lRotate(leaf);
    }

    return leaf;
}

struct tree *insert(struct tree *root, int value)
{
    if(root==NULL)
        return newLeaf(value);
    else if(root->value<value)
        root->right=insert(root->right,value);
    else
        root->left=insert(root->left,value);

    heightupdate(root);
    return root = balance(root);
}

struct tree *search(struct tree *root,int value){
	if(root==NULL){
		printf("%d NOT FOUND\n\n",value);
		return NULL;
	}
	
	if(value<root->value)
		root->left=search(root->left,value);
	else if(value>root->value)
		root->right=search(root->right,value);
	else if(value==root->value)
		printf("%d FOUND\n",root->value);
	
	return root;
}

void preorder(struct tree *root)
{
    if(root!=NULL)
    {
        preorder(root->left);
        printf("%d ",root->value);
        preorder(root->right);
    }
}

int main(){
	root = insert(root, 10);
	root = insert(root, 30);
	root = insert(root, 50);
	root = insert(root, 100);
	root = insert(root, 120);
	
	preorder(root);
	
	printf("\n");
	root = search(root, 100);
	root = search(root, 54);
}


