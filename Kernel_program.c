#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_int.h"
#include "../GLOBAL_INIT/GLOBAL_int.h"
#include "../TIMERS/TIMER_int.h"

#include "Kernel_private.h"
#include "Kernel_interface.h"
#include "Kernel_config.h"

typedef struct
{
	u8 Peripdicity;
	void (*task_func)(void);
	u8 status;
}task_t;

task_t system_task[TASK_NUM]={{NULL}};



void RTOS_voidStart(void)
{
	Timer1_SetInterruptTime_ms(1,&scheduler);
	Global_Interrupt_Enable();
}

void RTOS_u8CreateTask(u8 Copy_u8Priority,void (*Copy_pvTaskFunc)(void),u16 Copy_u16Periodicity)
{
	if(system_task[Copy_u8Priority].task_func==NULL)
	{
		system_task[Copy_u8Priority].Peripdicity=Copy_u16Periodicity;
		system_task[Copy_u8Priority].task_func=Copy_pvTaskFunc;
		system_task[Copy_u8Priority].status=RESUMED;
	}
	else
	{
		//no nothing
	}
}

static void scheduler(void)
{
	volatile static u16 counter=0;
	u8 i;
	counter++;
	for(i=0;i<TASK_NUM;i++)
	{
		if(system_task[i].status==RESUMED)
		{
			if(counter%system_task[i].Peripdicity==0)
			{
				if(system_task[i].task_func !=NULL)
				{
					system_task[i].task_func();
				}
				else
				{
					//no nothing
				}
			}
		}

		else
		{
			//no nothing
		}
	}
}





void RTOS_voidSuspendTask(u8 Copy_u8Priority)
{
	system_task[Copy_u8Priority].status=SUSPENDED;
}

void RTOS_voidResumeTask(u8 Copy_u8Priority)
{
	system_task[Copy_u8Priority].status=RESUMED;
}


