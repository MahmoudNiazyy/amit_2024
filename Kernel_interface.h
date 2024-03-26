

#ifndef KERNEL_INTERFACE_H_
#define KERNEL_INTERFACE_H_



void RTOS_voidStart(void);

void RTOS_u8CreateTask(u8 Copy_u8Priority,void (*Copy_pvTaskFunc)(void),u16 Copy_u16Periodicity);


void RTOS_voidSuspendTask(u8 Copy_u8Priority);

void RTOS_voidResumeTask(u8 Copy_u8Priority);

// wait /delete




#endif

