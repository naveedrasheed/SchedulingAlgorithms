#ifndef PROCESSOR
#define PROCESSOR

#ifdef  __cplusplus
extern "C" {
#endif

#define NUMBER_OF_PROCESSORS 4
#define INVALID_PROCESSOR -1

enum ProcessorSate
{
	IDLE,
	BUSY
};

int GetLeastLoadedProcessor();
void *Execute(void *processor);

#ifdef  __cplusplus
}
#endif
#endif