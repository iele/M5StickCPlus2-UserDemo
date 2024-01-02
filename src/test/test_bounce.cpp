#include "test.h"

namespace TEST
{

    void TEST::bounce_init()
    {
        imu.Init();
    }

    void TEST::bounce_test()
    {
        printf("bounce test\n");

        int score = 0;

        float gravx = 0;
        float gravy = 0;
        float gravz = 0;

        double x = 67;
        double y =120;

        int tx = random() % (135-30) + 15;
        int ty = random() % (240-30) + 15;

        int s = 15;
        double speedx = 0;
        double speedy = 0;

        bool tonedx = false;
        bool tonedy = false;

        while (1)
        {
            imu.getAccelData(&gravx, &gravy, &gravz);
            speedx -= gravx;
            speedy -= gravy;
            x +=  speedx;
            y += speedy;

            if (x < 0 + s) 
            {
                speedx = (-speedx) / 1.5;
                x = 0 + s;
                if (!tonedx) 
                {
                    _tone(440, 50);
                    tonedx = true;
                }
            } 
            else if (x > 135 - s) 
            {
                speedx = (-speedx) / 1.5;
                x = 135 - s;
                if (!tonedx) 
                {
                    _tone(440, 50);
                    tonedx = true;
                }
            } 
            else 
            {
                tonedx = false;
            }

            if (y < 0 + s) 
            {
                speedy = (-speedy) / 1.5;
                y = 0 + s;
                if (!tonedy) 
                {
                    _tone(440, 50);
                    tonedy = true;
                }
            } 
            else if (y > 240 - s) 
            {
                speedy = (-speedy) / 1.5;
                y = 240 - s;
                if (!tonedy) 
                {
                    _tone(440, 50);
                    tonedy = true;
                }
            } 
            else 
            {
                tonedy = false;
            }

            display->fillScreen(TFT_BLACK);
            display->setTextColor(TFT_WHITE, TFT_BLACK);

            Disbuff->drawNumber(score, 5, 5);
            Disbuff->drawCircle(y, x, s);
            Disbuff->fillCircle(y, x, s, TFT_WHITE);
            Disbuff->drawLine(y, x, y+speedy*10, x+speedx*10, TFT_DARKGRAY);
            Disbuff->drawLine(y, x, ty, tx, TFT_BROWN);

            Disbuff->drawCircle(ty, tx, s, TFT_DARKGREEN);            
            Displaybuff();

            if (int(x) >= tx - 3 && 
                int(x) <= tx + 3 && 
                int(y) >= ty - 3 && 
                int(y) <= ty + 3) 
            {
                _tone(5000, 100);
                score++;
                x = 67;
                y =120;
                tx = random() % (135-30) + 15;
                ty = random() % (240-30) + 15;
                s = 15;
                speedx = 0;
                speedy = 0;
                tonedx = false;
                tonedy = false;
            }

            delay(20);

            checkReboot();
            if (checkBtnA())
            {
                printf("quit bounce test\n");
                break;
            }
            if (checkBtnB()) 
            {
                x = 67;
                y =120;
                tx = random() % (135-30) + 15;
                ty = random() % (240-30) + 15;
                s = 15;
                speedx = 0;
                speedy = 0;
                tonedx = false;
                tonedy = false;
            }
        }
    }

}
