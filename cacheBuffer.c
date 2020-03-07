#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#define L 20
//#define T 10
#define SIZE 20

typedef struct link {
	int counter;            // Counting how much time, the owner website called.
	char data[SIZE];        // Data of website(website name)
	struct link * next;     // A pointer reffering next website. 
	struct link * prev;	   // A pointer reffering previous website
}node;

node * firstInsert(char data[] , node * head){      // firstInster function is creating the very first website entered.
                                                    // I seperate it from insert function because, very first node has some unique differences.
	node * first_website;
	first_website = (node *)malloc(sizeof(node));
	strcpy((first_website -> data) , data);	
	first_website -> next = NULL;
	first_website -> prev = NULL;
	first_website -> counter = 0;
	head = first_website;
	return head;
}

node * pullToTop(node * current , node * head, node * lastnode){    // pullToTop function is pulling the node which reached the threshold value.
	if (current == head){	            // Controlling different cases with this if statament.
		head = current;
	}
	else if(current == lastnode){               // this statament stands for, if the pulling node is lastone.
		head -> prev = current;
		current -> prev -> next = NULL;
		current -> prev = NULL;
		current -> next = head;
		head = current;
		
	}
	else{											// Pulling node is not head it is not lastnode also. 
		current -> prev -> next = current -> next;
		current -> next -> prev = current -> prev;
		head -> prev = current;
		current -> next = head;
		current -> prev = NULL;
		head = current;	
	}
	return current;
}

node * search(char data[] , node * head){              // This function searching for, if the input website has already exist.
	node * iter = head;									    // An iterator to jump between nodes.
	while((strcmp(data , iter -> data) != 0) && (iter -> next != NULL)){	
		iter = iter -> next;
	} 
	return iter;							            
}

node * insert(char data[] , node * head){       // This insert function is basically creating new nodes.
	
	node * new_website;
	new_website = (node *)malloc(sizeof(node));
	strcpy((new_website -> data) , data);
	new_website -> next = head;
	new_website -> prev = NULL;
    new_website -> counter = 1;
	head -> prev = new_website;                      
	head = new_website;
	return head;
	
}

node * deleteLast(node * lastnode){       // This deleteLast function is deleting the lastnode in our list. So that we can use its space.
	                                       // Controlling mechanism between length of list and the L value.
	lastnode -> prev -> next = NULL ;
	lastnode = lastnode -> prev ;
	return lastnode;

}

void clearscreen(){ //This function clears the screen for Windows. You can modify for your OS.
	system("cls");
}

