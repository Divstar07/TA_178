#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// declare item struct (if necessary)

// declare stack struct
typedef struct
{
    // declare the array holding items
    int *collection;
    // define the capacity of the stack
    int capacity;
    // declare a integer to represent the top of the stack
    int top;
} Stack;

// declare functions
Stack *create_stack(int capacity);

bool IsStackEmpty(Stack *stack); // check if stack is empty, if so return true

bool IsStackFull(Stack *stack); // check if stack is full, if so return true

bool push(Stack *stack, int data); // push to the top of the stack

bool pop(Stack *stack, int *data); // pop from the top of the stack and store the popped value in "data" by pass by pointer

bool popAll(Stack *stack); // pop every item from the stack

bool peek(Stack *stack, int *data); // peek at the top item in a stack without popping it, and return its value

void print_stack(Stack *stack); // print the stack

// main function
int main(void)
{
    // create a stack
    Stack *stack = create_stack(5);

    // push items to the stack until it is full
    for (int i = 0; i < stack->capacity; i++)
    {
        push(stack, i);
    }
    int value;
    peek(stack, &value);
    printf("Value at top of stack is: %d \n", value);

    // print the stack
    print_stack(stack);
    // try to push another item
    push(stack, stack->capacity + 1);

    // pop items from the stack 1 by 1
    for (int i = 0; i < stack->capacity; i++)
    {
        pop(stack, &value);
        printf("%d\n", value);
    }

    // try to pop another item
    pop(stack, &value);

    return 0;
}

// function definitions
Stack *create_stack(int capacity)
{
    //  check that the capacity parsed in is > 0
    if (capacity <= 0)
    {
        printf("Cannot create stack of capacity zero\n");
        return NULL;
    }

    //  create stack on the heap
    Stack *stack = malloc(sizeof(Stack));

    //  check if malloc failed
    if (stack == NULL)
    {
        printf("Stack creation failed...");
        return NULL;
    }

    //  allocate mememory for the collection array
    // this stack stores ints. If your stack stored an arbitrary element "item", replace the arguent of "sizeof" with item
    stack->collection = malloc(sizeof(int) * capacity);

    //  check if allocation failed
    if (stack->collection == NULL)
    {
        printf("Failed to create collection arrary of stack...");
        // if code reaches here, the stack was create successfully, but the collection array failed. We must free stack
        free(stack);
        return NULL;
    }

    //  set capacity and top of the stack
    stack->capacity = capacity;
    stack->top = -1; // this indicates that the stack is empty
}

bool IsStackEmpty(Stack *stack)
{
    return (stack->top == -1);
}

bool IsStackFull(Stack *stack)
{
    return (stack->top == stack->capacity - 1);
}

bool push(Stack *stack, int data)
{
    // check if stack is full
    if (IsStackFull(stack))
    {
        printf("Push failed, stack is full...\n");
        return false;
    }

    // insert data on the last index of the collection array
    stack->collection[stack->top + 1] = data;

    // update stack top
    stack->top++;

    return true;
}

bool pop(Stack *stack, int *data)
{
    // check if stack is empty
    if (IsStackEmpty(stack))
    {
        printf("Pop failed, stack is empty...\n");
        return false;
    }

    // store the item at the top of the stack in "data" via pass by pointer
    *data = stack->collection[stack->top];
    // decrement the top of the stack
    stack->top--;

    return true;
}

bool popAll(Stack *stack)
{
    // set the top of the stack to -1
    stack->top = -1;
    return true;
}

bool peek(Stack *stack, int *data)
{
    // check if the stack is empty
    if (IsStackEmpty(stack))
    {
        printf("Peek failed, stack is empty...\n");
        return false;
    }

    // store the value at the top of the stack in "data" via pass by pointer
    *data = stack->collection[stack->top];

    return true;
}

void print_stack(Stack *stack)
{
    for (int i = 0; i <= stack->top; i++)
    {
        printf("%d", stack->collection[i]);
        if (i != stack->top)
            printf("---->");
    }
    printf("\n");
}