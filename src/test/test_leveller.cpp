#include "test.h"

namespace TEST
{

    void TEST::leveller_init()
    {
        imu.Init();
    }

    void TEST::leveller_test()
    {
        printf("leveller test\n");
        Kalman kalmanx =  Kalman();
        Kalman kalmany =  Kalman();
        float gravx = 0;
        float gravy = 0;
        float gravz = 0;
        imu.getAccelData(&gravx, &gravy, &gravz);
        kalmanx.setAngle(gravx);
        kalmany.setAngle(gravx);

        double x = 67;
        double y =120;

        double rx = 67;
        double ry =120;
        int s = 15;

        while (1)
        {
            imu.getAccelData(&gravx, &gravy, &gravz);
            gravx = kalmanx.getAngle(gravx, 0, 0.1);
            gravy = kalmany.getAngle(gravy, 0, 0.1);

            x = rx + rx * gravx;
            y = ry + ry * gravy;

            bool overx = false; 
            bool overy = false;
            if (x >= 135 - s) {
                x = 135 - s;
                overx = true;
            }
            if (x <= s) {
                x = s;
                overx = true;
            }
            if (y >= 240 - s) {
                y = 240 - s;
                overy = true;
            }
            if (y <= s) {
                y = s;
                overy = true;
            }

            display->fillScreen(TFT_BLACK);
            display->setTextColor(TFT_WHITE, TFT_BLACK);
            Disbuff->setTextColor(Disbuff->color565(180, 180, 180));
            Disbuff->setTextSize(1);
            Disbuff->setCursor(5, 5);
            Disbuff->printf("x:  %f\n", gravx);
            Disbuff->setCursor(5, 12);
            Disbuff->printf("y:  %f\n", gravy);
        
            if (!overy) {
                Disbuff->drawRoundRect( 0, rx - s / 2,  ry * 2, s, 5, TFT_LIGHTGRAY);
            }
            if (!overx) {
                Disbuff->drawRoundRect(ry - s / 2, 0, s, rx * 2, 5, TFT_LIGHTGRAY);
            }
            Disbuff->fillRect(ry - s / 2,  rx - s / 2, s, s, TFT_YELLOW);
            if (!overy) {
                Disbuff->fillCircle(y, rx, s / 2, TFT_RED);
            }
            if (!overx) {
                Disbuff->fillCircle(ry, x, s / 2, TFT_RED);
            }
            
            Displaybuff();

            delay(20);

            checkReboot();
            if (checkBtnA())
            {
                printf("quit leveller test\n");
                break;
            }
            if (checkBtnB()) 
            {
            }
        }
    }

}