int main(){
	int toStart,length = 0,i = 0,j = 0,L = 0,T = 0;         // toStart is used for separating File mod - Consol mod
	char data[SIZE],toData[SIZE],temp[1],filename[SIZE];    // toData is used for transferring the string from file to 'data' without '\n' character
	printf("\nTo read from file press 1 ; For using consol and giving inputs manually press 2 : ");
	scanf("%d",&toStart);
	if(toStart == 1){
		
		printf("Buffer's length :");
		scanf("%d",&L);
		printf("Maximum count number to take a node, pull to head (threshold value) :");
		scanf("%d",&T);
		
		node * head = NULL;                                // * Initializing nodes.
		node * current = NULL;                             // *
		node * lastnode = NULL;	                           // *
		node * reader = NULL;                              // *
		
		printf("Enter file's name :");
		scanf("%s",filename);
		
		FILE *fp;
		fp = fopen(filename,"r"); 
		if(fp == NULL){
			perror("Unable to open file!");
			exit(1);
		}
		else{
			while(fgets(toData,sizeof(toData),fp) != NULL){
				i = strlen(toData);                 // * I tried to avoid from bugs that may appear if the 'fgets' function takes '\n' character.
				if(toData[i-1] == '\n')             // *
					toData[i-1] = '\0';              // *
				printf("\n");			               // *
				strcpy(data,toData);                // *
			
				if(length == 0){                    // We need this part for the very first node only.
					head = firstInsert(data,head);   // Creating first node.
					length = length + 1;            
					lastnode = head;                 // And head node is also lastnode now because it is the only one.
				}
				if(strcmp(search(data,head) -> data , data) != 0){  // Searching if the input website already exist.
					if(L == length){                                 // We are creating the input website so we need to be sure that we have space.
						lastnode = deleteLast(lastnode); 
						head = insert(data,head);
					}
					else{
						head = insert(data,head);
						length = length + 1;
					}
				}
				else{
					current = search(data,head);                   // Input website found in the list.
					if ((current -> counter) >= T){                // Controlling if the found website reach T value.
						(current -> counter) = (current -> counter) + 1;
						if(length != 1){
							if(current != lastnode){
								head = pullToTop(current,head,lastnode);
							}
							else{
								lastnode = lastnode -> prev;
								head = pullToTop(current,head,lastnode->next);
							}
						}
						else{
							head = pullToTop(current,head,lastnode);
						}
					}
					else{
						(current -> counter) = (current -> counter) + 1;
					}
				}
			
				reader = head;
				while(reader != NULL){                   // Printing the list.
					printf("  %s , %d ",reader->data,reader->counter);
					reader = reader->next;
				}
			}
		}
		fclose(fp);
		while(head -> next != NULL){            // Clearing the list.
				head = head -> next;
				free(head -> prev);
			}
			free(head);
	}
	else{
		clearscreen();
		printf("Below there are some infos to use this program correctly.\n\n-Program starts after taking buffer's length and threshold value.");
		printf("\n-You can type whenever you want 'gotomenu' to go menu and create a new buffer or exit program.");
		printf("\n-You can type whenever you want 'exitprogram' to exit program.");
		printf("\n-!These keywords will not appear again while programming running.");
		printf("\n-So be sure that everything is clear and then type anything.");
		scanf("%s",temp);
		clearscreen();
		while(strcmp("exitprogram" , data) != 0){
			length = 0;
			printf("Buffer's length :");
			scanf("%d",&L);
			printf("Maximum count number to take a node, pull to head (threshold value) :");
			scanf("%d",&T);
	
			node * head = NULL;                                // * Initializing nodes.
			node * current = NULL;                             // *
			node * lastnode = NULL;	                           // *
			node * reader = NULL;                              // *
	
	
			printf("Type a website :");
			printf("\n");
			scanf("%s",data);
			if((strcmp("exitprogram" , data) != 0) && (strcmp("gotomenu" , data) != 0)){      
				head = firstInsert(data,head);
				length = length + 1;
				lastnode = head;
			}	
			while((strcmp("exitprogram" , data) != 0) && (strcmp("gotomenu" , data) != 0)){
				if(strcmp(search(data,head) -> data , data) != 0){
					if(L == length){
						lastnode = deleteLast(lastnode); 
						head = insert(data,head);
					}
					else{
						head = insert(data,head);
						length = length + 1;
					}
				}
				else{
					current = search(data,head);
					if ((current -> counter) >= T){
						(current -> counter) = (current -> counter) + 1;
						if(length != 1){
							if(current != lastnode){                           // We have special cases while trying to pull the node depends where it is.
								head = pullToTop(current,head,lastnode);
							}
							else{
								lastnode = lastnode -> prev;
								head = pullToTop(current,head,lastnode->next);
							}
						}
						else{
							head = pullToTop(current,head,lastnode);
						}
					}
					else{
						(current -> counter) = (current -> counter) + 1;
					}
				}
			
			reader = head;
			while(reader != NULL){
				printf("  %s , %d ",reader->data,reader->counter);
				reader = reader->next;
			}
			printf("\nType a website :");
			printf("\n");
			scanf("%s",data);
			}
		
		if((strcmp("gotomenu" , data) == 0)){
			printf("For exit type 'exitprogram'. For starting a new buffer type 'again'. ");
			scanf("%s",data);
			
			if(head != NULL){
				while(head -> next != NULL){
					head = head -> next;
					free(head -> prev);
				}
			free(head);
			}
		}
		}
	}
	return 0;
}
