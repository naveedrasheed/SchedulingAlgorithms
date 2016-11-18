// SchedulingAlgoritms.cpp : main project file.

#include "stdafx.h"

using namespace System;

PriorityQueue pqueue[NUMBER_OF_PROCESSORS];
PriorityQueue central_pqueue;
int process_id = 1;

void Enqueue(PriorityQueue *pqueue, struct Process process) 
{
	struct PriorityQueueElement* temp = 
		(struct PriorityQueueElement*)malloc(sizeof(struct PriorityQueueElement));

	temp->process = process;
	temp->next = 0;
	temp->previous = pqueue->tail;
	
	pthread_mutex_lock (&mutex_central_pqueue);

	/* First element */
	if((pqueue->head == 0) && (pqueue->tail == 0))
	{
		pqueue->head = pqueue->tail = temp;
	}
	else
	{
		/* Same priority process goes to pqueue->tail */
		if(temp->process.priority <= pqueue->tail->process.priority)
		{
			pqueue->tail->next = temp;
			pqueue->tail = temp;
		}
		else
		{
			/* Adjust task according to priority */
			struct PriorityQueueElement* current = pqueue->tail->previous;

			while(current)
			{
				if (temp->process.priority <= current->process.priority)
				{
					temp->next = current->next;
					temp->previous = current;
					current->next->previous = temp;
					current->next = temp;
					break;
				}
				else
				{
					current = current->previous;
				}
			}

			/* This is the highest priority proccess */
			if(current == 0)
			{
				temp->next = pqueue->head;
				pqueue->head = temp;
				pqueue->head->next->previous = pqueue->head;
				pqueue->head->previous = 0;
			}
		}
	}

	pqueue->queue_length++;

	pthread_mutex_unlock (&mutex_central_pqueue);
}

Process Dequeue(PriorityQueue *pqueue) 
{
	Process process;
	struct PriorityQueueElement* temp = NULL;

	pthread_mutex_lock (&mutex_central_pqueue);

	if(pqueue->queue_length > 0)
	{
		temp = pqueue->head;

		if(pqueue->head == pqueue->tail) 
		{
			pqueue->head = pqueue->tail = NULL;
		}
		else 
		{
			pqueue->head = pqueue->head->next;
			pqueue->head->previous = 0;
		}

		pqueue->queue_length--;
	}

	pthread_mutex_unlock (&mutex_central_pqueue);

	if(temp != NULL)
	{
		process = temp->process;
		free(temp);
	}

	return process;
}
