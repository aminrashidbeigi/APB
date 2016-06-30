#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define MAX 30

void menu();
void addContact();
void deleteContact();
void searchContact();
void saveContacts();
void loadContacts();
void displayContacts();
void gotoxy(int, int);
void addContactAfterWantedContactName();
void addContactAfterWantedContactPhonenumber();

struct contact{
    char name[MAX];
    char phoneNumber[MAX];
    struct contact *nextContact;
}*first, *temp;

int main(){
    menu();
    while(1){
        switch(getch()){
            case '1' :
                printf("Enter the type of add: \n");
                printf("1. Add at the end of list.\n");
                printf("2. Add after an arbitrary contact's name\n");
                printf("3. Add after an arbitrary contact's phoneNumber\n");
                switch(getch()){
                    case '1' : addContact(); break;
                    case '2' : addContactAfterWantedContactName(); break;
                    case '3' : addContactAfterWantedContactPhonenumber(); break;
                }
            break;
            case '2' : deleteContact(); break;
            case '3' : searchContact(); break;
            case '4' : saveContacts(); break;
            case '5' : loadContacts(); break;
            case '6' : displayContacts(); break;
            case '7' : exit(1);
        }
        system("cls");
        menu();
    }
    getch();
    return 0;
}

void menu(){
    system("cls");
    system("color 5f");
    gotoxy(28,0);
    printf("WELCOME TO PHONEBOOK");
    gotoxy(35,2);
    printf("MENU");
    gotoxy(10,4);
    printf("1. Add New Contact");
    gotoxy(30,4);
    printf("2. Delete a Contact");
    gotoxy(50,4);
    printf("3. Search a Contact");
    gotoxy(10,5);
    printf("4. Save Contacts");
    gotoxy(30,5);
    printf("5. Load Contacts");
    gotoxy(50,5);
    printf("6. Display Contacts");
    gotoxy(34,7);
    printf("7. EXIT");
    printf("\n");
}

void addContact() {
    struct contact *last;
    temp = (struct contact *) malloc(sizeof(struct contact));
    printf("Name: ");
    gets(temp -> name);
    printf("Phone Number: ");
    gets(temp -> phoneNumber);
    temp -> nextContact = NULL;
    if(first == NULL) first = temp;
    else {
        last = first;
        while (last->nextContact != NULL) last = last->nextContact;
        last->nextContact = temp;
    }
    printf("%s added to contacts :)\nPress any key to continue",temp -> name);
    getch();
}

void addContactAfterWantedContactName() {
    struct contact *last=first, *next;
    int addedFlag = 0;
    char name[MAX];
    temp = (struct contact *) malloc(sizeof(struct contact));
    printf("Name: ");
    gets(temp -> name);
    printf("Phone Number: ");
    gets(temp -> phoneNumber);
    printf("Enter wanted contact: ");
    gets(name);
    while (last != NULL) {
        if (strcmp(name, last->name) == 0) {
            // Should Add Contact
            next = last->nextContact;
            last->nextContact = temp;
            temp->nextContact = next;
            addedFlag = 1;
            break;
        }
        last = last->nextContact;
    }
    if (addedFlag == 1) printf("%s added after %s :)\nPress any key to continue", temp->name, name);
    else printf("%s wasn't found in the contacts' list :(\nPress any key to continue", name);
    getch();
}

void addContactAfterWantedContactPhonenumber() {
    struct contact *last=first, *next;
    int addedFlag = 0;
    char number[MAX];
    temp = (struct contact *) malloc(sizeof(struct contact));
    printf("Name: ");
    gets(temp -> name);
    printf("Phone Number: ");
    gets(temp -> phoneNumber);
    printf("Enter number of wanted contact: ");
    gets(number);
    while (last != NULL) {
        if (strcmp(number, last->phoneNumber) == 0) {
            // Should Add Contact
            next = last->nextContact;
            last->nextContact = temp;
            temp->nextContact = next;
            addedFlag = 1;
            break;
        }
        last = last->nextContact;
    }
    if (addedFlag == 1) printf("%s added after %s :)\nPress any key to continue", temp->name, number);
    else printf("%s wasn't found in the contacts' list :(\nPress any key to continue", temp->name);
    getch();
}

