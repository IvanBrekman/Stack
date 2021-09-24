//
// Created by ivanbrekman on 22.09.2021.
//

#ifndef STACK_ERRORLIB_H
#define STACK_ERRORLIB_H

#include <string.h>
#include <malloc.h>

#define dbg(code) do{ printf("%s:%d\n", __FILE__, __LINE__); code }while(0) // liberror.h (color)
#define CONCAT3(str1, str2, str3) str1 ## str2 ## str3
#define Colored(text, color) CONCAT3(color, text, "\033[0m")

char* colored(const char* text, const char* color);

#define RED    "\033[1;31m"
#define GREEN  "\033[1;32m"
#define ORANGE "\033[1;33m"
#define BLUE   "\033[1;34m"
#define PURPLE "\033[1;35m"

#endif //STACK_ERRORLIB_H
