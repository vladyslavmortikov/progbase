#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <progbase.h>
#include <progbase/console.h>
#include <progbase/canvas.h>

struct vec2D
{
	float x;
	float y;
};

struct ball
{
	struct vec2D loc;
	int rad;
	struct vec2D vel;
	char colour1;
	char colour2;
	char colour3;
	float k;
};

int main()
{
	srand(time(0));
	Console_clear();

	const float pi = 3.14;
	int N = 5;

	struct ConsoleSize consoleSize = Console_size();
	const int widthPixels = consoleSize.columns;
	const int heightPixels = consoleSize.rows * 2;

	struct ball shar[N];
	int FPS = 30;

	for (int i = 0; i < N; i++)
	{
		shar[i].loc.x = rand() % ((widthPixels / 2 + 20) - 20 + 1) + 20;
		shar[i].loc.y = rand() % ((heightPixels / 2 + 20) - 20 + 1) + 20;
		shar[i].rad = rand() % (10 - 5 + 1) + 5;
		shar[i].colour1 = rand() % 254 + 1;
		shar[i].colour2 = rand() % 254 + 1;
		shar[i].colour3 = rand() % 254 + 1;
		shar[i].k = 10;
		shar[i].vel.x = pi * (rand() % (10 - 1 / 10 + 1) + 1 / 10);
		shar[i].vel.y = shar[i].k * sin(shar[i].vel.x);
	}

	Canvas_setSize(widthPixels, heightPixels);
	Canvas_invertYOrientation();

	int x1 = 0;

	char workingLab = Console_getChar();
	printf("You entered: '%c'\n", workingLab);

	while (!Console_isKeyDown())
	{
		Canvas_beginDraw();

		Canvas_setColorRGB(0, 250, 0);
		Canvas_strokeLine(0, (heightPixels / 2), widthPixels, (heightPixels / 2));

		for (int i = 0; i < N; i++)
		{

			if (i <= 0.5 * N)
			{
				if (shar[i].loc.x + shar[i].rad >= widthPixels || shar[i].loc.x - shar[i].rad <= 0)
				{
					shar[i].vel.x = -shar[i].vel.x;
				}

				if (shar[i].loc.y + shar[i].rad >= heightPixels || shar[i].loc.y - shar[i].rad <= 0)
				{

					shar[i].vel.y = 0.5 * shar[i].vel.y;
				}
				x1++;
				shar[i].loc.x += shar[i].vel.x;
				shar[i].loc.y += 10 * sin(x1);

				Canvas_setColorRGB(shar[i].colour1, shar[i].colour2, shar[i].colour3);
				Canvas_fillCircle(shar[i].loc.x, shar[i].loc.y, shar[i].rad);
			}

			else
			{
				shar[i].k = -shar[i].k;

				if (shar[i].loc.x + shar[i].rad >= widthPixels || shar[i].loc.x - shar[i].rad <= 0)
				{
					shar[i].vel.x = -shar[i].vel.x;
				}

				if (shar[i].loc.y + shar[i].rad >= heightPixels || shar[i].loc.y - shar[i].rad <= 0)
				{

					shar[i].vel.y = 0.5 * shar[i].vel.y;
				}

				x1++;
				shar[i].loc.x -= shar[i].vel.x;
				shar[i].loc.y += 10 * sin(x1);

				Canvas_setColorRGB(shar[i].colour1, shar[i].colour2, shar[i].colour3);
				Canvas_fillCircle(shar[i].loc.x, shar[i].loc.y, shar[i].rad);
			}
		}

		
		Canvas_endDraw();
	sleepMillis(FPS);
	}

	puts("ПОКААААААААААААААА!");
	// if (islab6Running == false)
	// {
	// 	break;
	// }
	return 0;
}
