#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 25
#define TABLE_SIZE 10

// Define the person struct
typedef struct person
{
    char name[MAX_NAME];
    int age;
    struct person *next;
} person;

person *hash_table[TABLE_SIZE]; // stores pointers to "person" structs

unsigned int hash(char *name);          // returns index of element in the hash table
void init_hash_table();                 // initializes the hash table
void print_hash_table();                // prints elements in the hash table
bool hash_table_insert(person *person); // inserts elements into the hash table
person *hash_table_lookup(char *name);  // finds a person in the table
person *hash_table_delete(char *name);  // removes a person from the table

int main()
{
    #pragma region // "person" DECLARATIONS
    person thomas = {.name = "Thomas", .age = 18};
    person finley = {.name = "Finley", .age = 18};
    person simon = {.name = "Simon", .age = 18};
    person luke = {.name = "Luke", .age = 18};
    person mo = {.name = "Mo", .age = 18};
    person jacob = {.name = "Jacob", .age = 18};
    person jeremy = {.name = "Jeremy", .age = 18};
    person ahnaaf = {.name = "Ahnaaf", .age = 18};
    person matt = {.name = "matt", .age = 18};
    person roy = {.name = "Roy", .age = 18};
    #pragma endregion

    #pragma region // INSERT INTO HASH TABLE
    hash_table_insert(&thomas);
    hash_table_insert(&finley);
    hash_table_insert(&simon);
    hash_table_insert(&luke);
    hash_table_insert(&mo);
    hash_table_insert(&jacob);
    hash_table_insert(&jeremy);
    hash_table_insert(&ahnaaf);
    hash_table_insert(&matt);
    hash_table_insert(&roy);
    #pragma endregion

    print_hash_table();
    return 0;
}

//========================================= FUNCTION DEFINITIONS ===================================================

unsigned int hash(char name[])
{
    // hash function should generate a random result consistent for the same data, quickly
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0; // counter to accumulate the result of the hash operation

    for (int i = 0; i < length; i++)
    {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table()
{
    // initialize the hash table with NULL in all locations
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
}

void print_hash_table()
{
    // print the table
    printf("TABLE BEGINS HERE\n");

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else
        {
            printf("\t%i\t", i);
            person *temp = hash_table[i]; // declare a temporary variable

            // traverse each element
            while (temp != NULL)
            {
                printf("%s ---> ", temp->name);
                temp = temp->next;
            }
            printf("\n");
        }
    }

    printf("TABLE ENDS HERE\n");
}

bool hash_table_insert(person *person)
{
    if (person == NULL)
        return false;
    int hash_index = hash(person->name); // compute the index of the element in the hash table
    // insert the element into the hash table with external chaining
    person->next = hash_table[hash_index]; // new element points to first element in list
    hash_table[hash_index] = person;       // head of list points to new element (remember hash_table[hash_index] is a pointer!)
    return true;
}

person *hash_table_lookup(char *name)
{
    // look for an element in the first index and in subsequent linked list positions
    int hash_index = hash(name); // compute hash index
    // initialize a temp and prev pointer to traverse linked list
    person *temp = hash_table[hash_index];

    // traverse the list until temp is NULL or the element is found
    while (temp != NULL && strncmp(temp->name, name, MAX_NAME) != 0)
    {
        temp = temp->next;
    }

    // if execution reaches here and temp is NULL, the element was not found
    if (temp == NULL)
        printf("%s not found in table", name);

    return temp;
}

person *hash_table_delete(char *name)
{
    // look for an element in the first index and in subsequent linked list positions
    int hash_index = hash(name); // compute hash index
    // initialize a temp and prev pointer to traverse linked list
    person *temp = hash_table[hash_index];
    person *prev = NULL;

    // traverse the list until temp is NULL or the element is found
    while (temp != NULL && strncmp(temp->name, name, MAX_NAME) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    // if execution reaches here and temp is NULL, the element was not found
    if (temp == NULL)
    {
        printf("%s not found in table", name);
        return NULL;
    }

    // if prev is NULL at this point, execution never entered the while loop, meaning the node to delete is the head
    if (prev == NULL)
    {
        hash_table[hash_index] = temp->next;
    }

    // if neither of those conditions was met, the node is somewhere in the middle of the list, we thus redirect the previous node

    else
    {
        prev->next = temp->next;
    }

    return temp;
}
