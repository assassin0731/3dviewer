#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include "myMain.h"


void myMain(Elements *elements, const char *path) {
    setlocale(LC_ALL, "en-US");
    setlocale(LC_NUMERIC, "C");
    ElementCounter(path, elements);
    parser(path, elements);
}

void ElementCounter(const char *file_name, Elements *elements) {
    FILE *f;
    char read;
    f = fopen(file_name, "r");
    char *line = NULL;
    size_t len = 0;
    elements->vertex_counter= 0;
    elements->index_counter = 0;
    elements->max_value = 0;
    if (f != NULL) {
    while ((read = getline(&line, &len, f)) != EOF) {
        if (line[0] == 'v' && line[1] == ' ') {
            elements->vertex_counter++;
        }
        if (line[0] == 'f') {
            char sep [10] = " ";
            char *istr;
            istr = strtok(line,sep);
            while (istr != NULL) {
                if (*istr >= '0' && *istr <= '9') {
                    elements->index_counter++;
                }
                istr = strtok (NULL,sep);
            }
        }
    }
        free(line);
}
    fclose(f);
}

void parser(const char *file_name, Elements *elements) {
    FILE *f;
    char read;
    f = fopen(file_name, "r");
    //elements->max_value = 0;
    if (f != NULL) {
        
    char *line = NULL;
    size_t len = 0;
    elements->vertex = malloc(elements->vertex_counter*3*sizeof(double));
    elements->index = malloc(elements->index_counter*2*sizeof(int));
        if (elements->vertex != NULL && elements->index != NULL) {
    int i = 0, j = 0;
    while ((read = getline(&line, &len, f)) != EOF) {
        if (line[0] == 'v' && line[1] == ' ') {
            char str[3];
            sscanf(line, "%s %lf %lf %lf", str, &elements->vertex[i], &elements->vertex[i+1], &elements->vertex[i+2]);
            if (fabs(elements->vertex[i]) > elements->max_value) {
                elements->max_value = fabs(elements->vertex[i]);
            }
            if (fabs(elements->vertex[i+1]) > elements->max_value) {
                elements->max_value = fabs(elements->vertex[i+1]);
            }
            if (fabs(elements->vertex[i+2]) > elements->max_value) {
                elements->max_value = fabs(elements->vertex[i+2]);
            }
            i += 3;
        }
        if (line[0] == 'f') {
            char sep [10] = " ";
            char *istr;
            int first = -1;
            istr = strtok(line,sep);
            while (istr != NULL) {
                if (*istr >= '0' && *istr <= '9') {
                    sscanf(istr, "%d", &elements->index[j]);
                    elements->index[j]--;
                    j++;
                    if (first == -1) {
                        first = elements->index[j-1];
                    } else {
                        sscanf(istr, "%d", &elements->index[j]);
                        elements->index[j]--;
                        j++;
                    }
                }
                istr = strtok (NULL,sep);
            }
            if (first != -1) {
            elements->index[j] = first;
            j++;
            }
        }
    }
            free(line);
    }
    }
    fclose(f);
}

void RotationC(Elements *elements, double x, double y, double z) {
    for (int i = 0; i < elements->vertex_counter*3; i += 3) {
        double temp_y = elements->vertex[i+1];
        double temp_z = elements->vertex[i+2];
        elements->vertex[i+1] = cos(x) * temp_y - sin(x) * temp_z;
        elements->vertex[i+2] = sin(x) * temp_y + cos(x) * temp_z;
    }
    for (int i = 0; i < elements->vertex_counter*3; i += 3) {
        double temp_x = elements->vertex[i];
        double temp_z = elements->vertex[i+2];
        elements->vertex[i] = cos(y) * temp_x - sin(y) * temp_z;
        elements->vertex[i+2] = sin(y) * temp_x + cos(y) * temp_z;
    }
    for (int i = 0; i < elements->vertex_counter*3; i += 3) {
        double temp_x = elements->vertex[i];
        double temp_y = elements->vertex[i+1];
        elements->vertex[i] = cos(z) * temp_x - sin(z) * temp_y;
        elements->vertex[i+1] = sin(z) * temp_x + cos(z) * temp_y;
    }
}

void ScalingC(Elements *elements, double scaler) {
    for (int i = 0; i < elements->vertex_counter*3; i++) {
        elements->vertex[i] = elements->vertex[i]*scaler;
    }
}

void MovingC(Elements *elements, double x, double y, double z) {
    for (int i = 0; i < elements->vertex_counter*3; i+=3) {
        elements->vertex[i] = elements->vertex[i] + x;
        elements->vertex[i+1] = elements->vertex[i+1] + y;
        elements->vertex[i+2] = elements->vertex[i+2] + z;
    }
}
