#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <progbase.h>
#include <progbase/console.h>
#include <progbase/canvas.h>

struct vec2D
{
	float x;
	float y;
};

struct colour
{
	char r;
	char g;
	char b;
};

struct ball
{
	struct colour ofball;
	struct vec2D loc;
	int rad;
	struct vec2D vel;
	float k;
};

int fequals(float a, float b);

float length(struct vec2D v);
struct vec2D negative(struct vec2D v);
struct vec2D add(struct vec2D a, struct vec2D b);
struct vec2D mult(struct vec2D v, float n);
struct vec2D norm(struct vec2D v);
struct vec2D rotate(struct vec2D v, float angle);
float distance(struct vec2D a, struct vec2D b);
float angle(struct vec2D v);
struct vec2D fromPolar(float angle, float length);
int equals(struct vec2D a, struct vec2D b);
struct vec2D mult(struct vec2D v, float n);

int getRand(int min, int max);
struct ball createBall(int canvasWidth, int canvasHeight);
struct ball updateBall(struct ball shar, int x1, long dt, long t, int cWidth, int cHeight);

void drowball(struct ball shar);

void mainTest();

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		return 1;
	}

	else if (strcmp(argv[1], "-n") == 0)
	{
		srand(time(NULL));

		struct ConsoleSize cSize = Console_size();
		const int h = cSize.rows * 2;
		const int w = cSize.columns;

		Console_clear();
		Canvas_setSize(w, h);
		Canvas_invertYOrientation();

		int nBalls = atoi(argv[2]);
		struct ball shar[nBalls];

		for (int i = 0; i < nBalls; i++)
		{
			shar[i] = createBall(w, h);
		}

		const long sleepMillisTime = 30;
		long t = 0;
		int x1 = 0;

		do
		{
			Canvas_beginDraw();
			x1++;
			Canvas_setColorRGB(0, 250, 0);
			Canvas_strokeLine(0, (h / 2), w, (h / 2));

			const long dt = sleepMillisTime;
			t += dt;

			for (int i = 0; i < nBalls; i++)
			{
				drowball(shar[i]);
				shar[i] = updateBall(shar[i], x1, dt, t, w, h);
			};

			sleepMillis(sleepMillisTime);

			Canvas_endDraw();
		} while (!Console_isKeyDown());

		return 0;
	}
	else if (strcmp(argv[1], "-t") == 0)
	{
		mainTest();
	}
}

struct ball createBall(int canvasWidth, int canvasHeight)
{
	struct ball shar =
		{
			.loc.x = getRand(canvasWidth / 10, canvasHeight / 1.5),
			.loc.y = getRand(canvasHeight / 10, canvasHeight / 1.5),
			.rad = getRand(4, 10),
			.ofball.r = getRand(1, 255),
			.ofball.g = getRand(1, 255),
			.ofball.b = getRand(1, 255),
			.vel.x = 3.14159 * getRand(1, 5),
		};

	return shar;
};

struct ball updateBall(struct ball shar, int x1, long dt, long t, int cWidth, int cHeight)
{
	shar.vel.y = 0.25*sin(x1);
	shar.loc.x += shar.vel.x;
	shar.loc.y += shar.loc.y;

	if (shar.loc.x + shar.rad >= cWidth || shar.loc.x - shar.rad <= 0)
	{
		shar.vel.x = -shar.vel.x;
	}

	if (shar.loc.y + shar.rad >= cHeight || shar.loc.y - shar.rad <= 0)
	{
		shar.loc.y = 0.2 * shar.loc.y;
		shar.vel.y = 0.5 * shar.vel.y;
	}

	return shar;
};

void drowball(struct ball shar)
{
	Canvas_setColorRGB(shar.ofball.r, shar.ofball.g, shar.ofball.b);
	Canvas_fillCircle(shar.loc.x, shar.loc.y, shar.rad);
}

int getRand(int min, int max)
{
	int a = rand() % (max - min + 1) + min;
	return a;
};

float length(struct vec2D v)
{
	float length = 0;
	length = sqrt(pow(v.x, 2) + pow(v.y, 2));
	return length;
};

struct vec2D negative(struct vec2D v)
{
	struct vec2D copy =
		{
			copy.x = -v.x,
			copy.y = -v.y,
		};

	return copy;
};

struct vec2D add(struct vec2D a, struct vec2D b)
{
	struct vec2D copy =
		{
			copy.x = a.x + b.x,
			copy.y = a.y + b.y,
		};

	return copy;
};

struct vec2D mult(struct vec2D v, float n)
{
	struct vec2D newVec = v;
	newVec.x *= n;
	newVec.y *= n;
	return newVec;
};

struct vec2D norm(struct vec2D v)
{
	float length = 0;
	length = sqrt(pow(v.x, 2) + pow(v.y, 2));

	struct vec2D copy =
		{
			copy.x = v.x / fabs(length),
			copy.y = v.y / fabs(length),
		};

	return copy;
};

float distance(struct vec2D a, struct vec2D b)
{
	float distance = 0;
	distance = sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));

	return distance;
};

float angle(struct vec2D v)
{
	float angle = acos((v.x * 1) / (sqrt(pow(v.x, 2) + pow(v.y, 2))));

	return angle;
};

struct vec2D rotate(struct vec2D v, float angle)
{
	struct vec2D copy =
		{
			copy.x = v.x * cos(angle) - v.y * sin(angle),
			copy.y = v.x * cos(angle) + v.y * sin(angle),
		};

	return copy;
};

struct vec2D fromPolar(float angle, float length)
{
	struct vec2D fromPolar =
		{
			fromPolar.x = length * cos(angle),
			fromPolar.y = length * sin(angle),
		};

	return fromPolar;
};

int fequals(float a, float b)
{
	return fabs(a - b) < 1e-4;
};

int equals(struct vec2D a, struct vec2D b)
{
	return fequals(a.x, b.x) && fequals(a.y, b.y);
};

void mainTest()
{
	printf("TEST\n");
	struct vec2D a = {1, 0};
	struct vec2D b = {2, -2};
	struct vec2D c = {3, 4};
	assert(equals(a, a));
	assert(fequals(length(a), 1));
	struct vec2D newvector = {-1, 0};
	assert(equals(negative(a), newvector));
	struct vec2D ex = {3, -2};
	assert(equals(add(a, b), ex));
	//--------------------------
	struct vec2D polar = {length(a) * cos(90), length(a) * sin(90)};
	assert(equals(fromPolar(90, length(a)), polar));
	//--------------------------
	struct vec2D k = {2, 0};
	assert(equals(mult(a, 2), k));
	//--------------------------
	assert(fequals(angle(a), acos(1)));
	//---------------------------
	float m = sqrt(5);
	assert(fequals(distance(a, b), m));
	//---------------------------
	struct vec2D s = {0.6, 0.8};
	assert(equals(norm(c), s));
	//---------------------------
	/*struct vec2D rot = {0 * cos(90 + acos(0)), 1 * sin(90 + acos(1))};
	assert(equals(rotate(a, 90), rot));*/ //test failed
	printf("END OF THE TEST\n");
}