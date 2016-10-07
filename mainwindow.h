#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "grid.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{

    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *event);

public:

    Grid grid, init_grid;
    QGraphicsScene* scene;

    QTimer* timer;
    bool end, edit;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init_random();

public slots:

    void updateTimer();
    void next_step(bool repaint);


private slots:

    void on_init_random_clicked();

    void on_next_step_clicked();

    void on_run_continuous_btn_clicked();

    void on_stop_continuous_btn_clicked();

    void on_int_steps_clicked();

    void on_clear_btn_clicked();

    void on_back_init_btn_clicked();

    void on_edit_mode_btn_toggled(bool checked);


private:

    void setEdit(bool e);
    void repaint();
    void drawGrid();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
