//
// Created by ivanbrekman on 22.09.2021.
//

#ifndef STACK_ERRORLIB_H
#define STACK_ERRORLIB_H

#ifndef TYPE
    #define TYPE "void"
#endif

#define dbg(code) do{ printf("%s:%d\n", __FILE__, __LINE__); code }while(0)
#define VALID_PTR(ptr, type) ((ptr) != NULL && (ptr) != (type*)poisons::UNINITIALIZED_PTR && (ptr) != (type*)poisons::FREED_PTR)
#define LOCATION(var) { TYPE, #var, __FILE__, __FUNCTION__, __LINE__ }

#define BLACK       "\033[1;30m"
#define RED         "\033[1;31m"
#define GREEN       "\033[1;32m"
#define ORANGE      "\033[1;33m"
#define BLUE        "\033[1;34m"
#define PURPLE      "\033[1;35m"
#define CYAN        "\033[1;36m"
#define WHITE       "\033[1;37m"

#define BLACK_UNL   "\033[4;30m"
#define RED_UNL     "\033[4;31m"
#define GREEN_UNL   "\033[4;32m"
#define ORANGE_UNL  "\033[4;33m"
#define BLUE_UNL    "\033[4;34m"
#define PURPLE_UNL  "\033[4;35m"
#define CYAN_UNL    "\033[4;36m"
#define WHITE_UNL   "\033[4;37m"

#define NATURAL     "\033[0m"

enum poisons {
    UNINITIALIZED_PTR     =   6,
    UNINITIALIZED_ELEMENT = -14,

    FREED_ELEMENT         = -15,
    FREED_PTR             =  12
};

#include <time.h>

#define PRINT_DATE(color) {                                         \
    char* date = (char*)calloc(40, sizeof(char));                   \
    printf((color "Time: %s\n" NATURAL), datetime(date));           \
    free(date);                                                     \
    date = NULL;                                                    \
};
#define FPRINT_DATE(file) {                                  \
    char* date = (char*)calloc(40, sizeof(char));                   \
    fprintf(file, "Time: %s\n", datetime(date));    \
    free(date);                                                     \
    date = NULL;                                                    \
};

char* datetime(char* calendar_date);

#endif //STACK_ERRORLIB_H
