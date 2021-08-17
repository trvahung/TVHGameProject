// Lesson4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include "Door.h"

using namespace Door;

int main()
{
    printf("Press l to lock/close\n");
    printf("Press o to close/open\n");
    printf("Press x to exit\n");
    printf("\n-----------START-------------\n");
    Context* context = new Context(new LockedState);
    context->DoorState();
    char key='a';
    while (key!='x')
    {
        key = getchar();
        context->Control(key);
        if (key != '\n') {
            context->DoorState();
        }
    }
}