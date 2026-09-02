#include <curses.h>
#include <math.h>
#include <stdio.h>

int Line(int x, int y_axis, double angle) {
	return x * tan(angle) + y_axis;
}

double Senoide(double t) {
	return sin(t * 2);
}

double deg2rad(double deg) {
	return deg * (M_PI/180);
}

int main(int argc, char ** argv) {
	WINDOW * win = initscr();

	const int width = getmaxx(win);
	const int height = getmaxy(win);

	double time = 0.0;
	while (1) {
		clear();

		double angle = Senoide(time) * deg2rad(60.0);
		printf("Angle: %f\n", angle);

		for (int i = 0; i < width; i++) {
			int y = Line(i, 0, angle);
			mvaddch(height - i, (width / 2) - y, 'X');
		}

		refresh();
		getch();

		time += 0.10;
	}
}
