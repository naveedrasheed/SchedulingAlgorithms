#ifndef SCHEDULAR
#define SCHEDULAR

#ifdef  __cplusplus
extern "C" {
#endif

#define SCHEDULAR_CENTERAL_QUEUE    0
#define SCHEDULAR_INITIAL_PLACEMENT 1
#define SCHEDULAR_TAKE              2

#define TASK_MIGRATION_COST         1
#define SYSTEM_MIGRATION_COST       TASK_MIGRATION_COST * (5 / 100)

enum SchedulingAlgorithm
{
	CENTERAL_QUEUE,
	INITIAL_PLACEMENT,
	TAKE       
};

struct SchedulingInfo
{
	ProcessorSate processor_state;
	Process process;
};


extern PriorityQueue pqueue[NUMBER_OF_PROCESSORS];
extern PriorityQueue central_pqueue;

extern int active_process_count;
extern SchedulingInfo active_scheduling[NUMBER_OF_PROCESSORS];
extern int process_id;
extern SchedulingAlgorithm sched_algo;
extern Process invalid_process;

extern pthread_mutex_t mutex_cpu_burst;
extern pthread_mutex_t mutex_active_process_count;
extern pthread_mutex_t mutex_processor_state;
extern pthread_mutex_t mutex_central_pqueue;
extern pthread_mutex_t mutex_grr;

int SchedualProcess(Process process, SchedulingAlgorithm sched_algo);
int CqSchedular(Process process);

void DispatchProcess(int processor, Process *process, ProcessorSate processor_state);
void SetProcessorState(int processor, ProcessorSate processor_state);
void Increment_Active_Process_Count();
void Decrement_Active_Process_Count();
void AddMigrationCost(int processor);
void ExecuteInstructions(Process *process);

#ifdef  __cplusplus
}
#endif
#endif