/**
 * @file test_imu.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-05-26
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "test.h"

namespace TEST
{

    void TEST::temp_init()
    {
        imu.Init();
    }

    void TEST::temp_test()
    {
        printf("imu test\n");

        float temp;

        while (1)
        {
            imu.getTempData(&temp);
            Disbuff->fillRect(0, 0, 240, 135, TFT_BLACK);
            Disbuff->fillRect(0, 0, 240, 25, Disbuff->color565(20, 20, 20));
            Disbuff->setTextSize(2);
            Disbuff->drawString("Temperature", 55, 5, 1);
            Disbuff->setTextSize(4);
            Disbuff->setCursor(60, 60);
            Disbuff->printf("%.1fC", temp);

            Displaybuff();

            delay(20);
            checkReboot();
            if (checkBtnA())
            {
                printf("quit imu test\n");
                break;
            }
        }
    }
} // namespace TEST
