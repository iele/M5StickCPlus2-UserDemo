/**
 * @file test.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-05-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "test.h"

namespace TEST
{

    void TEST::hardware_init()
    {
        /* Hold pwr pin */
        gpio_reset_pin((gpio_num_t)POWER_HOLD_PIN);
        pinMode(POWER_HOLD_PIN, OUTPUT);
        digitalWrite(POWER_HOLD_PIN, HIGH);

        Wire1.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    }

    void TEST::power_off()
    {
        rtc_init();
        display->fillScreen(TFT_BLACK);
        displayUpdate();

        while ((!btnPWR.read()))
        {
            delay(100);
        }

        delay(200);

        printf("power off\n");
        digitalWrite(POWER_HOLD_PIN, 0);
        delay(10000);

        while (1)
        {
            delay(1000);
        }
    }

    void TEST::setup()
    {
        hardware_init();
        key_init();
        lcd_init();
        rtc_init();
        imu_init();
        temp_init();
        mic_init();
        ble_init();
        bounce_init();
        leveller_init();
        ColorBar();
    }

    void TEST::loop()
    {
        imu_test();
        bounce_test();
        leveller_test();
        temp_test();
        gol_test();
        rtc_test();
        new_mic_test_fft();
        // tone_test();
        ir_test();
        wifi_test();
        ble_test();

        display->setFont(&fonts::Font0);
        display->setTextSize(1);
        displayUpdate();
    }

}
