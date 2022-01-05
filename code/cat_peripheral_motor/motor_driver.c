#include "motor_driver.h"

//任务函数调用电机控制函数
//所用参数：驱动算法，电机相数，速度，电机步数
static void motor_ctrl(motor_dev * dev)
{
    unsigned char i;
    //判断用什么驱动算法
    //知道是几相电机
    //还有速度方向

    //三相三拍 四相四拍 五相五拍
    if (dev->stepalg == one && dev->speed != 0)
    {
        switch(dev->step)
        {
            case 0:	    //AB
                for (i=0; i<dev->phases; i++)
                {
                    if (i==0 || i==1)
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;

            case 1:     // BC		 
                for (i=0; i<dev->phases; i++)
                {
                    if (i==1 || i==2)
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;

            case 2:	    //CD CA
                for (i=0; i<dev->phases; i++)
                {
                    //三相电机
                    if ((dev->phases > 3 && (i==2 || i==3))||(dev->phases == 3 && (i==2 || i==0)))
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;

            case 3:		//DE DA
                for (i=0; i<dev->phases; i++)
                {
                    //四相电机
                    if ((dev->phases > 4 && (i==3 || i==4))||(dev->phases == 4 && (i==3 || i==0)))
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;

            case 4:		//EA
                for (i=0; i<dev->phases; i++)
                {
                    //五相五拍
                    if (i==4 || i==0)
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;
        }
        if (dev->speed > 0)
        {
            dev->step++;
            if (dev->step == dev->phases)
            {
                dev->step = 0;
            }
        }
        else if (dev->speed < 0)
        {
            dev->step--;
            if (dev->step == 0xFF)
            {
                dev->step = dev->phases-1;
            }
        }
    }
    //两相四拍 三相六拍 四相八拍 五相十拍
    else if (dev->stepalg == two && dev->speed != 0)
    {
        switch(dev->step)
        {
            case 0:	    //A	
                for (i=0; i<dev->phases; i++)
                {
                    if (i==0)
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;

            case 1:     // AB		 
                for (i=0; i<dev->phases; i++)
                {
                    if (i==0 || i==1)
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;

            case 2:	    //B
                for (i=0; i<dev->phases; i++)
                {
                    if (i==1)
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;

            case 3:		//BC BA
                for (i=0; i<dev->phases; i++)
                {
                    //两相电机
                    if ((dev->phases > 2 && (i==1 || i==2)) || (dev->phases == 2 && (i==1 || i==0)))
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;

            case 4:		//C
                for (i=0; i<dev->phases; i++)
                {
                    if (i==2)
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;

            case 5:     //CD
                for (i=0; i<dev->phases; i++)
                {
                    //三项电机
                    if ((dev->phases > 3 && (i==2 || i==3)) || (dev->phases == 3 && (i==2 || i==0)))
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;

            case 6:	    //D
                for (i=0; i<dev->phases; i++)
                {
                    if (i==3)
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;

            case 7:     //DE
                for (i=0; i<dev->phases; i++)
                {
                    //四相电机
                    if ((dev->phases > 4 && (i==3 || i==4)) || (dev->phases == 4 && (i==3 || i==0)))  
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;

            case 8:     //E
                for (i=0; i<dev->phases; i++)
                {
                    if (i==4)
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;

            case 9:     //EA
                for (i=0; i<dev->phases; i++)
                {
                    //五相电机
                    if (i==4 || i==0)
                    {
                        IoTGpioSetOutputVal(dev->gpio[i], 0);
                    }
                    else
                    {
                        IoTGpioSetOutputVal(dev->gpio[i],1);
                    }  
                }
            break;
        }
        if (dev->speed > 0)
        {
            dev->step++;
            if (dev->step == dev->phases*2)
            {
                dev->step = 0;
            }
        }
        else if (dev->speed < 0)
        {
            dev->step--;
            if (dev->step == 0xFF)
            {
                dev->step = dev->phases*2-1;
            }
        }
    }
    //停止
    else if (dev->speed == 0)
    {
        for (i=0; i<dev->phases; i++)
        {
            IoTGpioSetOutputVal(dev->gpio[i],1);
        }
    }
    usleep(abs(dev->speed));
}

static void motor_task(motor_dev * dev)
{
    for(;;)
    {
        motor_ctrl(dev);
        printf("\nstep: %d",dev->step);
    }
}
/*  用户调用初始化函数
    unsigned char gpio[MAXPHASES];	    //电机GPIO
    unsigned char phases;               //当前电机相数
    int speed;                          //电机转速
    unsigned char step;                 //电机步进计数
    enum {one,two} stepalg;             //电机驱动算法,0:一相一拍1:一相两排
@return Returns the thread ID; returns NULL in the case of an error.
还要返回结构体*/
motor_dev * motor_init(unsigned char * gpio,unsigned char phases,unsigned char stepalg)
{
    unsigned char i;
    unsigned char gpiomul[15];

    osThreadAttr_t attr;
    osThreadId_t taskID;
    motor_dev * dev = (motor_dev *)malloc(sizeof(motor_dev));
    memset(dev,0,sizeof(motor_dev));

    attr.name = "motor_task";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 1024 * 4;
    attr.priority = 25;

    //所用结构体参数：驱动算法，电机相数，速度，电机步数
    dev->phases = phases;
    dev->stepalg = stepalg;
    dev->speed = 0;
    dev->step = 0;
    dev->gpio = gpio;

    //get the GPIO multiplexing function id
    gpiomul[0] = HI_IO_FUNC_GPIO_0_GPIO;
    gpiomul[1] = HI_IO_FUNC_GPIO_1_GPIO;
    gpiomul[2] = HI_IO_FUNC_GPIO_2_GPIO;
    gpiomul[3] = HI_IO_FUNC_GPIO_3_GPIO;
    gpiomul[4] = HI_IO_FUNC_GPIO_4_GPIO;
    gpiomul[5] = HI_IO_FUNC_GPIO_5_GPIO;
    gpiomul[6] = HI_IO_FUNC_GPIO_6_GPIO;
    gpiomul[7] = HI_IO_FUNC_GPIO_7_GPIO;
    gpiomul[8] = HI_IO_FUNC_GPIO_8_GPIO;
    gpiomul[9] = HI_IO_FUNC_GPIO_9_GPIO;
    gpiomul[10] = HI_IO_FUNC_GPIO_10_GPIO;
    gpiomul[11] = HI_IO_FUNC_GPIO_11_GPIO;
    gpiomul[12] = HI_IO_FUNC_GPIO_12_GPIO;
    gpiomul[13] = HI_IO_FUNC_GPIO_13_GPIO;
    gpiomul[14] = HI_IO_FUNC_GPIO_14_GPIO;

    for (i=0; i<phases; i++)
    {
        // init gpio
        IoTGpioInit(*(gpio+i));
        // set the GPIO multiplexing function
        hi_io_set_func(*(gpio+i), gpiomul[*(gpio+i)]);
        //set GPIO is output mode
        IoTGpioSetDir(*(gpio+i), IOT_GPIO_DIR_OUT);
    }
    dev->taskID = osThreadNew((osThreadFunc_t)motor_task, dev, &attr);
    if (dev->taskID == NULL) {    //任务1创建
        printf("Failed to create motor_task!\n");                          //创建失败输出
    }

    return dev;
}

//用户调用取消初始化函数
//删除创建的任务
//释放malloc申请的内存
void motor_deinit(motor_dev * dev)
{
    osThreadTerminate(dev->taskID);
    free(dev);
    dev = NULL;
}

//用户调用更改速度
void motor_setspeed(int speed,motor_dev * dev)
{
    dev->speed = speed;
}

