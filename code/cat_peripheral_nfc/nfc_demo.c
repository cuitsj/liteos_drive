/*
 * Copyright (c) 2020 Nanjing Xiaoxiongpai Intelligent Technology Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "cmsis_os2.h"
#include "iot_errno.h"
#include "iot_gpio.h"
#include "iot_i2c.h"
#include "nfc.h"
#include "ohos_init.h"
#include "hi_i2c.h"
#include "hi_io.h"

#define I2C_TASK_STACK_SIZE 1024 * 8
#define I2C_TASK_PRIO 25

#define TEXT "Welcome to BearPi-HM_Nano!"
#define WEB "harmonyos.com"

/**
 * @brief i2c task writes data to NFC tag
 *
 */
static void I2cTask(void)
{
    uint8_t ret;
    uint32_t res;
    hi_i2c_data i2cdata;
    unsigned char wtbuf[64];
	unsigned char rdbuf[256];
    unsigned char data[] = {0x10,0x3D,0x01,0x00,0X00,0X00};
    //unsigned char data[] = {0x00,0x02,0x05,0x54,0X02,0X62};

    // wtbuf[0] = 0x10;
    // wtbuf[1] = 0x3D;
    // GPIO_0 multiplexed to I2C1_SDA
    IoTGpioInit(HI_IO_NAME_GPIO_0);
    hi_io_set_func(HI_IO_NAME_GPIO_0, HI_IO_FUNC_GPIO_0_I2C1_SDA);

    // GPIO_1 multiplexed to I2C1_SCL
    IoTGpioInit(HI_IO_NAME_GPIO_1);
    hi_io_set_func(HI_IO_NAME_GPIO_1, HI_IO_FUNC_GPIO_1_I2C1_SCL);

    // baudrate: 400kbps
    IoTI2cInit(HI_I2C_IDX_1, 400000);
    IoTI2cSetBaudrate(HI_I2C_IDX_1,400000);


    // printf("\nI2C READ TEST\n");
    // printf("WRITE BLOCK ADDR\n");
    // res = hi_i2c_write(HI_I2C_IDX_1,0xA8,&i2cdata);
    // if (res != 0) {
    // printf("WRITE BLOCK ADDR FAILED:%x \n", res);
    // }
    // else
    // {
    //    printf("WRITE BLOCK ADDR SUCCESS\n");
    // }

    // printf("READ DATA");
    // res = hi_i2c_read(HI_I2C_IDX_1, 0xA8, &i2cdata);
    // if (res != 0) {
    // printf("I2C READ DATA FAILED:%x \n", res);
    // }
    // else
    // {
    //     printf("I2C READ DATA SUCCESS:%x %x %x %x \n", rdbuf[0],rdbuf[1],rdbuf[2],rdbuf[3]);
    // }
    // //memcpy(wtbuf, rdbuf, 4);
    // wtbuf[2] = rdbuf[0]|0x01;
    // wtbuf[3] = rdbuf[1];
    // wtbuf[4] = rdbuf[2];
    // wtbuf[5] = rdbuf[3];

    i2cdata.receive_buf = rdbuf;
    i2cdata.receive_len = 4;
    i2cdata.send_buf = data;
    i2cdata.send_len = 6;
    
    printf("\nI2C WRITE TEST\n");
    res = hi_i2c_write(HI_I2C_IDX_1,0xA8,&i2cdata);
    if (res != 0) {
    printf("I2C WRITE DATA FAILED:%x \n", res);
    }
    else
    {
       printf("I2C WRITE DATA SUCCESS\n");
    }

    // ret = storeText(NDEFFirstPos, (uint8_t*)TEXT);
    // if (ret != 1) {
    //     printf("NFC Write Data Falied :%d \n", ret);
    // }
    // ret = storeUrihttp(NDEFLastPos, (uint8_t*)WEB);
    // if (ret != 1) {
    //     printf("NFC Write Data Falied :%d \n", ret);
    // }
    while (1) {
        // printf("=======================================\n");
        // printf("***********I2C_NFC_example**********\n");
        // printf("=======================================\n");
        // printf("Please use the mobile phone with NFC function close to the development board!\n");
        // usleep(1000000);
    }
}

/**
 * @brief Main Entry of the I2c Example
 *
 */
static void I2cExampleEntry(void)
{
    osThreadAttr_t attr;

    attr.name = "I2cTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = I2C_TASK_STACK_SIZE;
    attr.priority = I2C_TASK_PRIO;

    if (osThreadNew((osThreadFunc_t)I2cTask, NULL, &attr) == NULL) {
        printf("Falied to create I2cTask!\n");
    }
}

APP_FEATURE_INIT(I2cExampleEntry);