#include <stdio.h>
#include <time.h>

int main()
{
#if 0
	struct tm {
		int tm_sec;    /* Seconds (0-60) */
		int tm_min;    /* Minutes (0-59) */
		int tm_hour;   /* Hours (0-23) */
		int tm_mday;   /* Day of the month (1-31) */
		int tm_mon;    /* Month (0-11) */
		int tm_year;   /* Year - 1900 */
		int tm_wday;   /* Day of the week (0-6, Sunday = 0) */
		int tm_yday;   /* Day in the year (0-365, 1 Jan = 0) */
		int tm_isdst;  /* Daylight saving time */
	};	
#endif
	time_t t = time(NULL);
	struct tm* tm = gmtime(&t);
	printf("%d.%d.%d %d:%d:%d\n", tm->tm_year, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

	return 0;
}
