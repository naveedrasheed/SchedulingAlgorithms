// SchedulingAlgoritms.cpp : main project file.

#include "stdafx.h"
#include <time.h>

pthread_mutex_t mutex_cpu_burst;
pthread_mutex_t mutex_active_process_count;
pthread_mutex_t mutex_processor_state;
pthread_mutex_t mutex_central_pqueue;
pthread_mutex_t mutex_grr;

SchedulingAlgorithm sched_algo = CENTERAL_QUEUE;

using namespace System;

void main_application_process()
{
	int result;
	Process process;

	for (int i = 0; i < 100; i++)
	{
		process = CreateProcess("P1", 1, 25, 100);
		SchedualProcess(process, sched_algo);

		process = CreateProcess("P2", 1, 25, 100);
		SchedualProcess(process, sched_algo);

		process = CreateProcess("P3", 2, 25, 100);
		SchedualProcess(process, sched_algo);

		process = CreateProcess("P4", 2, 25, 100);
		SchedualProcess(process, sched_algo);

		process = CreateProcess("P5", 3, 25, 100);
		SchedualProcess(process, sched_algo);

		process = CreateProcess("P6", 3, 25, 100);
		SchedualProcess(process, sched_algo);

		process = CreateProcess("P7", 4, 25, 100);
		SchedualProcess(process, sched_algo);

		process = CreateProcess("P8", 4, 25, 100);
		SchedualProcess(process, sched_algo);

		process = CreateProcess("P9", 5, 25, 100);
		SchedualProcess(process, sched_algo);

		process = CreateProcess("P10", 5, 25, 100);
		SchedualProcess(process, sched_algo);
	}
}

int main(array<System::String ^> ^args)
{
	int processors[NUMBER_OF_PROCESSORS] = {0, 1, 2, 3};
	pthread_t thread_id;
	size_t cpusetsize = NUMBER_OF_PROCESSORS;

	pthread_mutex_init (&mutex_cpu_burst, 0);
	pthread_mutex_init (&mutex_active_process_count, 0);
	pthread_mutex_init (&mutex_processor_state, 0);
	pthread_mutex_init (&mutex_central_pqueue, 0);
	pthread_mutex_init (&mutex_grr, 0);

	for (int i = 0; i < NUMBER_OF_PROCESSORS; i++)
	{
		pthread_create (&thread_id, 0, Execute, (void *)&processors[i]);
		sched_setscheduler (i, 2);
	}

	main_application_process();
    Console::WriteLine(L"Hello World");

	pthread_join(thread_id, 0);

    return 0;
}
