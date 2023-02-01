#include "mainwidget.h"
#include "static.h"



MainWidget::MainWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    //x_pos=y_pos=angle_x=angle_y=0;
}

MainWidget::~MainWidget()
{

}

void MainWidget::initializeGL()
{
    glClearColor(red_bg, green_bg, blue_bg, 0);
    glEnable(GL_DEPTH_TEST);
}

void MainWidget::resizeGL(int nWidth, int nHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, nWidth, nHeight);
    //gluPerspective(30.0, nWidth/nHeight, 2.0, 10.0);

    if (parallel) {
        glOrtho(-elements.max_value, elements.max_value, -elements.max_value*9/16, elements.max_value*9/16, -elements.max_value, elements.max_value);
    }
    if (central) {
        float fov = 60.0 * M_PI / 180;  // 60 угол в градусах
        float heapHeight = elements.max_value/2 / (2 * tan(fov / 2));
        glFrustum(-elements.max_value*16/9/4, elements.max_value*16/9/4, -elements.max_value/4, elements.max_value/4, heapHeight, elements.max_value*5);
        glTranslated(0, 0, -heapHeight * 4);
    }

}

void MainWidget::paintGL() {
   // (double)vertexx[0] = 20;
    if (elements.index == NULL || elements.vertex == NULL || elements.index_counter < 1 || elements.vertex_counter < 1) {
        glClearColor(red_bg, green_bg, blue_bg, 0);
        glClear(GL_COLOR_BUFFER_BIT);
    } else {
        if (!start) {
            //initializeGL();
            resizeGL(elements.max_value, elements.max_value);
            start = true;
            update();
        }

        //elements.max_value = 0;
        //Elements elements;
        //myMain(&elements);
        glClearColor(red_bg, green_bg, blue_bg, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(angle_x, 1, 0, 0);
    glRotatef(angle_y, 0, 1, 0);


    glVertexPointer(3, GL_DOUBLE, 0, elements.vertex);



    glEnableClientState(GL_VERTEX_ARRAY);

    int edges_counter = elements.index_counter*2;
    glColor3d(red, green, blue);
    if (striple_line) {
        glLineStipple(elements.max_value*20, 0x3333);
        glEnable(GL_LINE_STIPPLE);
    } else {
        glDisable(GL_LINE_STIPPLE);
    }
    glLineWidth(lineWidth);
    glDrawElements(GL_LINES, edges_counter, GL_UNSIGNED_INT, elements.index);
    //glRotatef(30, 0, 1, 0);
    //glRotatef(30, 1, 0, 0);
    if (point_type != 1) {
        int type = 0;
        if (point_type == 2) {
            type = GL_POINT_SMOOTH;
        } else {
            type = GL_POINT;
        }
        glEnable(type);
        glColor3d(red_point, green_point, blue_point);
        glPointSize(point_size);
        glDrawArrays(GL_POINTS, 0, elements.vertex_counter);
        glDisable(type);
    }
    glDisableClientState(GL_VERTEX_ARRAY);


    //free(vertexx);
    //free(indexx);

}
}

void MainWidget::mousePressEvent(QMouseEvent *e) {
    if (e->button()==Qt::LeftButton) {
        x_pos = e->x();
        y_pos = e->y();
    }
}


void MainWidget::mouseMoveEvent(QMouseEvent *e) {
    angle_x += 180*(GLfloat(e->y()) - y_pos)/width();
    angle_y += 180*(GLfloat(e->x()) - x_pos)/height();
    x_pos = e->x();
    y_pos = e->y();
    update();
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    //QMessageBox::information(0,"fds",QString::number(angle_x));
    //RotationC(&elements, angle_x/57.3, angle_y/57.3, 0);
}
