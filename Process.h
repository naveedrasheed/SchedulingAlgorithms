#ifndef PROCESS
#define PROCESS

#ifdef  __cplusplus
extern "C" {
#endif

#define INVALID_PROCESS_ID 0

struct Process
{
	int id;
	char *name;
	int priority;
	int processor;
	int time_quantam;
	float cpu_burst;
	float task_time;
	float elapsed_time;
};

Process CreateProcess(char *name, int priority, int time_quantam, int cpu_burst);

#ifdef  __cplusplus
}
#endif
#endif