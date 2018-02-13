#include <stdio.h>

int main() {
    char string[] = "hello, world";
    int length = sizeof(string);
    int i, j;
    char temp;
    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = string[i];
        string[i] = string[j];
        string[j] = temp;
    }
    printf("%s\n", string);
    return 0;
}