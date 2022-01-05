#include "motor_driver.h"

static void motor_main(void)
{
    motor_dev * dev;
    unsigned char gpio[]={14,13,2,7};//定义gpio数组存放所用管脚编号按照ABCD相的顺序排列，

    dev = motor_init(gpio,4,two);
    
    for(;;)
    {
        motor_setspeed(-50,dev);
        printf("motor set success1!\n");
        usleep(10000000);
        motor_setspeed(50,dev);
        printf("motor set success2!\n");
        usleep(10000000);
    }
}

APP_FEATURE_INIT(motor_main);