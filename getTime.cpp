 #include <sys/time.h>
 #include <iostream>


 int main () {
    
	struct timeval tv;
	struct timezone tz;
	struct tm *tm;
	
	gettimeofday(&tv, NULL);
	time_t temp = tv.tv_sec;
	tm = localtime(&temp);
	
	std::cout << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec << std::endl;;
 return 0;
 }
