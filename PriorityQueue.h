#include "Process.h"

#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE

#ifdef  __cplusplus
extern "C" {
#endif

struct PriorityQueueElement
{
	Process process;
	PriorityQueueElement *next;
	PriorityQueueElement *previous;
};

struct PriorityQueue
{
	struct PriorityQueueElement *head;
	struct PriorityQueueElement *tail;
	int queue_length;
};

void Enqueue(PriorityQueue *pqueue, struct Process process);
Process Dequeue(PriorityQueue *pqueue);

#ifdef  __cplusplus
}
#endif
#endif