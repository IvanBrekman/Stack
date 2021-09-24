//
// Created by ivanbrekman on 22.09.2021.
//

#include <malloc.h>
#include <string.h>

char* colored(const char* text, const char* color) {
    char right[] = "\033[0m";

    char* colored_str = (char*)calloc(strlen(color) + strlen(text) + strlen(right) + 1, sizeof(char));
    strcat(colored_str, color);
    strcat(colored_str, text);
    strcat(colored_str, right);

    return colored_str;
}
