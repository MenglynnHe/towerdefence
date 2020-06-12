#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include"scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);





private:
    Ui::MainWindow *ui;
    ChoiceScene * choices=nullptr;
public slots:
   void choice();//选择关卡
};

#endif // MAINWINDOW_H
