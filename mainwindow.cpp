#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QIcon"
#include "QPainter"
#include "mypushbutton.h"
#include "QTimer"
#include "enemy.h"
#include "QSound"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/thing/picture/logo.jpg"));//设置游戏图标
    this->setWindowTitle("Tower Defense 1.0");  //设置游戏标题
     this->setMouseTracking(true);                 //track mouse when mouse isn`t pressed
    this->setFixedSize(1200, 639);//固定窗口
    //退出
//    connect(ui->actionquit,&QAction::triggered,[=](){
//        this->close()});
    mainsound->setLoops(-1);
    mainsound->play();


    MyPushButton *startbtn=new MyPushButton(":/thing/picture/btnplay.png");
    startbtn->setParent(this);//放在当前窗口下
    startbtn->move(470,454);

    connect(startbtn,&MyPushButton::clicked,[=](){
        //弹跳特效
    startbtn->upbounce();
    startbtn->downbounce();
    //延时500秒触发
    QTimer::singleShot(500,this,[=](){
       // choice();
        choices= new ChoiceScene(this);
        mainsound->stop();
        connect(this->choices, SIGNAL(toTitle()), this, SLOT(back()));
    });

    });


}

void MainWindow::onTimer(){
    emit toTitle();
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/thing/picture/map1.jpg");
    painter.drawPixmap(0,0,/*this->width(),this->height(),*/pix);//慎用图片铺平
    pix.load(":/thing/picture/title.png");
    painter.drawPixmap(0,0,pix);



}

MainWindow::~MainWindow()
{
    delete ui;
    delete choices;
}

void MainWindow:: choice(){
//    if (choices)
//    {
//        delete choices;
//        choices = nullptr;
//    }
    choices= new ChoiceScene(this);
    connect(this->choices, SIGNAL(toTitle()), this, SLOT(back()));

}

void MainWindow::back()
{   qDebug()<<"back"<<endl;
    this->setFixedSize(1200, 639);
    if (scene)
    {//  qDebug()<<"back1"<<endl;
        delete scene;
     //   qDebug()<<"back2"<<endl;
        scene = nullptr;
     //   qDebug()<<"back3"<<endl;
    }
    qDebug()<<"back4"<<endl;
    if (choices)//choices是选择界面
    {
        delete choices;
        choices = nullptr;

    }

//    choices = new ChoiceScene(this);
    this->show();
    mainsound->play();
 //   connect(this->choices, SIGNAL(toCanyon()), this, SLOT(playCanyon()));
    qDebug()<<"!!"<<endl;
 //   connect(this->choices, SIGNAL(toPolar()), this, SLOT(playPolar()));
}
void MainWindow::playPolar(){

    if (choices)
    {
        delete choices;
        choices = nullptr;
    }
    //remember to delete !!!
    scene= new Scene(this);
    connect(this->scene, SIGNAL(toTitle()), this, SLOT(back()));
}
void MainWindow::playCanyon(){
    if (choices)
    {
        delete choices;
        choices = nullptr;
    }
    //remember to delete !!!
     scene= new CanyonScene(this);
    connect(this->scene, SIGNAL(toTitle()), this, SLOT(back()));

}
