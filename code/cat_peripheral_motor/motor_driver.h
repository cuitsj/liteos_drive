#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#include <stdio.h>
#include <stdlib.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "hi_io.h"
#include "iot_gpio.h"

typedef struct{
    unsigned char * gpio;	            //电机GPIO
    unsigned char phases;               //当前电机相数
    volatile int speed;                 //电机转速
    unsigned char step;                 //电机步进计数
    enum {one,two} stepalg;             //电机驱动算法,one:一相一拍two:一相两排
    osThreadId_t taskID;                //电机驱动任务ID
} motor_dev;

motor_dev * motor_init(unsigned char * gpio,unsigned char phases,unsigned char stepalg);
void motor_deinit(motor_dev * dev);
void motor_setspeed(int speed,motor_dev * dev);

#endif