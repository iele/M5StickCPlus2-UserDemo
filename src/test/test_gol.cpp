// The Game of Life, also known simply as Life, is a cellular automaton
// devised by the British mathematician John Horton Conway in 1970.
//  https://en.wikipedia.org/wiki/Conway's_Game_of_Life

#include "test.h"

namespace TEST
{

    void TEST::gol_test()
    {
        int height = 135;
        int width = 240;

        display->fillScreen(TFT_BLACK);
        display->clear();
        lgfx::v1::color_depth_t defaultColorDepth = display->getColorDepth();
        display->setColorDepth(8);
        Disbuff->createPalette();
        Disbuff->setPaletteColor(1, TFT_WHITE);

        while (1)
        {
            bool stop = false;

            int height = 240;
            int width = 135;

            int y = 1;
            do
            {
                int x = 1;
                do
                {
                    if (random(10) == 0)
                    {
                        Disbuff->drawPixel(x, y, 1);
                    }
                } while (++x < height - 1);
            } while (++y < width - 1);

            Displaybuff();

            int diff;
            do
            {
                diff = 0;

                auto old_buf = (uint8_t *)Disbuff->getBuffer();
                auto new_buf = (uint8_t *)Disbuff->getBuffer();
                int height = 240;
                int width = 135;
                int py;
                int y = width - 1;
                int ny = 0;
                do
                {
                    py = y;
                    y = ny;
                    if (++ny == width)
                        ny = 0;

                    int px;
                    int x = height - 1;
                    int nx = 0;
                    do
                    {
                        px = x;
                        x = nx;
                        if (++nx == height)
                            nx = 0;

                        int neighbors = old_buf[px + py * height] + old_buf[x + py * height] +
                                        old_buf[nx + py * height] + old_buf[px + y * height] +
                                        old_buf[nx + y * height] + old_buf[px + ny * height] +
                                        old_buf[x + ny * height] + old_buf[nx + ny * height];

                        int idx = x + y * height;
                        bool flg = (neighbors == 3) || (neighbors == 2 && old_buf[idx]);
                        if (flg != new_buf[idx])
                        {
                            Disbuff->drawPixel(x, y, flg ? TFT_WHITE : TFT_BLACK);
                            new_buf[idx] = flg;
                            ++diff;
                        }
                    } while (nx);
                } while (ny);

                Displaybuff();

                delay(20);

                checkReboot();
                if (checkBtnA())
                {
                    stop = true;
                    break;
                }
            } while (diff);

            if (stop)
                break;
        }

        display->setColorDepth(defaultColorDepth);
    }
} // namespace TEST