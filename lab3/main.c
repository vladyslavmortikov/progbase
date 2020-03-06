#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <progbase.h>
#include <progbase/console.h>

int main()
{

    Console_clear();

    // border size
    const int width_rz = 100;
    const int height_rz = 50;

    // origin point shift
    int centerx = width_rz / 2;
    int centery = height_rz / 2 + 1;

    // graphic coord.
    int grx = width_rz / 2;
    int gry = centery;
    int line_ab_y = centery;
    int line_ab_x = centerx;

    while (1)
    {

        // draw border (horizontal lines)
        for (int border_w = 1; border_w <= width_rz; border_w = border_w + 1)
        {
            int border_h = 1;
            Console_setCursorPosition(border_h, border_w);
            printf("*");
            border_h = height_rz;
            Console_setCursorPosition(border_h, border_w);
            printf("*");
        }

        // draw border (vertical lines)
        for (int border_h = 1; border_h <= height_rz; border_h = border_h + 1)
        {
            int border_w = 1;
            Console_setCursorPosition(border_h, border_w);
            printf("*");
            border_w = width_rz;
            Console_setCursorPosition(border_h, border_w);
            printf("*");
        }

        // draw y line
        for (int yline = 1; yline <= height_rz; yline++)
        {
            int xline = centerx;
            Console_setCursorPosition(yline, xline);
            printf("|");
        }

        // draw x line
        for (int xline = 1; xline < width_rz; xline++)
        {
            int yline = centery;
            Console_setCursorPosition(yline, xline);
            printf("-");
        }

        // function x
        const float xmin = -5;
        const float xmax = 5;
        const float xstep = 0.005;

        // function-to-console transformation values
        const float xwidth = xmax - xmin;
        const float yheight = 5;
        const float ax0 = width_rz / xwidth;
        const float ay0 = height_rz / yheight;

        int xper = 0;

        for (float x = xmin; x <= xmax; x = x + xstep)
        {
            float y = pow(x, 2);

            int gx = grx + ax0 * x;
            int gy = gry - (ay0 * y);
            if (gy == line_ab_y)
                xper = gx;
            Console_setCursorAttribute(BG_RED);
            Console_setCursorPosition(gy, gx);
            printf("·");
            Console_reset();
        }

        Console_setCursorPosition(2, 2);
        printf("%d", xper);

        // draw line AB
        
        for (float x = line_ab_x - xper; x < xper - line_ab_x - 1; x++)
        {
            Console_setCursorAttribute(BG_WHITE);
            Console_setCursorPosition(line_ab_y, line_ab_x + x);
            printf("*");
        }

        Console_reset();

        // user key input
        char keyCode = 0;
        keyCode = Console_getChar();

        // controls
        const int tStep = 1;

        switch (keyCode)
        {
        case 'w':
            if (gry >= 10)
            {
                gry -= tStep;
            }
            break;

        case 'a':
            if (grx > 20)
            {   line_ab_x -= tStep;
                grx -= tStep;
            }
            break;

        case 's':
            if (gry < 49)
            {
                gry += tStep;
            }
            break;

        case 'd':
            if (grx < width_rz-20)
            {   
                line_ab_x += tStep;
                grx += tStep;
            }
            break;

        case 'i':
            if (line_ab_y > 1)
            {
                line_ab_y -= tStep;
            }
            break;

        case 'k':
            line_ab_y += tStep;
            break;
        }

        Console_clear();
    }
    return 0;
}
