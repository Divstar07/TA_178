#include "queue.h"

pQueue CreateQueue (void) {
  pQueue pnew = (pQueue)malloc(sizeof (struct queue));
  if (pnew != NULL) {
    pnew->front = NULL;
    pnew->back =  NULL;
    pnew->count = 0;
  }
  return pnew;
}

int CreateQueueArray(pQueue queue_array[], int num_queues){
  for (int i=0; i<num_queues; i++) {
    queue_array[i] = CreateQueue();
    if (queue_array[i] == NULL) {
      //fprintf (stderr, "ERROR: Failed to create queue %d\n", i);
      Serial.print("ERROR: Failed to create queue ");
      Serial.print(i);
      Serial.println(".");
      return EXIT_ERR;
    }
  }
  return EXIT_OK;
}

// Code to create new item and initialize value field
pStampedItem CreateItem (int timestamp) {
	pStampedItem pnew = (pStampedItem) malloc(sizeof(StampedItem));
	if (pnew != NULL)	{
		pnew->timestamp = timestamp;
    pnew->next = NULL;
	} else {
    //fprintf (stderr, "ERROR: Failed to create queue %d\n", i);
    Serial.print("ERROR: Failed to create new item ");
    Serial.print(timestamp);
    Serial.println(".");
  }
	return pnew;
}

bool IsQEmpty (pQueue queue) {
    return (queue->count == 0);
}

int Enqueue (pQueue queue, pStampedItem item) {
	if (item != NULL && queue != NULL) {
		// Make current last node point to new node
		if (queue->back != NULL) {
		  queue->back->next = item;   
		}
    // and update queue's back pointer
    queue->back = item;
    
		// If queue was empty, new node is also new front node
		if (IsQEmpty (queue))	queue->front = item;
		// In any event, count is increased
		queue->count++;
	} else {
    Serial.println("ERROR: Failed to enqueue new item because item and/or queue is NULL.");
    return EXIT_ERR;
	}
  return EXIT_OK;
}

int Dequeue (pQueue queue, int &timestamp) {
  if (queue == NULL) {
    Serial.println("ERROR: Failed to dequeue item because queue is NULL.");
    return EXIT_ERR;
  }
  // Check if there is anything to remove
  else if (!IsQEmpty(queue)) {
		// There is data to remove
		StampedItem *p_item = queue->front;   // pointer to first element
		timestamp = p_item->timestamp;			  // give value to caller
		queue->front = p_item->next;	        // move front pointer to next item
		queue->count--;					              // reduce queue count
		free (p_item);				                // give back memory
		
		// Did we just remove last item from queue? If so, must adjust
		// end pointer.
		if (IsQEmpty (queue))	queue->back = NULL;
	} 
  return EXIT_OK;
}

int DequeueAll (pQueue queue) {
  if (queue == NULL) {
    Serial.println("ERROR: Failed to dequeue all items because queue is NULL.");
    return EXIT_ERR;
  }
  int data; // temp data variable that stores data to be discarded
  while (!IsQEmpty (queue)) {
    if(Dequeue (queue, data) != EXIT_OK) return EXIT_ERR;
  }
  return EXIT_OK; 
}

int GetTime(DS3231 rtc_clock) {
  int time[3];
  bool h12Flag = false, pmFlag = false;
  time[0] = rtc_clock.getSecond();
  time[1] = rtc_clock.getMinute();
  time[2] = rtc_clock.getHour(h12Flag, pmFlag);
  return time[2] * 3600 + time[1] * 60 + time[0];
}
