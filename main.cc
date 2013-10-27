#include "my_date.h"
#include <iostream>
#include <ctime>

int main(int argc, char **argv) {
	if (1 == argc) {
		time_t raw_time;
		time(&raw_time);
		MyDate t(raw_time);
		t.Kalender();
	}
	return 0;
}
