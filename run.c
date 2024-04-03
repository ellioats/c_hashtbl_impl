// Elliot Currie
// Student Number: 991644153
// Date: April 2nd, 2024
// Assignment 4 - C and Data Structures

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 13
#define Empty 0

/* Structure Definition*/
typedef struct node {
    int num;
    struct node *next;
} Node, *NodePtr;


/* Function Prototypes */
NodePtr newNode (int n);
void printList(NodePtr);
int hashTableInsert(NodePtr index[N], int key);
void menu();

// main function
int main() {

    // variables
    int i, key, userChoice, index, numOfUniqueEntries = 0;
    FILE *in = fopen("input.txt", "r");
    NodePtr hash[N];

    // user input
    char input[3];
    char * STRTOL_TEST;

    // sets all values inside hashtable to null
    for (i = 0; i < N; i++) {
        hash[i] = NULL;
    }


    puts("prep done :)");


    while(true) {
        menu();
        do {
            printf("Choice: ");
            fgets(input, 3, stdin);
            // printf("\nSTRING input read as: %s\n", input);
            // printf("\nLONG input read as: %i\n", userChoice);

            userChoice = strtol(input, &STRTOL_TEST, 10);

        } while(STRTOL_TEST != NULL && STRTOL_TEST[0] != '\n');        

        switch(userChoice) {
            case 1: // insert new value
                
                puts("inserting values from file...");
                while(fscanf(in, "%d", &key) == 1) {
                    
                    // printf("DEBUG: inserting %d into table at position %i\n", key, index);
                    numOfUniqueEntries += hashTableInsert(hash, key);
                    // puts("end of itr");

                    
                }
                printf("%i unique entries...\n", numOfUniqueEntries);

                break;
            case 2: // print list 
            puts("printing list...");

                for (i = 0; i < N; i++) {
                    if (hash[i] == NULL) {
                        printf("index %i is empty...\n", i);
                        continue;
                    }
                    printf("Hash[%d]->", i);
                    printList(hash[i]);
                }
                break;
            case 3: 
                puts("Exiting, goodbye :)");
                exit(0);
                break;
            default: 
                puts("Invalid input, please try again...");
        }
    }


    return 0;
}


// creates new node
NodePtr newNode (int n){
    NodePtr p = (NodePtr)malloc(sizeof(Node));
    p->num = n;
    p->next = NULL;
    return p;
}

// prints all elements inside a single element of the hash[]
void printList(NodePtr front){
    if (front == NULL) {
        puts("List is empty");
        return;
    }
    while(front != NULL){
        printf("%2d->", front->num);
        front = front->next;
    }
    printf("\n");
}


/* 

Insert into hashtable

*/
int hashTableInsert(NodePtr index[N], int key)
{

    int element = ((2*key)+5)%N;

    NodePtr current = index[element];
    NodePtr previous = NULL;


    while (current != NULL) {
        if (current->num == key) {
            // puts("same key found, returning...");
            // puts("\tHASHTABLEINSERT exited...");
            return 0;
        }
            
        previous = current;
        current = current->next;
    }

    NodePtr temp = newNode(key);

    if (previous == NULL) {
        index[element] = temp;
    } else {
        previous->next = temp;
    }

    return 1;
  
}


/* 

prints menu for user to interact with program

*/
void menu() {
    puts("\n1: Append new value into hash table");
    puts("2: Print hash table");
    puts("3: Exit Program");
}