//
// Created by ivanbrekman on 26.09.2021.
//

#include "errorlib.h"

char* datetime(char* calendar_date) {
    const time_t timer = time(NULL);
    struct tm* calendar = localtime(&timer);

    strftime(calendar_date, 40, "%d.%m.%Y %H:%M:%S, %A", calendar);

    return calendar_date;
}
