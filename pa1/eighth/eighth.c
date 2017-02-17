#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BSTnode{
  int data;
  int height;
  struct BSTnode *Right;
  struct BSTnode *Left;
};

int height;

struct BSTnode *root = NULL;
struct BSTnode *null = NULL;

/*creates and returns new node*/
struct BSTnode* newBSTnode(int x){
  	struct BSTnode *node;
  	node = ((struct BSTnode*) malloc(sizeof(node)));

  	node->data = x;
  	node->height = 1;

  	node->Right = NULL;
  	node->Left = NULL;
  	
	return node;
}

void insert(struct BSTnode *node, int target){
  //empty tree
  if(node == null){
    root = newBSTnode(target);
    printf("inserted %d\n", root->height);
  }
  //node is equal to target
  else if(node -> data == target){
    printf("duplicate\n");
  }

  else if(node->data > target && node->Left != NULL){
    insert(node->Left, target);
  }

  else if(node->data < target && node->Right !=NULL){
    insert(node->Right, target);
  }
  //node is greater than target, and the left subtree is null, it will return
  //the node, otherwise it will keep traversing
  else if(node->data > target && node->Left == NULL){

    //consider putting a height increaser here
    node->Left = newBSTnode(target);
    node->Left->height = node->height+1;
    printf("inserted %d\n", node->Left->height);
  }

  //node is less than target, and the right subtree is null, it will return
  //the node, otherwise it will keep traversing
  else if(node -> data < target && node->Right == NULL){
    node->Right = newBSTnode(target);
    node->Right->height = node->height+1;
    printf("inserted %d\n", node->Right->height);
  }
}

void search(struct BSTnode *node, int target){
  if(node == null){
    printf("absent\n");
  }
  else if(node->data == target){
    printf("present %d\n", node->height);
  }
  else if(node->data > target && node->Left != NULL){
    search(node->Left, target);
  }
  else if(node->data < target && node->Right != NULL){
    search(node->Right, target);
  }
  else if(node->data > target && node->Left == NULL){
    printf("absent\n");
  }
  else if(node->data < target && node->Right == NULL){
    printf("absent\n");
  }
}


void dealloc(struct BSTnode *root){
  if(root != NULL){
    dealloc(root->Right);
    dealloc(root->Left);
    free(root);
  }
}

int main(int argc, char** argv){
  FILE *fp;
  fp = fopen(argv[1], "r");
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char command;
  int data;

  if(fp == NULL){
    printf("error\n");
    return 0;
  }
  if(argc < 2){
    return 0;
  }
  while((read = getline(&line, &len, fp)) != -1){
    sscanf(line, "%c %d", &command, &data);
    if(command == 'i'){
      insert(root, data);
    }else if(command == 's'){
      search(root, data);
    }else{
      printf("error\n");
      return 0;
    }
  }

  dealloc(root);
  root = NULL;

  putchar('\n');
  return 0;
}

