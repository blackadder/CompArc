#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10000

struct hash *hashTable = NULL;

struct node{
  int key;
  struct node *next;
};

struct hash{
  int key;
  struct node *head;
};

struct node *getNode(int key){
  struct node *newNode;
  newNode = (struct node*) malloc(sizeof(struct node));
  newNode -> key = key;
  newNode -> next = NULL;
  return newNode;
}

void insert(int key){
  int hashIndex = key % SIZE, flag = 0;
  struct node *newNode = getNode(key);
  struct node *temp = hashTable[hashIndex].head;
  
  /*Looks to see if the new key to be inserted is a duplicate*/
  while(temp != NULL){
    if(temp->key == key){
      flag = 1;
    }
    temp = temp->next;
  }
  
  if(flag == 1){
    printf("duplicate\n");
  }else{
    printf("inserted\n");
  }

  /*creates head of LL at this index, if none already exist*/
  if(!hashTable[hashIndex].head){
    hashTable[hashIndex].head = newNode;
    return;
  }
  
  newNode->next = (hashTable[hashIndex].head);
  hashTable[hashIndex].head = newNode;
}

void search(int key){
  int hashIndex = key % SIZE, flag = 0;
  struct node *temp;
    
  temp = hashTable[hashIndex].head;
    
  if(!temp){
    printf("absent\n");
    return;
  }
  while(temp != NULL){
    if(temp->key == key){
      printf("present\n");
      return;
    }
    temp = temp-> next;
  }
  printf("absent\n");
  return;
}

int main(int argc, char** argv){
    int key;
    
    FILE *fp;
    fp = fopen(argv[1], "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char command;
    
    hashTable = (struct hash*) calloc(SIZE, sizeof(struct hash));
    
    if(fp == NULL){
      printf("error\n");
      return 0;
    }
    if(argc < 2){
      return 0;
    }
    while((read = getline(&line, &len, fp)) != -1){
      sscanf(line, "%c %d", &command, &key);
      if(command == 'i'){
	insert(key);
      }else if(command == 's'){
	search(key);
      }else{
	printf("error\n");
      }
    }
    fclose(fp);
    return 0;
}
