#ifndef MAIN_H
#define MAIN_H

typedef struct Struct {
    double *vertex;
    int *index;
    int vertex_counter;
    int index_counter;
    double max_value;
}Elements;

void ElementCounter(const char *file_name, Elements *elements);
void parser(const char *file_name, Elements *elements);
void myMain(Elements *elements, const char *path);
void RotationC(Elements *elements, double x, double y, double z);
void ScalingC(Elements *elements, double scaler);
void MovingC(Elements *elements, double x, double y, double z);

#endif // MAIN_H
