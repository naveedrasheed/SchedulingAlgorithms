#include "stdafx.h"

Process invalid_process;

Process CreateProcess(char *name, int priority, int time_quantam, int cpu_burst)
{
	struct Process process;

	process.id = process_id++;
	process.name = name;
	process.priority = priority;
	process.processor = INVALID_PROCESSOR;
	process.time_quantam = time_quantam;
	process.cpu_burst = cpu_burst;	
	process.task_time = cpu_burst;
	process.elapsed_time = 0;

	return process;
}
