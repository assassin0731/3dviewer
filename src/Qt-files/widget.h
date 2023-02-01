#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QColor>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QFileDialog>
#include <gl.h>
#include <glu.h>
#include "static.h"
#include "qgifimage.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    int gif_counter = 0;
    QGifImage *gif;
    void recordGif();
    int old_x = 0;
    int old_y = 0;
    int old_z = 0;
    double old_scale = 0;
    double old_scaler = 0;
    Elements elements = {NULL, NULL, 0, 0, 0};
    int old_x_move = 0;
    int old_y_move = 0;
    int old_z_move = 0;
    void refresh();
    void setDisabled();
    void setEnabled();
    void loadSettings();
    void setElements();
    void setSliderValues();



private:
    Ui::Widget *ui;

public slots:
    void update();
    void rotation();
    void scaling();
    void moving();
    void setParallel();
    void setCentral();
    void onColorChaged();
    void bgClick();
    void lineClick();
    void lineType();
    void lineWidth();
    void saveSettings();
    void noPoint();
    void circlePoint();
    void squarePoint();
    void sizePoint();
    void colorPoint();
    void brightPoint();
    void saveImage();
    void saveGif();
    void rotationSlider();
    void scalingSlider();
    void movingSlider();


};
#endif // WIDGET_H
