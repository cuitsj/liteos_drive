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
#include <unistd.h>

#include "ohos_init.h"
#include "cmsis_os2.h"
#include "iot_gpio.h"
#include "hi_io.h"


#define LED_GPIO 7
#define BUTTON_F1_GPIO 11

/**
 * @brief Callback for F1 key
 *
 */
static void F1Pressed(char* arg)
{
    (void)arg;
    static uint8_t value = 0;

    usleep(1);
    value=!value;
    IoTGpioSetOutputVal(LED_GPIO, value);
    printf("\nF1 pressed");
}

/**
 * @brief Main Entry of the Button Example
 *
 */
static void ButtonExampleEntry(void)
{
    // init gpio of LED
    IoTGpioInit(LED_GPIO);
    IoTGpioSetDir(LED_GPIO, IOT_GPIO_DIR_OUT);

    // init gpio of F1 key and set it as the falling edge to trigger interrupt
    IoTGpioInit(BUTTON_F1_GPIO);
    hi_io_set_func(BUTTON_F1_GPIO, HI_IO_FUNC_GPIO_11_GPIO);
    IoTGpioSetDir(BUTTON_F1_GPIO, IOT_GPIO_DIR_IN);
    hi_io_set_pull(BUTTON_F1_GPIO, HI_IO_PULL_UP);
    IoTGpioRegisterIsrFunc(BUTTON_F1_GPIO, IOT_INT_TYPE_EDGE, IOT_GPIO_EDGE_RISE_LEVEL_HIGH, F1Pressed, NULL);
}

APP_FEATURE_INIT(ButtonExampleEntry);