void deleteContact(){
    struct contact *ptr,*prev, *last;
    char wantedContact[MAX];
    printf("Name to Delete : ");
    gets(wantedContact);
    prev = ptr = first;
    while(strcmp(ptr -> name , wantedContact)!= 0){
        prev = ptr;
        ptr = ptr -> nextContact;
        if (ptr == NULL) break;
    }
    if(ptr != NULL){
        if (ptr == first) {
            last = first -> nextContact;
            free(first);
            first=last;
        }
        else{
            last = ptr -> nextContact;
            free(ptr);
            prev -> nextContact = last;
        }
        printf("%s deleted from the list :(\n", wantedContact);
    }
    else {
        printf("\nNo matching records found :(\n");
    }
    getch();
}

void searchContact(){
    struct contact *last;
    char wantedContact[MAX];
    int resultFlag = 0;
    printf("Enter type of search:\n(1)Name\n(2)phoneNumber\n");
    switch(getch()){
    case '1':
        printf("Name to search:\n");
        gets(wantedContact);
        last = first;
        while (last != NULL) {
            if (strcmp(wantedContact, last->name) == 0) {
                printf("%s's number: %s\nPress any key to continue\n", wantedContact, last->phoneNumber);
                resultFlag = 1;
                break;
            }
            last = last->nextContact;
        }
        if (resultFlag !=1 ) printf("%s wasn't found in the contacts' list :(\nPress any key to continue\n", wantedContact);
        break;
    case '2':
        printf("Number to search:");
        gets(wantedContact);
        last = first;
        while (last != NULL) {
            if (strcmp(wantedContact, last->phoneNumber) == 0) {
                printf("%s's name: %s\nPress any key to continue\n", wantedContact, last->name);
                resultFlag = 1;
                break;
            }
            last = last->nextContact;
        }
        if (resultFlag !=1 ) printf("%s wasn't found in the contacts' list :(\n\nPress any key to continue\n", wantedContact);
    }
    getch();
}

void saveContacts(){
    FILE *fptr = fopen("phonebook.txt", "w+");
    temp = first;
    if (fptr != NULL) {
        while(temp != NULL){
            fprintf(fptr, "name: %s\n", temp -> name);
            fprintf(fptr, "Phone Number: %s\n", temp -> phoneNumber);
            temp = temp -> nextContact;
        }
        fclose(fptr);
    }
    printf("Contacts Saved :)\nPress any key to continue\n");
    getch();
    return 0;
}

void loadContacts(){
    FILE *fptr = fopen("phonebook.txt", "r+");
    if(!fptr){
        printf("Can not open the file...:( \nPress any key to continue\n");
        getch();
        return 0;
    }
    first = temp = (struct contact *) malloc(sizeof(struct contact));
    while(!feof(fptr)) {
        fscanf(fptr, "name: %s\n", temp -> name);
        fscanf(fptr, "Phone Number: %s\n", temp -> phoneNumber);
        if (!feof(fptr)) {
            temp -> nextContact = temp = (struct contact *) malloc(sizeof(struct contact));
        } else {
            temp -> nextContact = NULL;
        }
    }
    printf("Contacts loaded :)\nPress any key to continue\n");
    fclose(fptr);
    getch();
    return 0;
}

void displayContacts(){
    struct contact *ptr;
    if(first == NULL){
        printf("Telephone Directory is Empty\nPress any key to continue\n");
        getch();
        return;
    }
    printf("\t\t\t------------------------------\n");
    for(ptr = first; ptr != NULL; ptr = ptr -> nextContact) {
        printf("\t\t\tFirst name:    %s", ptr -> name);
        printf("\n\t\t\tTelephone No.: %s", ptr -> phoneNumber);
        printf("\n\t\t\t------------------------------\n");
    }
    printf("\nPress any key to continue\n");
    getch();
}

void gotoxy(int x,int y){
    COORD pos;
    HANDLE hConsole = GetStdHandle ( STD_OUTPUT_HANDLE );
    if(INVALID_HANDLE_VALUE != hConsole){
        pos.X = x;
        pos.Y = y;
        SetConsoleCursorPosition( hConsole, pos );
    }
}
