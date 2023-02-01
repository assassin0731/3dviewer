#include "myMain.h"
#include <stdio.h>

int main(){
    Elements elements;
    myMain(&elements, "Models/12190_Heart_v1_L3.obj");
    for (int i = 0; i < 8; i++)
    printf("%lf\n", elements.vertex[i]);
    return 0;
}
