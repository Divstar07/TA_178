/******************************************************************************
FILENAME:   stack.cpp 
COURSE:     MREN 178
LAB:        2 

STUDENT:   [YOUR NAME HERE]         STUDENT ID: [YOUR STUDENT ID]  
PARTNER:   [PARTNER's NAME HERE]    

OTHER CONTRIBUTORS: [AS PART OF ACADEMIC INTEGRITY POLICY, ANY CONTRIBUTIONS
OBTAINED FROM ADDITIONAL SOURCES MUST BE LISTED. THESE INCLUDE WEBSITES, OTHER
STUDENTS, ETC.]
******************************************************************************/

#include <stdio.h>
#include "Stack.h"

////////////////////////////////////////////////////////////////////////////////  

void CreateStackArray(Stack stack_array[], int num_stacks){
  for (int i=0; i<num_stacks; i++) {
    Stack stack; 
    stack.top = -1; 
    stack_array[i] = stack;
  }
}

int Push(pStack stack, int timestamp, char data) {
  // initilizes item of type StampedItem
  StampedItem item = { 
    .timestamp = timestamp,
    .data = data };

  if (IsStackFull(stack)) 
    return EXIT_ERR;
  else 
    stack->stack_of_items[++stack->top] = item; 

  return EXIT_OK;
}

int Pop(pStack stack, int &timestamp, char &data) {
  if (IsStackEmpty(stack)) 
    return EXIT_ERR;
  else {
    StampedItem item = stack->stack_of_items[stack->top--];
    timestamp = item.timestamp;
    data = item.data;
  }
  return EXIT_OK;
}

bool IsStackFull (pStack stack) {
  return (stack->top == MAX_STACK_LEN - 1);  
}

bool IsStackEmpty (pStack stack) {
  return (stack->top == -1);
}

void PopAll(pStack stack) {
  /*
  int timestamp;
  char data;
  while (IsStackEmpty(stack))
    Pop(stack, timestamp, data);
  */
  //OR
  stack->top = -1; 
}

long GetTime(DS3231 rtc_clock) {
  long time[3];
  bool h12Flag = false, pmFlag = false;
  time[0] = (long) rtc_clock.getSecond();
  time[1] = (long) rtc_clock.getMinute();
  time[2] = (long) rtc_clock.getHour(h12Flag, pmFlag);
  return time[2] * 3600 + time[1] * 60 + time[0];
}
