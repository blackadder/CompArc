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

struct BSTnode *getNode(struct BSTnode *node, int target){
  if(node == null){
    return NULL;
  }
  else if(node->data == target){
    return node;
  }
  else if(node->data > target && node->Left != NULL){
    getNode(node->Left, target);
  }
  else if(node->data < target && node->Right != NULL){
    getNode(node->Right, target);
  }
  else if(node->data > target && node->Left == NULL){
    return NULL;
  }
  else if(node->data < target && node->Right == NULL){
    return NULL;
  }
}

struct BSTnode *getParent(struct BSTnode *node, int target){
    if(node == NULL){
      return NULL;
    }
    else if(node->data == target){
      return NULL;
    }
    else if(node->Right->data == target || node->Left->data == target){
      return node;
    }
    else if(node->data > target && node->Left != NULL){
      getParent(node->Left, target);
    }
    else if(node->data < target && node->Right != NULL){
      getParent(node->Right, target);
    }
    else if(node->data > target && node->Left == NULL){
      return NULL;
    }
    else if(node->data < target && node->Right == NULL){
      return NULL;
    }
  }

struct BSTnode *getSmallestRight(struct BSTnode *node){
  if(node->Right == NULL && node->Left == NULL){
    return node;
  }
  else if(node->Left == NULL){
    getSmallestRight(node->Right);
  }
  else{
    getSmallestRight(node->Left);
  }
}


void delete(int target){
  struct BSTnode *node;
  struct BSTnode *parent;
  struct BSTnode *temp;
  node = getNode(root, target);
  parent = getParent(root, target);
  
  if(node == NULL){
    printf("fail\n");
  }
  /*cases where deleted node is root*/
  else if(parent == NULL && node != NULL){
    if(node->Left == NULL && node->Right == NULL){
      root = NULL;
    }
    else if(node->Left != NULL && node->Right == NULL){
      root = node->Left;
    }
    else if(node->Left == NULL && node->Right != NULL){
      root = node->Right;
    }
    else{
      temp = getSmallestRight(node->Right);
      root->data == temp->data;
      delete(temp->data);
    }
  }
  /*All cases where deleted note has less than 2 children and is not root*/
  else if(node->Left == NULL && node->Right == NULL){
    if(parent->data > node->data){
      parent->Left = NULL;
    }
    else if(parent->data < node->data){
      parent->Right = NULL;
    }
  }
  else if(node->Left == NULL && node->Right != NULL){
    if(parent->data > node->data){
      parent->Left = node->Right;
    }
    else if(parent->data < node->data){
      parent->Right = node->Right;
    }
  }
  else if(node->Left != NULL && node->Right == NULL){
    if(parent->data > node->data){
      parent->Left = node->Left;
    }
    else if(parent->data < node->data){
      parent->Right = node->Left;
    }
  }

  /*Cases where deleted node has two children*/
  else{
    temp = getSmallestRight(node->Right);
    node->data = temp->data;
    delete(temp->data);
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
    }else if (command == 'd'){
      delete(data);
    }
    else{
      printf("error\n");
      return 0;
    }
  }

  dealloc(root);
  root = NULL;

  putchar('\n');
  return 0;
}
