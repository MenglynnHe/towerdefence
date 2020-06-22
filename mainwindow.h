#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include"scene.h"
#include"QSound"
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
     ChoiceScene * choices=nullptr;
     BaseScene * scene=nullptr;
     QTimer* timer = nullptr;//@
    //主场景音乐
     QSound *mainsound= new QSound(":/AudioConvert/entry.wav",this);


private:
    Ui::MainWindow *ui;
signals:
    void toTitle();
public slots:
   void choice();//选择关卡
   void back();    // 来到主界面
   void playPolar();//开始游戏
   void playCanyon();
   void onTimer();
};

#endif // MAINWINDOW_H
