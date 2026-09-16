#include <curses.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

int Line(int x, int y_axis, double angle) {
	return x * tan(angle) + y_axis;
}

double Senoide(double t) {
	return sin(t * 5);
}

double deg2rad(double deg) {
	return deg * (M_PI/180);
}

double rad2deg(double rad) {
	return (rad * 180) / M_PI;
}

long DiffTimes(time_t time1_sec, long time1_nsec, time_t time2_sec, long time2_nsec) {
	long nanosec_out = 0.0;

	if (time1_sec != time2_sec) {
		nanosec_out += ((time1_sec - time2_sec) * 1000000000);
	}

	nanosec_out += (time1_nsec - time2_nsec);
	return nanosec_out;
}

const double FPS = 60.0;

double tolerance = 0.2;

int main(int argc, char ** argv) {
	WINDOW * win = initscr();

	const int width = getmaxx(win);
	const int height = getmaxy(win);

	double simutime = 0.0;
	struct timespec prev_realtime = {0};
	clock_gettime(CLOCK_MONOTONIC, &prev_realtime);

	// double second = 0.0;
	int n_rep = 0;
	int rep_lock = 0;

	while (1) {
		usleep((1/FPS) * 1000000);

		clear();

		double angle = Senoide(simutime) * deg2rad(70.0);

		for (int x = 0; x < height; x++) {
			int y = Line(x, 0, angle);

			int half_y = y / 2 ; // como o bloco é apróximadamente 2 vezes mais alto do que longo
			double line_lenght = sqrt((x * x) + (half_y * half_y));

			if (line_lenght > (height / 1.4)) continue; // ocupar 1.4 (??) da tela eu não sei o que é isso direito

			char linec = '|';
			if (angle > deg2rad(40.0)) linec = '/';
			else if (angle < -deg2rad(40.0)) linec = '\\';

			// mvaddch(height - x, (width / 2) + y, 'X');
			mvaddch(height - x, (width / 2) + y, linec);
		}

		mvprintw(0,0, "Simulation time: %f", simutime);
		mvprintw(1,0, "Angle: %f", rad2deg(angle));
		mvprintw(2,0, "Reps: %i", n_rep);
		mvprintw(3,0, "Frequency: %f", n_rep/simutime);

		if (angle <= tolerance && angle >= -tolerance) {
			if (rep_lock == 0) {n_rep += 1; rep_lock = 1;}
			int x = (width/2) - 5;
			int y = 0;
			mvprintw(y,x, "   XXXX   "); y++;
			mvprintw(y,x, " XXXXXXXX "); y++;
			mvprintw(y,x, "XXX GO XXX"); y++;
			mvprintw(y,x, " XXXXXXXX "); y++;
			mvprintw(y,x, "   XXXX   "); y++;
		}
		else rep_lock = 0;

		refresh();

		struct timespec t = {0};
		clock_gettime(CLOCK_MONOTONIC, &t);

		double difft = (DiffTimes(t.tv_sec, t.tv_nsec, prev_realtime.tv_sec, prev_realtime.tv_nsec) / 1000000000.0);
		simutime += difft;
		// second += difft;

		// if (second >= 1.0) second = 0.0;

		clock_gettime(CLOCK_MONOTONIC, &prev_realtime);
	}
}
