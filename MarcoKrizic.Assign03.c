#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define size 80 

//TYPE DECLARATION
//Creating item entries
typedef struct entry {
	int id; //the registered entry's ID number for searching and updating purposes
	char name[size]; //the registered entry's name (what kind of products)
	int quantity; //the registered amount of the entry items on hand
	struct entry *next; //the next entry in the linked list
} Entry, *EntryPtr;	//declarations of entry object and pointer to said object


//METHOD DECLARATION
//This method adds a new item into the inventory
void insertEntry(EntryPtr *randomPtr, int idInput, char nameInput[size], int quantityInput) {
	
	EntryPtr newPtr; //new inventory entry
	EntryPtr previousPtr; //pointer to previous entry
 	EntryPtr currentPtr; //pointer to current entry in inventory
	newPtr = malloc(sizeof( Entry ) ); //initialize allocated memory for new inventory entry

	if(newPtr != NULL ) { 
 		newPtr->id = idInput; 
 		strcpy(newPtr->name, nameInput);
 		newPtr->quantity = quantityInput;
 		newPtr->next = NULL; 
		previousPtr = NULL;
		currentPtr = *randomPtr;

		//loop to find the correct location in inventory
		while(currentPtr != NULL && idInput > currentPtr->id ) {
 			previousPtr = currentPtr; 
 			currentPtr = currentPtr->next; 
		} //end nested while

		//insert new entry at beginning of list
 		if(previousPtr == NULL) {
 			newPtr->next = *randomPtr;
			 *randomPtr = newPtr;
 		} //end nested if	
 		else { //insert new entry between previousPtr and currentPtr
 			previousPtr->next = newPtr;
 			newPtr->next = currentPtr;
 		} //end nested else
 	} //end if
 	
 	else {
 		printf( "The entry has not been inserted. No memory available.\n");
 	} //end of else
	
} //end of method

//This method searches for the data of a stored item in the inventory based on user input
void searchEntry(EntryPtr *randomPtr, int findId) {

	EntryPtr currentPtr; //Initializing pointer for selected inventory entry		
	currentPtr = *randomPtr; //Assign initialized entry pointer
		
	while (currentPtr != NULL && currentPtr->id != findId) {
		currentPtr = currentPtr->next;
		if (currentPtr == NULL) {
			printf("\nThe value you are looking for does not exist.");
		} //end of nested if
	} //end of while loop
	
	if (currentPtr->id == findId) {
		printf("\nID\t\t\t\tName\t\t\t\tQuantity\n");
		printf( "\n%d				%s	  			%d", currentPtr->id, currentPtr->name, currentPtr->quantity);
	} //end if
	
} //end of method

//This method updates the quantity of an item in the inventory selected via user input
void updateEntry(EntryPtr *randomPtr, int chId, int chQuantity) {
	
	EntryPtr currentPtr; //Initializing pointer for selected inventory entry
	currentPtr = *randomPtr; //Assign initialized entry pointer
	
	while (currentPtr != NULL && currentPtr->id != chId) {
		currentPtr = currentPtr->next;
		if (currentPtr == NULL) {
			printf("\nThe value you are looking to update does not exist.");
		} //end of nested if
	} //end of while
	
	if (currentPtr->id == chId) {
		currentPtr->quantity = chQuantity;
	} //end of if
	
} //end of method

//This method checks if the inventory is empty (aka NULL)
int isEmpty(EntryPtr randomPtr) {
	return randomPtr == NULL;	
}

//This method prints all the items currently registered in the inventory
void printList(EntryPtr currentPtr) {

 	if(isEmpty(currentPtr)) {
 		printf( "There are no current items registered.\n\n" );
 	} // end if
 	
 	else {
 		printf( "Warehouse Inventory System\n" );
 		printf("\n-----------------------------------------");
 		printf("\nID\t\t\t\tName\t\t\t\tQuantity\n");

 	/* while not the end of the list */
		while(currentPtr != NULL ) {
 			printf("\n%d				%s	  			%d", currentPtr->id, currentPtr->name, currentPtr->quantity);
 			currentPtr = currentPtr->next;
 		} //end of while
 	} //end else
 	
}

//This method prints all the instructions for the menu selection screen 
void printMenu( void ) {
	printf("Input one of the following numbers as listed below:");
	printf("\n1) Add a new entry to the inventory");
	printf("\n2) Search the inventory for an entry");
	printf("\n3) Change the quantity of an entry");
	printf("\n4) Display all entries in the inventory");
	printf("\n5) Exit the program");
}

//MAIN METHOD OF PROGRAM
int main(int argc, char *argv[]) {

	EntryPtr inventory = NULL;
	
	//Configuring User Inputs
	//for main menu
	int option;
	
	//for option 1
	int inputId;	
	char inputName[size];
	int inputQuantity;
	
	//for option 2
	int searchId;
	
	//for option 3
	int changeId;
	int changeQuantity;
	
	//options 4 and 5 do not require specified inputs
	
	
	printf("Hello and welcome!");
	printf("\n");
	printf("\nThis program will serve as a makeshift inventory system.");
	printf("\n\n");
	
	printMenu();
	printf("\n\nType in a number from 1-5:");
	scanf("%d", &option);
	
	while (option != 5) {
		
		switch(option) {
			
			case 1:
				printf("\n");
				printf("\nEnter the ID number of your new entry:");
				scanf("%d", &inputId);
				printf("\nEnter the name of your new entry:");
				scanf("%s", inputName);
				printf("\nEnter the quantity of your new entry on hand:");
				scanf("%d", &inputQuantity);
				insertEntry(&inventory, inputId, inputName, inputQuantity);
				break;
				
			case 2:
				printf("\n");
				printf("\nEnter the ID of the item you are looking for:");
				scanf("%d", &searchId);
				
				if (isEmpty(inventory)) {
					printf("\n\nThere are no values available to search from.");
				}
				else {
					searchEntry(&inventory, searchId);	
				}
				break;
			
			case 3:
				printf("\n");
				printf("\nEnter the ID of the item you are looking for:");
				scanf("%d", &changeId);
				printf("\nEnter the current quantity of the item on hand:");
				scanf("%d", &changeQuantity);
				
				if (isEmpty(inventory)) {
					printf("\n\nThere are no values available to search from.");
				}
				else {
					updateEntry(&inventory, changeId, changeQuantity);	
				}
				break;
				
			case 4:
				printf("\n");
				printList(inventory);
				printf("\n");
				break;
			
			case 5:
				exit(0);
				break;
				
			default:
				printf("\n\nThe value you entered was invalid. Please try again by inputting any value from 1 through 5. \n\n");
				printMenu();
				break;
				
		} //end of switch
		
		
		printf("\n\nType in a number from 1-5:");
		scanf("%d", &option);
		
	} //end of while loop
	
	return 0;
} //end of main
