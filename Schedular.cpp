#include "stdafx.h"

int active_process_count;
SchedulingInfo active_scheduling[NUMBER_OF_PROCESSORS];

int SchedualProcess(Process process, SchedulingAlgorithm sched_algo)
{
	if(sched_algo == CENTERAL_QUEUE)
	{
		CqSchedular(process);
	}

	return 0;
}
