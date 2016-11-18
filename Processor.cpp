#include "stdafx.h"

float total_task_time;
float total_elapsed_time;
float grr;

using namespace System;

int GetLeastLoadedProcessor()
{
	int i = 0;
	int processor = 0;
	int min = pqueue[i++].queue_length;

	for(; i < NUMBER_OF_PROCESSORS; i++)
	{
		if(pqueue[i].queue_length < min)
		{
			min = pqueue[i].queue_length;
			processor = i;
		}
	}

	return processor;
}

void *Execute(void *arg)
{
	int processor = *((int *) arg);
	
	while(1)
	{
		int counter = 0;
		Process *process = &(active_scheduling[processor].process);

		while(active_scheduling[processor].processor_state == BUSY)
		{
			ExecuteInstructions(process);

			/* CPU burst of this processor is complete */
			if(!process->cpu_burst)
			{
				pthread_mutex_lock (&mutex_grr);
				total_elapsed_time += process->elapsed_time;
				total_task_time += process->task_time;
				grr = total_elapsed_time / total_task_time;
				pthread_mutex_unlock (&mutex_grr);

				SetProcessorState(processor, IDLE);
				Decrement_Active_Process_Count();
				SchedualProcess(invalid_process, sched_algo);

				break;
			}

			/* Time quantam expired on this processor */
			if(++counter == process->time_quantam)
			{
				SetProcessorState(processor, IDLE);
				Decrement_Active_Process_Count();
				SchedualProcess(*process, sched_algo);

				break;
			}
		}
	}

	return 0;
}

void AddMigrationCost(int processor)
{
	pthread_mutex_lock (&mutex_cpu_burst);

	/* Add task migration cost */
	active_scheduling[processor].process.cpu_burst += TASK_MIGRATION_COST;

	if (NUMBER_OF_PROCESSORS > 1)
	{
		/* Add system migration cost */
		for (int i = 0; i < NUMBER_OF_PROCESSORS; i++)
		{
			active_scheduling[i].process.cpu_burst += SYSTEM_MIGRATION_COST;
		}
	}

	pthread_mutex_unlock (&mutex_cpu_burst);
}

void ExecuteInstructions(Process *process)
{
	pthread_mutex_lock (&mutex_cpu_burst);
	process->cpu_burst--;
	pthread_mutex_unlock (&mutex_cpu_burst);

	process->elapsed_time++;

	//for(volatile int i = 0; i < 1000000; i++);
	Console::WriteLine(L"Process id " + process->id + 
						" with priority "+ process->priority +
						" is being executed at processor " + process->processor + "\r\n");
}
