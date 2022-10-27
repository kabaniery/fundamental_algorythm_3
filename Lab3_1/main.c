#include <stdio.h>
#include <stdlib.h>

int copyString(char* string1, char* string2, int startFirst, int startSecond, int sizeFirst) {
    for (int i = 0; i < sizeFirst; ++i) {
        string2[i+startSecond] = string1[i+startFirst];
    }
    return 0;
}

int convert(int value, int stepen, char** result) {
    if (stepen > 5 || stepen < 1) {
        fprintf(stderr, "Choosen degree isn't valid");
        *result = NULL;
        return -1;
    }
    *result = (char*)malloc(sizeof(char)*2);
    char *temp;
    if (!*result) {
        fprintf(stderr, "Can't get memory for result");
        return -1;
    }
    (*result)[1] = '\0';
    int isNegative = 0, index = 0, size = 2, tempI;
    if (value < 0) {
        value *= -1;
        isNegative = 1;
    }
    if (value == 0) {
        (*result)[0] = '0';
        return 0;
    }
    while (value != 0) {
        if (index == -1) {
            // тут realloc бы лучше юзал, ну да ладно, работает - не трогай (=
            temp = (char *) malloc(sizeof(char) * size * 2);
            if (!temp) {
                fprintf(stderr, "Can't get memory");
                // тут же память выделенная лежит, надо почистить вилкой (=
                free(*result);
                *result = NULL;
                return -1;
            }
            copyString(*result, temp, 0, size, size);
            index = size - 1;
            size *= 2;
            free(*result);
            *result = temp;
        }
        tempI = 0;
        for (int i = 0; i < stepen; ++i) {
            tempI = tempI | ((value & 1) << i);
            value = value >> 1;
        }
        if (tempI < 10) {
            (*result)[index] = '0' + tempI;
        } else {
            (*result)[index] = 'A' + tempI - 10;
        }
        index--;
    }
    if (isNegative == 1) {
        if (index < 0) {
            temp = malloc(sizeof(char)*(size+1));
            copyString(*result, temp, 0, 1, size);
            temp[0] = '-';
            free(*result);
            *result = temp;

        } else {
            (*result)[index] = '-';
            index--;
        }
    }
    if (index < 0) {
        return 0;
    } else {
        temp = malloc(sizeof(char)*(size-1-index));
        // TODO: check if temp is NULL
        if (!temp) {
            fprintf(stderr, "Can't get memory");
            free(*result);
            *result = NULL;
            return -1;
        }
        copyString(*result, temp, index+1, 0, size-1-index);
        //printf("%s %s\n", temp, *result);
        free(*result);
        *result = temp;
        //free(result);
        return 0;
    }
}

int main() {
    char* result;
    convert(65537, 5, &result);
    printf("%s\n", result);
    free(result);
    return 0;
}
