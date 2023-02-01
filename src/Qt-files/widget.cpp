#include "widget.h"
#include "ui_widget.h"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <QPalette>
//QGifImage gif(QSize(640, 360));


//extern "C" void myMain(Elements *elements, const char *path);
//extern "C" void RotationC(Elements *elements, double x, double y, double z);

double X = 0.51;
double Y = -1.51;
double Z = 0.51;
double *mas;



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setDisabled();
    loadSettings();
    colorPoint();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(update()));
    connect(ui->rotate, SIGNAL(clicked()), this, SLOT(rotation()));
    connect(ui->scale_b, SIGNAL(clicked()), this, SLOT(scaling()));
    connect(ui->move_b, SIGNAL(clicked()), this, SLOT(moving()));
    connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(setParallel()));
    connect(ui->radioButton_2, SIGNAL(clicked()), this, SLOT(setCentral()));
    connect(ui->redSlider, SIGNAL(valueChanged(int)), this, SLOT(onColorChaged()));
    connect(ui->greenSlider, SIGNAL(valueChanged(int)), this, SLOT(onColorChaged()));
    connect(ui->blueSlider, SIGNAL(valueChanged(int)), this, SLOT(onColorChaged()));
    connect(ui->bg_color, SIGNAL(clicked()), this, SLOT(bgClick()));
    connect(ui->line_color, SIGNAL(clicked()), this, SLOT(lineClick()));
    connect(ui->line_type, SIGNAL(currentIndexChanged(int)), this, SLOT(lineType()));
    connect(ui->widthSlider, SIGNAL(valueChanged(int)), this, SLOT(lineWidth()));
    connect(ui->point_size_slider, SIGNAL(valueChanged(int)), this, SLOT(sizePoint()));
    connect(ui->no_point, SIGNAL(clicked()), this, SLOT(noPoint()));
    connect(ui->circle_point, SIGNAL(clicked()), this, SLOT(circlePoint()));
    connect(ui->square_point, SIGNAL(clicked()), this, SLOT(squarePoint()));
    connect(ui->point_color_slider, SIGNAL(valueChanged(int)), this, SLOT(colorPoint()));
    connect(ui->point_bright, SIGNAL(valueChanged(int)), this, SLOT(brightPoint()));
    connect(ui->save_image, SIGNAL(clicked()), this, SLOT(saveImage()));
    connect(ui->save_gif, SIGNAL(clicked()), this, SLOT(saveGif()));
    connect(ui->x_rotate, SIGNAL(valueChanged(int)), this, SLOT(rotationSlider()));
    connect(ui->y_rotate, SIGNAL(valueChanged(int)), this, SLOT(rotationSlider()));
    connect(ui->z_rotate, SIGNAL(valueChanged(int)), this, SLOT(rotationSlider()));
    connect(ui->scale_slider, SIGNAL(valueChanged(int)), this, SLOT(scalingSlider()));
    connect(ui->x_move_slider, SIGNAL(valueChanged(int)), this, SLOT(movingSlider()));
    connect(ui->y_move_slider, SIGNAL(valueChanged(int)), this, SLOT(movingSlider()));
    connect(ui->z_move_slider, SIGNAL(valueChanged(int)), this, SLOT(movingSlider()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::loadSettings(){
    QString dir_path = QApplication::applicationDirPath();
    QSettings settings (dir_path + "/../../../settings.ini",QSettings::IniFormat);

    settings.beginGroup("Settings");
    ui->openGLWidget->red = settings.value("red", 1.0).toDouble();
    ui->openGLWidget->green = settings.value("green", 1.0).toDouble();
    ui->openGLWidget->blue = settings.value("blue", 1.0).toDouble();

    ui->redSlider->setValue(settings.value("red_bg", 0).toDouble()*255);
    ui->greenSlider->setValue(settings.value("green_bg", 0).toDouble()*255);
    ui->blueSlider->setValue(settings.value("blue_bg", 0).toDouble()*255);

    ui->openGLWidget->red_bg = settings.value("red_bg", 0).toDouble();
    ui->openGLWidget->green_bg = settings.value("green_bg", 0).toDouble();
    ui->openGLWidget->blue_bg = settings.value("blue_bg", 0).toDouble();

    ui->openGLWidget->lineWidth = settings.value("line_width", 1).toInt();
    ui->line_type->setCurrentIndex(settings.value("stripple_line", 0).toInt());
    ui->widthSlider->setValue(settings.value("line_width", 1).toInt());
    ui->point_size_slider->setValue(settings.value("size_point", 0).toInt());
    ui->openGLWidget->point_size = settings.value("size_point", 0).toInt();

    ui->point_color_slider->setValue(settings.value("point_color", 255).toInt());
    ui->point_bright->setValue(settings.value("point_bright", 0).toInt());
    if (settings.value("proect_type", 1).toInt() == 1) {
        ui->radioButton->setChecked(true);
    } else {
        ui->radioButton_2->setChecked(true);
    }
    if (settings.value("point", 1).toInt() == 1) {
        ui->no_point->setChecked(true);
    } else if (settings.value("point", 1).toInt() == 2) {
        ui->circle_point->setChecked(true);
    } else {
        ui->square_point->setChecked(true);
    }
    settings.endGroup();
}

void Widget::setDisabled(){
    ui->line_type->addItem("Сплошная", QVariant(1));
    ui->line_type->addItem("Пунктирная", QVariant(2));
    ui->line_type->setDisabled(true);
    ui->radioButton->setChecked(true);
    ui->line_color->setDisabled(true);
    ui->bg_color->setChecked(true);
    ui->no_point->setChecked(true);
    ui->no_point->setDisabled(true);
    ui->circle_point->setDisabled(true);
    ui->square_point->setDisabled(true);
    ui->point_size_slider->setDisabled(true);
    ui->widthSlider->setDisabled(true);
    ui->point_size_slider->setDisabled(true);
    ui->point_color_slider->setDisabled(true);
    ui->point_bright->setDisabled(true);
    ui->x_Axis->setDisabled(true);
    ui->y_Axis->setDisabled(true);
    ui->z_Axis->setDisabled(true);
    ui->rotate->setDisabled(true);
    ui->save_gif->setDisabled(true);
    ui->save_image->setDisabled(true);
    ui->scale->setDisabled(true);
    ui->scale_b->setDisabled(true);
    ui->scale_slider->setDisabled(true);
    ui->x_move_slider->setDisabled(true);
    ui->y_move_slider->setDisabled(true);
    ui->z_move_slider->setDisabled(true);
    ui->x_move->setDisabled(true);
    ui->y_move->setDisabled(true);
    ui->z_move->setDisabled(true);
    ui->move_b->setDisabled(true);
    ui->x_rotate->setDisabled(true);
    ui->y_rotate->setDisabled(true);
    ui->z_rotate->setDisabled(true);
}

void Widget::setEnabled(){
    ui->line_color->setDisabled(false);
    ui->no_point->setDisabled(false);
    ui->circle_point->setDisabled(false);
    ui->square_point->setDisabled(false);
    ui->point_size_slider->setDisabled(false);
    ui->widthSlider->setDisabled(false);
    ui->point_size_slider->setDisabled(false);
    ui->point_color_slider->setDisabled(false);
    ui->point_bright->setDisabled(false);
    ui->x_Axis->setDisabled(false);
    ui->y_Axis->setDisabled(false);
    ui->z_Axis->setDisabled(false);
    ui->rotate->setDisabled(false);
    ui->save_gif->setDisabled(false);
    ui->save_image->setDisabled(false);
    ui->scale->setDisabled(false);
    ui->scale_b->setDisabled(false);
    ui->scale_slider->setDisabled(false);
    ui->x_move_slider->setDisabled(false);
    ui->y_move_slider->setDisabled(false);
    ui->z_move_slider->setDisabled(false);
    ui->x_move->setDisabled(false);
    ui->y_move->setDisabled(false);
    ui->z_move->setDisabled(false);
    ui->move_b->setDisabled(false);
    ui->x_rotate->setDisabled(false);
    ui->y_rotate->setDisabled(false);
    ui->z_rotate->setDisabled(false);
    ui->line_type->setDisabled(false);
}

void Widget::refresh()
{
    gif_counter = 0;
    old_x = 0;
    old_y = 0;
    old_z = 0;
    old_scale = 0;
    old_x_move = 0;
    old_y_move = 0;
    old_z_move = 0;
    ui->x_Axis->setValue(0);
    ui->y_Axis->setValue(0);
    ui->z_Axis->setValue(0);
    ui->x_rotate->setValue(0);
    ui->y_rotate->setValue(0);
    ui->z_rotate->setValue(0);
    ui->scale->setValue(0);
    ui->scale_slider->setValue(0);
    ui->x_move->setValue(0);
    ui->y_move->setValue(0);
    ui->z_move->setValue(0);
    ui->x_move_slider->setValue(0);
    ui->y_move_slider->setValue(0);
    ui->z_move_slider->setValue(0);
    ui->openGLWidget->x_pos = 0;
    ui->openGLWidget->y_pos = 0;
    ui->openGLWidget->angle_x = 0;
    ui->openGLWidget->angle_y = 0;
}

void Widget::update()
{
    QDir dir(".");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QApplication::applicationDirPath()+"../../../../../Models",
                                                      tr("Objects (*.obj)"));
    QFile f(fileName);
    QFileInfo fileInfo(f.fileName());
    QString name_of_file(fileInfo.fileName());
    QByteArray ba = fileName.toLocal8Bit();
    const char *path = ba.data();
    if (strlen(path) != 0) {
    refresh();
    myMain(&elements, path);
    ui->lineEdit->setText(fileName);
    this->setWindowTitle(name_of_file);
    if (ui->radioButton->isChecked()) {
        ui->openGLWidget->parallel = true;
        ui->openGLWidget->central = false;
    } else {
        ui->openGLWidget->central = true;
        ui->openGLWidget->parallel = false;
    }
    int line = ui->line_type->currentData().toInt();
    if (line == 2) {
        ui->openGLWidget->striple_line = true;
    } else {
        ui->openGLWidget->striple_line = false;
    }
    if (ui->circle_point->isChecked()) {
        ui->openGLWidget->point_type = 2;
    } else if (ui->square_point->isChecked()) {
        ui->openGLWidget->point_type = 3;
    } else {
        ui->openGLWidget->point_type = 1;
    }
    setElements();
    setSliderValues();
    QString str = "Vertexes: ";
    
    str += QString::number(elements.vertex_counter);
    str += "\n";
    str += "Edges: ";
    str += QString::number(elements.index_counter);
    ui->vertex_edge->setText(str);
    
    ui->openGLWidget->update();
    setEnabled();
    ui->openGLWidget->start = false;
}


}

void Widget::setElements(){
    ui->openGLWidget->elements.index_counter = elements.index_counter;
    ui->openGLWidget->elements.vertex_counter = elements.vertex_counter;
    ui->openGLWidget->elements.index = new int[elements.index_counter*2];
    ui->openGLWidget->elements.vertex = new double[elements.vertex_counter*3];
    for (int i = 0; i < elements.index_counter*2; i++) {
        ui->openGLWidget->elements.index[i] = elements.index[i];
    }
    for (int i  = 0; i < elements.vertex_counter*3; i++) {
        ui->openGLWidget->elements.vertex[i] = elements.vertex[i];
    }
    ui->openGLWidget->elements.max_value = elements.max_value * 2;
    ui->vertex_edge->setText(QString::number(elements.vertex[1]));
}
void Widget::setSliderValues(){
    ui->x_move_slider->setMaximum(ui->openGLWidget->elements.max_value*1000);
    ui->x_move_slider->setMinimum(-ui->openGLWidget->elements.max_value*1000);
    ui->y_move_slider->setMaximum(ui->openGLWidget->elements.max_value*1000);
    ui->y_move_slider->setMinimum(-ui->openGLWidget->elements.max_value*1000);
    ui->z_move_slider->setMaximum(ui->openGLWidget->elements.max_value*1000);
    ui->z_move_slider->setMinimum(-ui->openGLWidget->elements.max_value*1000);
    ui->x_move->setSingleStep(ui->openGLWidget->elements.max_value/10);
    ui->y_move->setSingleStep(ui->openGLWidget->elements.max_value/10);
    ui->z_move->setSingleStep(ui->openGLWidget->elements.max_value/10);
}

void Widget::rotation()
{
    double x = ui->x_Axis->value()/57.3;
    double y = ui->y_Axis->value()/57.3;
    double z = ui->z_Axis->value()/57.3;
    RotationC(&ui->openGLWidget->elements, x, y, z);
    ui->openGLWidget->update();
    if (!ui->save_gif->isEnabled()) {
        recordGif();
    }
}

void Widget::rotationSlider()
{
    double x = (ui->x_rotate->value() - old_x)/57.3;
    double y = (ui->y_rotate->value() - old_y)/57.3;
    double z = (ui->z_rotate->value() - old_z)/57.3;
    RotationC(&ui->openGLWidget->elements, x, y, z);
    ui->openGLWidget->update();
    if (!ui->save_gif->isEnabled()) {
        recordGif();
    }
    old_x = ui->x_rotate->value();
    old_y = ui->y_rotate->value();
    old_z = ui->z_rotate->value();
}

void Widget::scalingSlider()
{
    double scaler = (double)(ui->scale_slider->value())/100 + 1.;
    double scaler_old = (double)(old_scale + old_scaler)/100 + 1.;
    ScalingC(&ui->openGLWidget->elements, scaler/scaler_old);
    ui->openGLWidget->update();
    old_scale = ui->scale_slider->value();
    if (!ui->save_gif->isEnabled()) {
        recordGif();
    }
}


void Widget::scaling()
{
    double scaler = (double)ui->scale->value()/100 + 1.;
    ScalingC(&ui->openGLWidget->elements, scaler);
    ui->openGLWidget->update();
    if (!ui->save_gif->isEnabled()) {
        recordGif();
    }

    old_scaler +=  (double)ui->scale->value()/100;
}

void Widget::moving()
{
    double x = ui->x_move->value();
    double y = ui->y_move->value();
    double z = ui->z_move->value();
    MovingC(&ui->openGLWidget->elements, x, y, z);
    ui->openGLWidget->update();
    if (!ui->save_gif->isEnabled()) {
        recordGif();
    }
}

void Widget::movingSlider()
{
    double x = ((double)ui->x_move_slider->value() - old_x_move)/1000.;
    double y = ((double)ui->y_move_slider->value() - old_y_move)/1000.;
    double z = ((double)ui->z_move_slider->value() - old_z_move)/1000.;

    MovingC(&ui->openGLWidget->elements, x, y, z);
    ui->openGLWidget->update();
    if (!ui->save_gif->isEnabled()) {
        recordGif();
    }
    old_x_move = ui->x_move_slider->value();
    old_y_move = ui->y_move_slider->value();
    old_z_move = ui->z_move_slider->value();

}

void Widget::setParallel()
{
    ui->openGLWidget->parallel = true;
    ui->openGLWidget->central = false;
    ui->openGLWidget->start = false;
    saveSettings();
    ui->openGLWidget->update();
}

void Widget::setCentral()
{
    ui->openGLWidget->parallel = false;
    ui->openGLWidget->central = true;
    ui->openGLWidget->start = false;
    saveSettings();
    ui->openGLWidget->update();
}

void Widget::onColorChaged()
{
    if (ui->bg_color->isChecked()) {
    ui->openGLWidget->red_bg = (float)ui->redSlider->value()/255.;
    ui->openGLWidget->green_bg = (float)ui->greenSlider->value()/255.;
    ui->openGLWidget->blue_bg = (float)ui->blueSlider->value()/255.;
    } else {
        ui->openGLWidget->red = (float)ui->redSlider->value()/255.;
        ui->openGLWidget->green = (float)ui->greenSlider->value()/255.;
        ui->openGLWidget->blue = (float)ui->blueSlider->value()/255.;
    }
    saveSettings();
    ui->openGLWidget->update();
}

void Widget::bgClick()
{
    int red = ui->openGLWidget->red_bg*255;
    int green = ui->openGLWidget->green_bg*255;
    int blue = ui->openGLWidget->blue_bg*255;
    ui->redSlider->setValue(red);
    ui->greenSlider->setValue(green);
    ui->blueSlider->setValue(blue);
}

void Widget::lineClick()
{
    int red = ui->openGLWidget->red*255;
    int green = ui->openGLWidget->green*255;
    int blue = ui->openGLWidget->blue*255;
    ui->redSlider->setValue(red);
    ui->greenSlider->setValue(green);
    ui->blueSlider->setValue(blue);
}

void Widget::lineType()
{
    int line = ui->line_type->currentData().toInt();
    if (line == 2) {
        ui->openGLWidget->striple_line = true;
    } else {
        ui->openGLWidget->striple_line = false;
        //ui->label->setText("Pudge");
    }
    saveSettings();
    ui->openGLWidget->update();
}

void Widget::lineWidth()
{
    ui->openGLWidget->lineWidth = ui->widthSlider->value();
    saveSettings();
    ui->openGLWidget->update();
}

void Widget::saveSettings()
{
    QString dir_path = QApplication::applicationDirPath();
    QSettings settings(dir_path + "/../../../settings.ini",QSettings::IniFormat);
    settings.beginGroup("Settings");
    settings.setValue( "red", ui->openGLWidget->red);
    settings.setValue("green",ui->openGLWidget->green);
    settings.setValue("blue",ui->openGLWidget->blue);
    settings.setValue( "red_bg", ui->openGLWidget->red_bg);
    settings.setValue("green_bg",ui->openGLWidget->green_bg);
    settings.setValue("blue_bg",ui->openGLWidget->blue_bg);
    settings.setValue("line_width",ui->openGLWidget->lineWidth);
    settings.setValue("stripple_line",ui->line_type->currentIndex());
    settings.setValue("size_point",ui->point_size_slider->value());
    settings.setValue("point_color",ui->point_color_slider->value());
    settings.setValue("point_bright",ui->point_bright->value());
    if (ui->radioButton->isChecked()) {
        settings.setValue("proect_type", 1);
    } else {
        settings.setValue("proect_type", 2);
    }
    if (ui->no_point->isChecked()) {
        settings.setValue("point", 1);
    } else if (ui->circle_point->isChecked()) {
        settings.setValue("point", 2);
    } else {
        settings.setValue("point", 3);
    }
    settings.endGroup();
}

void Widget::noPoint()
{
    ui->openGLWidget->point_type = 1;
    saveSettings();
    ui->openGLWidget->update();
}

void Widget::circlePoint()
{
    ui->openGLWidget->point_type = 2;
    saveSettings();
    ui->openGLWidget->update();
}

void Widget::squarePoint()
{
    ui->openGLWidget->point_type = 3;
    saveSettings();
    ui->openGLWidget->update();
}

void Widget::sizePoint()
{
    ui->openGLWidget->point_size = ui->point_size_slider->value();
    saveSettings();
    ui->openGLWidget->update();
}

void Widget::colorPoint()
{
    float new_value = 0.0;
    if (ui->point_color_slider->value() >= 255 && ui->point_color_slider->value() < 510) {
        ui->openGLWidget->red_point = 1.0;
        new_value = (float)ui->point_color_slider->value() - 255;
        ui->openGLWidget->green_point =  new_value/255;
        ui->openGLWidget->blue_point = 0.0;
    } else if (ui->point_color_slider->value() >= 510 && ui->point_color_slider->value() < 765) {
        new_value = (float)ui->point_color_slider->value() - 510.;
        ui->openGLWidget->red_point = 1.0 - new_value/255.;
        ui->openGLWidget->green_point = 1.0;
        ui->openGLWidget->blue_point = 0;
    } else if (ui->point_color_slider->value() >= 765 && ui->point_color_slider->value() < 1020) {
        new_value = (float)ui->point_color_slider->value() - 765.;
        ui->openGLWidget->red_point = 0.0;
        ui->openGLWidget->green_point = 1.0;
        ui->openGLWidget->blue_point = new_value/255.;
    } else if (ui->point_color_slider->value() >= 1020 && ui->point_color_slider->value() < 1275) {
        new_value = (float)ui->point_color_slider->value() - 1020.;
        ui->openGLWidget->red_point = 0;
        ui->openGLWidget->green_point = 1.0 - new_value/255.;
        ui->openGLWidget->blue_point = 1.0;
    } else if (ui->point_color_slider->value() >= 1275 && ui->point_color_slider->value() < 1530){
        new_value = (float)ui->point_color_slider->value() - 1275.;
        ui->openGLWidget->red_point = new_value/255.;
        ui->openGLWidget->green_point = 0.0;
        ui->openGLWidget->blue_point = 1.0;
    } else if (ui->point_color_slider->value() >= 1530 && ui->point_color_slider->value() < 1785) {
        new_value = (float)ui->point_color_slider->value() - 1530.;
        ui->openGLWidget->red_point = 1.0;
        ui->openGLWidget->green_point = 0;
        ui->openGLWidget->blue_point = 1.0 - new_value/255.;
    }
    ui->openGLWidget->red_point_remember = ui->openGLWidget->red_point;
    ui->openGLWidget->green_point_remember = ui->openGLWidget->green_point;
    ui->openGLWidget->blue_point_remember = ui->openGLWidget->blue_point;
    brightPoint();
    saveSettings();
    ui->openGLWidget->update();
}

void Widget::brightPoint()
{
    if (ui->point_bright->value() >= 0) {
        ui->openGLWidget->red_point = ui->openGLWidget->red_point_remember + (1.0 - ui->openGLWidget->red_point_remember)*(1. - (1. - (float)ui->point_bright->value()/100));
        ui->openGLWidget->green_point = ui->openGLWidget->green_point_remember + (1.0 - ui->openGLWidget->green_point_remember)*(1. - (1. - (float)ui->point_bright->value()/100));
        ui->openGLWidget->blue_point = ui->openGLWidget->blue_point_remember + (1.0 - ui->openGLWidget->blue_point_remember)*(1. - (1. - (float)ui->point_bright->value()/100));
    } else {
        ui->openGLWidget->red_point = ui->openGLWidget->red_point_remember - ui->openGLWidget->red_point_remember*(1. - (1. + (float)ui->point_bright->value()/100));
        ui->openGLWidget->green_point = ui->openGLWidget->green_point_remember - ui->openGLWidget->green_point_remember*(1. - (1. + (float)ui->point_bright->value()/100));
        ui->openGLWidget->blue_point = ui->openGLWidget->blue_point_remember - ui->openGLWidget->blue_point_remember*(1. - (1. + (float)ui->point_bright->value()/100));
    }
    saveSettings();
    ui->openGLWidget->update();
}

void Widget::saveImage()
{
    QString file = QFileDialog::getSaveFileName(this, "Save as...",
                                                QApplication::applicationDirPath()+"../../../../../Images", "BMP (*.bmp);; JPEG (*.jpeg)");
    ui->openGLWidget->grabFramebuffer().save(file, NULL, 100);
}

void Widget::saveGif()
{
    gif = new QGifImage;
    ui->save_gif->setDisabled(true);
    QString str = "Frames to save: ";
    str += QString::number(50 - gif_counter);
    ui->gif_record->setText(str);
}

void Widget::recordGif()
{
    gif->setDefaultDelay(100);

    QImage image = ui->openGLWidget->grabFramebuffer().scaled(640, 360);

    //image.fill(QColor(Qt::black));
    //QPainter p(&image);
    //p.setPen(Qt::red);
    //p.drawText(15, 15, "Qt");
    //p.drawRect(20, 20, 60, 60);
    gif_counter++;
    QString str = "Frames to save: ";
    str += QString::number(50 - gif_counter);
    ui->gif_record->setText(str);
    gif->addFrame(image, QPoint(0, 0));
    if (gif_counter == 50) {
        QString dir_path = QApplication::applicationDirPath();
        gif->save(dir_path + "/../../../../Images/demo.gif");
        ui->save_gif->setDisabled(false);
        gif_counter = 0;
        str = "Gif saved";
        ui->gif_record->setText(str);
    }
}

