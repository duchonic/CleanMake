// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "customLibs/helper.h"

#ifdef IS_LINUX
#include <sys/timerfd.h>

SCENARIO("test some timer") {
	INFO_LOG << "catchTimer tests" << '\n';

	GIVEN("make a timer") {
		struct itimerspec itval;
		int fd = timerfd_create(CLOCK_MONOTONIC,0);
		
		REQUIRE(fd != -1);

		unsigned int sec = 1;
		unsigned int nsec = 1;

		itval.it_interval.tv_sec = sec;
		itval.it_interval.tv_nsec = nsec;
		itval.it_value.tv_sec = sec;
		itval.it_value.tv_nsec = nsec;
			
		int ret = timerfd_settime(fd, 0, &itval, NULL);

		REQUIRE(ret >= 0);

		WHEN("timer is set") {

			unsigned long long missed;

			for(int runs = 5; runs > 0; runs--){
				int ret = read (fd, &missed, sizeof(missed));
				REQUIRE(ret != -1);
				INFO_LOG << "timer is running" << '\n';
			}
		}
	}
}
#endif