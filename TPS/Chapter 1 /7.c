#include <stdio.h>
#include <stdlib.h>

//Using atexit handlers

void handler1() {
    printf("Executing handler 1\n");
    return;
}

void handler2() {
    printf("Executing handler 2\n");
    return;
}

int main() {
    atexit(handler1);
    atexit(handler2);
    // atexit(handler2);

    printf("Main done!\n");

    return 0;
}