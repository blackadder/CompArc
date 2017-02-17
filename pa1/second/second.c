
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int data;           //data
    struct node *next;  //pointer
};

struct node *head = NULL;
struct node *current = NULL;

void printList(){
    if(head == NULL){
      return;
    }
    else{
      struct node *ptr = head->next; //pointer that will traverse LL
      printf("%d", head->data);
      while(ptr != NULL){
        printf("\t%d", ptr->data);
        ptr = ptr -> next;
      }
   }
}

void insertAtHead(int data){
    struct node *link = ((struct node*) malloc(sizeof(struct node)));
    link -> data = data;
    link -> next = head;
    head = link;
}

void insertHere(int data){
    struct node *link = ((struct node*) malloc(sizeof(struct node)));
    link -> data = data;
    link -> next = NULL;
    struct node *ptr = head;

    if(head == NULL){
        head = link;
    }
    while(ptr != NULL){
        if(head -> data > link -> data){
            link -> next = head;
            head = link;
            return;
        }
        else if(ptr -> data == link -> data){
            return;
        }
        else if(ptr -> next == NULL){
            ptr -> next = link;
            return;
        }else if(ptr -> next -> data > link -> data){
            link -> next  = ptr -> next;
            ptr -> next = link;
        }
        else{
            ptr =  ptr -> next;
        }
    }
}

void delete(int data){
    struct node *ptr = head;
    struct node *temp = head;
    if(head == NULL){
      return;
    }
    else if(head->data == data && head->next == NULL){
      head = NULL;
    }
    while(ptr->next != NULL){
        if(ptr->data == data){
            temp = ptr;
            head = ptr -> next;
            free(temp);
            return;
        }
        else if(ptr->next->data == data){
            temp = ptr->next;
            ptr->next = ptr->next->next;
            free(temp);
            return;
        }else{
            ptr = ptr->next;
        }
    }
}

int main(int argc, char** argv)
{

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char command;
    int data;
    fp = fopen(argv[1], "r");
    if(fp == NULL){
      printf("error\n");
      return (-1);
    }
    if(argc < 2){
      return (-1);
    }
    while((read = getline(&line, &len, fp)) != -1){
	sscanf(line, "%c %d", &command, &data);
	if(command == 'i'){
	  insertHere(data);
	}else if (command == 'd'){
	  delete(data);
	}else{
	  printf("error\n");
	  return 0;
	}
    }

    printList();

    fclose(fp);

    putchar('\n');
    return 0;
}

