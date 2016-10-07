#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QMouseEvent>
#include <chrono>
#include <QTimer>
#include <QTimerEvent>
#include <thread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    setEdit (false);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    ui->nb_cell->setValue(10);
    this->setWindowTitle("Life");
}

MainWindow::~MainWindow(){
    delete ui;
    delete scene;
}

void MainWindow::next_step(bool repaint = true){
    if(grid.nb_it == 0){
        init_grid = Grid(grid);
    }
    grid.next_step();
    if(repaint)
        this->repaint();
}
void MainWindow::init_random(){
    end = true;
    grid.init_random(ui->nb_cell->value());
    repaint();
}

void MainWindow::on_init_random_clicked(){
  init_random();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(edit && event->button() == Qt::LeftButton){
        QPointF mousePoint = ui->graphicsView->mapToScene(event->pos());
        if(ui->graphicsView->width() >= mousePoint.x() && mousePoint.x() >= 0 && ui->graphicsView->height() >= mousePoint.y() && mousePoint.y() >=0){
            int x = mousePoint.x()/(ui->graphicsView->width()/SIZE);
            int y = mousePoint.y()/(ui->graphicsView->height()/SIZE);
            grid.states[y][x] ^= 1;
            if(grid.states[y][x]){
                grid.count++;
            }
            else{
                grid.count--;
            }
            repaint();
        }
    }
}


void MainWindow::repaint(){
    scene->clear();
    drawGrid();
    double incw = ui->graphicsView->width()/SIZE,
            inch = ui->graphicsView->height()/SIZE;
    for(int i = 0 ; i < SIZE ; i++){
        for(int j = 0 ; j < SIZE ; j++){
            if(grid.states[i][j] == ON){
                scene->addRect(
                                j*incw+1,
                                i*inch+1,
                                incw,
                                inch,
                                QPen(),
                                QBrush(QColor(200,100,200))
                               );
            }
        }
    }
    ui->lbl_nb_it->setText(QString::number(grid.nb_it));
    ui->nb_cells->setText(QString::number(grid.count));
}

void MainWindow::drawGrid(){
    for(int i = 0 ; i <  ui->graphicsView->width() ; i+= ui->graphicsView->width()/SIZE){
        scene->addLine(i,0,i,ui->graphicsView->height());
    }
    for(int j = 0 ; j <  ui->graphicsView->height() ; j+=ui->graphicsView->height()/SIZE){
        scene->addLine(0,j,ui->graphicsView->width(),j);
    }
}




void MainWindow::on_next_step_clicked(){
    next_step();
}


void MainWindow::updateTimer(){
    if(!end && !grid.stable() && !grid.clean()){
        next_step();
    }
    else{
        timer->stop();
    }
}

void MainWindow::on_run_continuous_btn_clicked(){
    setEdit (false);
    end =false;
    timer->setInterval(ui->time_incr->value() * 500);

    timer->start();
}

void MainWindow::on_stop_continuous_btn_clicked(){
    end = true;
}

void MainWindow::on_int_steps_clicked(){
    setEdit (false);
    for(int i = 0 ; i < ui->step_incr->value() ; i++){
        next_step(false);
    }
    repaint();
}

void MainWindow::on_clear_btn_clicked(){
    end = true;
    grid.clear();
    repaint();
}

void MainWindow::on_back_init_btn_clicked(){
    end = true;
    grid = Grid(init_grid);
    repaint();
}

void MainWindow::setEdit(bool e){
    ui->edit_mode_btn->setChecked(e);
    edit = e;
}

void MainWindow::on_edit_mode_btn_toggled(bool checked)
{
    edit = checked;
}

