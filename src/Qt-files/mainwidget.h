#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#define GL_SILENCE_DEPRECATION
#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <gl.h>
#include <glu.h>
#include <QMouseEvent>
#include <QMessageBox>
#include "static.h"





class MainWidget : public QOpenGLWidget
{
public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    GLfloat y_pos = 0, x_pos = 0;
    GLfloat angle_x = 0, angle_y = 0;
    Elements elements = {NULL, NULL, 0, 0, 0};
    int vertex_counter = -1;
    int index_counter = -1;
    double max_value = -1;
    int *index = NULL;
    int pudge[10] = {0,1,2,3,4,5,6,7,8,9};
    double *vertex = NULL;
    bool start = false;
    bool parallel = true;
    bool central = true;
    float red = 1.0;
    float blue = 1.0;
    float green = 1.0;

    float red_point = 1.0;
    float blue_point = 0.0;
    float green_point = 0.0;

    float red_point_remember = 1.0;
    float blue_point_remember = 0.0;
    float green_point_remember = 0.0;


    float red_bg = 0.0;
    float green_bg = 0.0;
    float blue_bg = 0.0;
    bool striple_line = false;
    int lineWidth = 1;
    int point_size = 0;
    int point_type = 1;
    int bright_point = 0;


};

#endif // MAINWIDGET_H
