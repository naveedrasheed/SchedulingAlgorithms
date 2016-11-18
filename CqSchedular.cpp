#include "stdafx.h"

int CqSchedular(Process process)
{
	Process *process_ptr;

	/* If this is a valid process */
	if (process.id == INVALID_PROCESS_ID)
	{
		if (central_pqueue.queue_length)
		{
			process = Dequeue(&central_pqueue);
		}
		else
		{
			return 0;
		}
	}

	process_ptr = &process;

	/* If all processors are idle */
	if(active_process_count == 0)
	{
		/* No migration will occure in this case */
		if(process_ptr->processor != INVALID_PROCESSOR)
		{
			DispatchProcess(process_ptr->processor, process_ptr, BUSY);
		}
		else
		{
			DispatchProcess(0, process_ptr, BUSY);
		}

		Increment_Active_Process_Count();
	}
	else if(active_process_count < NUMBER_OF_PROCESSORS)
	{
		/* It is a new process. Put it on an idle processor */
		if(process_ptr->processor == INVALID_PROCESSOR)
		{
			for (int i = 0; i < NUMBER_OF_PROCESSORS; i++)
			{
				if (active_scheduling[i].processor_state == IDLE)
				{
					DispatchProcess(i, process_ptr, BUSY);
					break;
				}
			}
		}
		else if (active_scheduling[process.processor].processor_state == IDLE)
		{
			/* Hoping that no migratin occured */
			DispatchProcess(process_ptr->processor, process_ptr, BUSY);
		}
		else
		{
			for (int i = 0; i < NUMBER_OF_PROCESSORS; i++)
			{
				if (active_scheduling[i].processor_state == IDLE)
				{
					/* Schedual on any available processor */
					DispatchProcess(i, process_ptr, BUSY);
					break;
				}
			}
		}

		Increment_Active_Process_Count();
	}
	else
	{
		/* All processors are busy. Put the process on queue. */
		int i = 0;
		int avail_processor = 0;
		int min = active_scheduling[i++].process.priority;
			
		for(; i < NUMBER_OF_PROCESSORS; i++)
		{
			if(active_scheduling[i].process.priority < min)
			{
				min = active_scheduling[i].process.priority;
				avail_processor = i;
			}
		}

		/* If it is a high priority process, Schdeule it. */
		if (process.priority > min)
		{
			SetProcessorState(avail_processor, IDLE);
			Decrement_Active_Process_Count();
			Enqueue(&central_pqueue, active_scheduling[avail_processor].process);

			DispatchProcess(avail_processor, process_ptr, BUSY);

			Increment_Active_Process_Count();
		}
		else
		{
			Enqueue(&central_pqueue, *process_ptr);
		}
	}

	return 0;
}

void DispatchProcess(int processor, Process *process, ProcessorSate processor_state)
{
	int old_processor;
	int old_process_id;

	if(process->id != INVALID_PROCESS_ID)
	{
		pthread_mutex_lock (&mutex_processor_state);
		old_processor = process->processor;
		old_process_id = active_scheduling[processor].process.id;
		process->processor = processor;
		active_scheduling[processor].process = *process;
		active_scheduling[processor].processor_state = processor_state;
		pthread_mutex_unlock (&mutex_processor_state);

		if((old_processor != INVALID_PROCESSOR) && (old_processor != processor) || (old_process_id != process->id))
		{
			/* Migration costs will apply */
			AddMigrationCost(processor);
		}
	}	
}

void SetProcessorState(int processor, ProcessorSate processor_state)
{
	pthread_mutex_lock (&mutex_processor_state);
	active_scheduling[processor].processor_state = processor_state;
	pthread_mutex_unlock (&mutex_processor_state);
}

void Increment_Active_Process_Count()
{
	pthread_mutex_lock (&mutex_active_process_count);
	active_process_count++;
	pthread_mutex_unlock (&mutex_active_process_count);
}

void Decrement_Active_Process_Count()
{
	pthread_mutex_lock (&mutex_active_process_count);
	active_process_count--;
	pthread_mutex_unlock (&mutex_active_process_count);
}
