//
// Created by ivanbrekman on 26.09.2021.
//

#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

#include "errorlib.h"

int isbadreadptr(void* ptr) {
    int nullfd = open("/dev/random", O_WRONLY);

    errno = 0;
    write(nullfd, ptr, 1);
    close(nullfd);

    return errno;
}

char* datetime(char* calendar_date) {
    const time_t timer = time(NULL);
    struct tm* calendar = localtime(&timer);

    strftime(calendar_date, 40, "%d.%m.%Y %H:%M:%S, %A", calendar);

    return calendar_date;
}
