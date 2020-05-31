
#include "scene.h"
#include "QPainter"
#include <QXmlStreamReader>
#include "plistreader.h"
#include "QFile"
#include <QMessageBox>
#include <QtGlobal>
#include <QMouseEvent>
#include "QDebug"
#include "QTimer"
#include "copy.h"
#include "enemy.h"

Scene::Scene(QWidget *parent) : QLabel(parent),
    waves(0)
  ,haveMoney(1000)
  ,baselife(0)
  ,killed_enemies(0)
  ,gameEnded(false)
  ,gameWin(false)
{    this->setMouseTracking(true);
    this->setFixedSize(1200, 639);
    this->show();
    loadTowerPositions();

    addPathPoints();
     preLoadWavesInfo();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);
   //  qDebug()<<"ok"<<endl;
    setTowerup();
     QTimer::singleShot(300, this, SLOT(gameStart()));

}
Scene::~Scene(){
    delete this->lab1;
    delete this->lab2;
    delete this->lab3;
    delete this->lab4;
    delete this->lab5;
    delete this->lab6;
    delete this->lab7;
    delete this->lab8;
    delete this->lab9;
    delete this->lab10;
    delete this->lab11;
   // delete this->lab12;
   // delete this->m_towersList;
   delete this-> copyBar;
    delete this-> copyBarPic;

    delete this-> statusBar;
     delete this-> statusBarPic;

    delete this->WaveFront ;
    delete  this->baselifeFront ;
    delete  this->MoneyFront ;
    delete this->killedFront;
    delete currenttower;

    foreach (Copy *copy, towerCopy)
    {
        Q_ASSERT(copy);
        towerCopy.removeOne(copy);
        delete copy;
    }


}
void Scene::paintEvent(QPaintEvent *){
  if(gameEnded||gameWin)//赢了或结束了，结束即输了
{
      if(gameWin){
      QPixmap loseScene(":/picture/title.png");
      QPainter painter(this);
      painter.drawPixmap(0, 0, loseScene);

      }

      if(gameEnded)
      {
          QPixmap loseScene(":/picture/title.png");
          QPainter painter(this);
          painter.drawPixmap(0, 0, loseScene);
      }
      return;

}
    QPixmap backgroundPix(":/picture/timga.png"); //背景
   // QPixmap copybarPix(":/picture/copybase.png"); //放置基塔的状态栏
    QPainter cachePainter(&backgroundPix);

//    foreach (const TowerPosition &towerPos, m_towerPositionsList)
//        towerPos.draw(&cachePainter);


//建立塔
    foreach (Tower *tower, m_towersList)
        tower->draw(&cachePainter);
    // qDebug()<<"ok to draw tower"<<endl;
//画敌人行进路线
    foreach (const TravelPath *travelpath, m_pathPointsList)
        travelpath->draw(&cachePainter);
//敌人前进
    foreach (Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);
   // qDebug()<<"ok to draw enemies"<<endl;
    foreach (const Bullet *bullet, bulletList)
        bullet->draw(&cachePainter);
  //  qDebug()<<"ok to draw bullets"<<endl;
    foreach ( BloodBar *blood, bloodbarList)
       blood->draw(&cachePainter);
  //  qDebug()<<"blood draw list"<<endl;
    drawhaveMoney();
    drawWave();
    drawbaselife();
    drawkillednum();

    QPainter painter(this);
    painter.drawPixmap(0, 0, backgroundPix);
   // painter.drawPixmap(480,550,copybarPix);





}

void Scene::loadTowerPositions()
{
    QFile file("C:/Users/Windows/Documents/MyTowerDefence/config/TowersPositionn.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    QList<QVariant> array = reader.data();
    foreach (QVariant dict, array)
    {
        QMap<QString, QVariant> point = dict.toMap();
        int x = point.value("x").toInt();
        int y = point.value("y").toInt();
        m_towerPositionsList.push_back(QPoint(x, y));
    }

    file.close();
}


void Scene::mouseMoveEvent(QMouseEvent *event)
{
   //让塔跟着鼠标动
    pp = event->pos();
    if (this->settleCopy != nullptr)
    {
        this->settleCopy->move
                (pp+QPoint(-20,-20));
    }
}

void Scene::mousePressEvent(QMouseEvent *event)
{ QPoint pressPos = event->pos();
    int pos_x = pressPos.x();
    int pos_y = pressPos.y();

    //拆塔实现
    if (settleCopy == nullptr){
        auto it = m_towerPositionsList.begin();
        while (it != m_towerPositionsList.end())
        {
            if (settleCopy == nullptr && it->containPoint(pressPos) && it->hasTower())
            {

                currenttower = it->m_tower;    //把当前tower赋给currenttower
                if (event->button() == Qt::RightButton)
             {

                    delete it->m_tower;
                    m_towersList.removeOne(it->m_tower);
                   // this->settleCopy->move(this->whichtowerPos);
                  //  this->settleCopy = nullptr;
                    it->m_hasTower=false;
                    return;
                }
            }
             ++it;
        }
    }
//         if (settleCopy == nullptr){
//             auto it = m_towerPositionsList.begin();
//             while (it != m_towerPositionsList.end())
//             {
//                 if ( it->containPoint(pressPos) && it->hasTower())
//                 {
//                     delete it->m_tower;
//                      m_towersList.removeOne(it->m_tower);
//                     this->settleCopy->move(this->whichtowerPos);
//                     this->settleCopy = nullptr;
//                     return;
//                 }
//             }
//     }
//     }
//    for (int i = 0; i < m_towersList.count(); i++)
//    {
//        if (settleCopy == nullptr){
//            if (event->button() == Qt::RightButton)
//            {
//            delete m_towersList[i];
//            m_towersList.removeAt(i);
//            this->settleCopy->move(this->whichtowerPos);
//            this->settleCopy = nullptr;
//            return;
//        }
//    }
//     }
    //鼠标点的赋值

        qDebug()<<pos_x<<" "<<pos_y<<endl;
    //让塔可以放在塔部，没有点塔放不上去
        if(settleCopy!= nullptr){
            bool temp = 0;//判断是否所有塔基上都建立了塔
            auto it = m_towerPositionsList.begin();

            while (it != m_towerPositionsList.end())
            {
                if ( canBuyTower() && it->containPoint(pressPos) && !it->hasTower())//可以在塔基位置安装的条件
                {
                    temp = 1;


                    it->setHasTower();
                    Tower *tower;
                    switch(settletower)
                    {
                    case 0:tower = new AsheTower (it->centerPos(), this);//把中心点传给他
                        it->m_tower = tower;
                        haveMoney -= 100;//减钱

                      //  it->m_towerkind = 0;
                        break;
                    case 1:tower = new TristanaTower(it->centerPos(), this);
                        haveMoney -= 100;
                       it->m_tower = tower;

//                        it->m_towerkind = 1;
                        break;
                    case 2:tower = new MorganaTower(it->centerPos(),this);
                        haveMoney-=100;
                       it->m_tower = tower;

                        break;

                    }
                    m_towersList.push_back(tower);
                    update(); //调用paintevent(),重绘画面
                    settleCopy->move(whichtowerPos);
                    settleCopy = nullptr;//更新为nullptr
                    break;
                }

                ++it;
            }
            if(temp == 0)//如果所有塔基都建立了塔，玩家手中的塔的copy件不能安装塔而直接回到copybar
            {
                settleCopy->move(whichtowerPos);
                settleCopy = nullptr;
            }
        }

      //用whichtower表示塔的分类，选择了哪个塔
      int whichtower = -1;
      //ashe
      if (pos_x >= 510 && pos_x <= 555 && pos_y >= 540 && pos_y <= 585)
          whichtower = 0;
      //tristana
      else if (pos_x >= 565 && pos_x <= 610 && pos_y >= 540 && pos_y <= 585)
          whichtower = 1;
      //morgana
      else if (pos_x >= 620 && pos_x <= 665 && pos_y >= 540 && pos_y <= 585)
          whichtower =2;


      if (whichtower >= 0)
      {
          whichtowerPos = towerCopy[whichtower]->pos();
          this->settleCopy = towerCopy[whichtower];
          settletower = whichtower;
      }


//    QPoint pressPos = event->pos();//把鼠标的点给presspos
//    QString str= QString("鼠标按下 x=%1  y=%2").arg(event->x()).arg(event->y());
//    qDebug()<<str;
//    auto it = m_towerPositionsList.begin();
//    while (it != m_towerPositionsList.end())
//    {
//        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())//可以买塔，鼠标点到了框内且框中无塔
//        {
//            //m_audioPlayer->playSound(TowerPlaceSound);
//            //m_playrGold -= TowerCost;
//            it->setHasTower();//放塔

//            Tower *tower = new Tower(it->centerPos(), this);//塔的中心点
//            m_towersList.push_back(tower);
//            update();
//            break;
//        }

//        ++it;
//    }

//        if (QRect(400, 400, 600,600).contains(event->pos()))//如果鼠标点到了这个矩形区域
//        {
//            emit toPlay();


//        }
}

bool Scene::canBuyTower() const
{
    return true;
}
void Scene::setTowerup(){

    //设置塔基的位置
    lab1->setStyleSheet("QLabel{border: 1px solid white;} QLabel:hover{border:1px groove #EE0000;}");
    lab1->setGeometry(230, 150, 70, 70);
    lab1->show();
    //lab1->setPixmap(QPixmap(":/picture/pic.png"));
    lab1->raise();//把lable放在前面，防止被覆盖

    lab2->setStyleSheet("QLabel{border: 1px solid white;} QLabel:hover{border:1px groove #EE0000;}");
    lab2->setGeometry(800, 320, 70, 70);
    lab2->show();
   // lab2->setPixmap(QPixmap(":/picture/pic.png"));
    lab2->raise();

    lab3->setStyleSheet("QLabel{border: 1px solid white;} QLabel:hover{border:1px groove #EE0000;}");
    lab3->setGeometry(40, 340, 70, 70);
    lab3->show();
    //lab3->setPixmap(QPixmap(":/picture/pic.png"));
    lab3->raise();

    lab4->setStyleSheet("QLabel{border: 1px solid white;} QLabel:hover{border:1px groove #EE0000;}");
    lab4->setGeometry(600, 320, 70, 70);//中凸点
    lab4->show();
   // lab4->setPixmap(QPixmap(":/picture/pic.png"));
    lab4->raise();

    lab5->setStyleSheet("QLabel{border: 1px solid white;} QLabel:hover{border:1px groove #EE0000;}");
    lab5->setGeometry(416, 434, 70, 70);
    lab5->show();
   // lab5->setPixmap(QPixmap(":/picture/pic.png"));
    lab5->raise();

    lab6->setStyleSheet("QLabel{border: 1px solid white;} QLabel:hover{border:1px groove #EE0000;}");
    lab6->setGeometry(330, 230, 70, 70);
    lab6->show();
   // lab6->setPixmap(QPixmap(":/picture/pic.png"));
    lab6->raise();

    lab7->setStyleSheet("QLabel{border: 1px solid /*#000000*/white;} QLabel:hover{border:1px groove #EE0000;}");
    lab7->setGeometry(455, 120, 70, 70);//中凸点
    lab7->show();
    //lab7->setPixmap(QPixmap(":/picture/pic.png"));
    lab7->raise();

    lab8->setStyleSheet("QLabel{border: 1px solid /*#000000*/white;} QLabel:hover{border:1px groove #EE0000;}");
    lab8->setGeometry(900, 120, 70, 70);
    lab8->show();
    //lab8->setPixmap(QPixmap(":/picture/pic.png"));
    lab8->raise();

    lab9->setStyleSheet("QLabel{border: 1px solid /*#000000*/white;} QLabel:hover{border:1px groove #EE0000;}");
    lab9->setGeometry(960, 316, 70, 70);
    lab9->show();
  //  lab9->setPixmap(QPixmap(":/picture/pic.png"));
    lab9->raise();

    lab10->setStyleSheet("QLabel{border: 1px solid /*#000000*/white;} QLabel:hover{border:1px groove #EE0000;}");
    lab10->setGeometry(730, 117, 70, 70);
    lab10->show();
   // lab10->setPixmap(QPixmap(":/picture/pic.png"));
    lab10->raise();

    lab11->setStyleSheet("QLabel{border: 1px solid /*#000000*/white;} QLabel:hover{border:1px groove #EE0000;}");
    lab11->setGeometry(1140, 200, 70, 70);//中凸点
    lab11->show();
   // lab11->setPixmap(QPixmap(":/picture/pic.png"));
    lab11->raise();
//    AsheTowerCopy->setGeometry(180, 40, 100, 70);
//    asheTowerCopy->start();
//    AsheTowerCopy->show();
//    AsheTowerCopy->setMovie(asheTowerCopy);
//    AsheTowerCopy->raise();


//    lab12->setStyleSheet("QLabel{border: 1px solid /*#000000*/white;} QLabel:hover{border:1px groove #EE0000;}");
//    lab12->setGeometry(400, 520,260, 110);//中凸点
//    lab12->show();
   // lab11->
   // lab12->raise();

   setCopyup();

  //设置退出按钮
   exit->setParent(this);//放在当前窗口下
   exit->move(700,0);
   connect(exit,&MyPushButton::clicked,[=](){
       //弹跳特效
       exit->upbounce();
       exit->downbounce();
   });
  // exit->setGeometry(700, 0, 60, 60);
   exit->setFlat(true);
 //  exit->setIcon(QIcon(":/image/Leave.png"));
   exit->setIconSize(QSize(60,60));
   exit->setStyleSheet("background: transparent");
   exit->setCursor(Qt::PointingHandCursor);
  // connect(exit, SIGNAL(clicked()), this, SLOT(leave()));
   exit->show();
   exit->raise();
//金币
   MoneyFront->setGeometry(610, 600, 60, 60);
   MoneyFront->setFont(QFont("Calibri", 14));
   MoneyFront->setStyleSheet("color:yellow");
   MoneyFront->setText("50");
   MoneyFront->setAlignment(Qt::AlignHCenter);
   MoneyFront->show();
   MoneyFront->raise();
//wave
   WaveFront->setGeometry(956, 5, 50, 30);
   WaveFront->setFont(QFont("Calibri", 10));
   WaveFront->setStyleSheet("color:white");
   WaveFront->setText("1");
   WaveFront->setAlignment(Qt::AlignHCenter);
   WaveFront->show();
   WaveFront->raise();

//to show how many tower the player have set
   baselifeFront->setGeometry(880, 5, 50, 30);
   baselifeFront->setFont(QFont("Calibri", 11));
   baselifeFront->setStyleSheet("color:red");
   baselifeFront->setText("1");
   baselifeFront->setAlignment(Qt::AlignHCenter);
   baselifeFront->show();
   baselifeFront->raise();
// to show how many enemies have been killed
   killedFront->setGeometry(810, 5, 50, 30);
   killedFront->setFont(QFont("Calibri", 11));
   killedFront->setStyleSheet("color:lightblue");
   killedFront->setText("1");
   killedFront->setAlignment(Qt::AlignHCenter);
   killedFront->show();
   killedFront->raise();

}


void Scene::setCopyup()
{

//设置右上角状态栏
    statusBar->setGeometry(805,1,397,34);
    statusBarPic->start();
    statusBar->show();
    statusBar->setPixmap(QPixmap(":/picture/statebar.png"));

//设置塔工具栏
    copyBar->setGeometry(490, 530, 260, 110);
    copyBarPic->start();
    copyBar->show();
    copyBar->setPixmap(QPixmap(":/picture/copybase.png"));
   // copyBar->raise();
//ashetower-copy
     Copy *ashetowercopy = new AsheTowerCopy(this);
     ashetowercopy->setGeometry(510, 540 , 45, 45);
     towerCopy.append(ashetowercopy);//将元素放到列表中
     ashetowercopy->show();
     ashetowercopy->raise();
//tristanatower-copy
     Copy *tristanatowercopy = new TristanaTowerCopy(this);
     tristanatowercopy->setGeometry(565, 540 , 45, 45);
     towerCopy.append(tristanatowercopy);//将元素放到列表中
     tristanatowercopy->show();
     tristanatowercopy->raise();
//Morganatower-copy
     Copy *Morganatowercopy = new MorganaTowerCopy(this);
     Morganatowercopy->setGeometry(620, 540 , 45, 45);
     towerCopy.append(Morganatowercopy);//将元素放到列表中
     Morganatowercopy->show();
     Morganatowercopy->raise();
}


void Scene::addPathPoints()
{
    TravelPath *TravelPoint1 = new TravelPath(QPoint(1172,375));
    m_pathPointsList.push_back(TravelPoint1);

    TravelPath *TravelPoint2 = new TravelPath(QPoint(1072, 375));
    m_pathPointsList.push_back(TravelPoint2);
    TravelPoint2->setNextTravelPoint(TravelPoint1);

    TravelPath *TravelPoint3 = new TravelPath(QPoint(1072, 261));
    m_pathPointsList.push_back(TravelPoint3);
    TravelPoint3->setNextTravelPoint(TravelPoint2);

    TravelPath *TravelPoint4 = new TravelPath(QPoint(482, 261));
    m_pathPointsList.push_back(TravelPoint4);
    TravelPoint4->setNextTravelPoint(TravelPoint3);

    TravelPath *TravelPoint5 = new TravelPath(QPoint(482,364));
    m_pathPointsList.push_back(TravelPoint5);
    TravelPoint5->setNextTravelPoint(TravelPoint4);

    TravelPath *TravelPoint6 = new TravelPath(QPoint(170,364));
    m_pathPointsList.push_back(TravelPoint6);
    TravelPoint6->setNextTravelPoint(TravelPoint5);

    TravelPath *TravelPoint7= new TravelPath(QPoint(170,56));
    m_pathPointsList.push_back(TravelPoint7);
    TravelPoint7->setNextTravelPoint(TravelPoint6);



}


void Scene::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;
   // Scene::removedBlood();
    if (m_enemyList.empty())
    {
        ++waves;//加波数
        qDebug()<<"++waves "<<waves<<endl;
        if (!loadWave())
        {
//			m_gameWin = true;

        }
    }
}
void Scene::removedBlood(BloodBar *blood){
    bloodbarList.removeOne(blood);
    delete blood;
}
void Scene::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    bulletList.removeOne(bullet);
    delete bullet;
}
void Scene::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    bulletList.push_back(bullet);
}
void Scene::preLoadWavesInfo()
{
    QFile file("C:/Users/Windows/Documents/MyTowerDefence/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Waves", "Cannot Open Waves.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    // 获取波数信息
    wavesInfo = reader.data();

    file.close();
}

bool Scene::loadWave()
{
    if (waves >= wavesInfo.size())
        return false;
//qDebug()<<"****"<<wavesInfo.size()<<endl;
    TravelPath *nowPathPoint = m_pathPointsList.back();
    QList<QVariant> curWavesInfo = wavesInfo[waves].toList();//每波按文件是6个
   // qDebug()<<"wave"<<" "<<waves<<endl;
    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        //qDebug()<<"curwaves"<<" "<<curWavesInfo.size()<<endl;
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();

        Enemy *enemy ;

        int j=i%6;
        switch(j){
        case 0:

        enemy =new Enemy(nowPathPoint,this);


        case 1:

            enemy = new DogFace1(nowPathPoint, this);
            break;
        case 2:

            enemy=new Wind(nowPathPoint, this);

            break;
        case 3:

            enemy=new Nashor(nowPathPoint , this);

            break;

        case 4:

            enemy=new Draven(nowPathPoint , this);

            break;

        case 5:

            enemy=new Yasuo(nowPathPoint , this);

            break;


        }
        m_enemyList.push_back(enemy);
       // qDebug()<<"enemy push back"<<endl;

        BloodBar * blood=new BloodBar(enemy,this);
        bloodbarList.push_back(blood);
      //  qDebug()<<"blood push back"<<endl;

        QTimer::singleShot(spawnTime, enemy, SLOT(setFree()));//延迟spawnTime
      //  qDebug()<<"spawnTime"<<" "<<spawnTime<<endl;
    }

    return true;
}

QList<Enemy *> Scene::enemyList() const
{
    return m_enemyList;
}

void Scene::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();

    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}
void Scene::gameStart(){
     loadWave();
}
void Scene::awardMoney(int money){
    haveMoney+=money;
    update();
}
void Scene::drawhaveMoney(){
//    painter->setPen(QPen(Qt::red));
//    painter->drawText(QRect(200, 100, 200, 25), QString("GOLD : %1").arg(haveMoney));

    MoneyFront->setText(QString("%1").arg(haveMoney));
    MoneyFront->setAlignment(Qt::AlignHCenter);
    MoneyFront->show();
    // qDebug()<<"draw money"<<endl;
    MoneyFront->raise();

}
void Scene::drawWave(){
    WaveFront->setText(QString("%1").arg(waves +1));
    WaveFront->setAlignment(Qt::AlignHCenter);
    WaveFront->show();
    WaveFront->raise();
}
void Scene::drawbaselife(){
    baselifeFront->setText(QString("%1").arg(baselife ));
    baselifeFront->setAlignment(Qt::AlignHCenter);
    baselifeFront->show();
    baselifeFront->raise();
}
void Scene::drawkillednum(){
 //   qDebug()<<killed_enemies<<endl;
    killedFront->setText(QString("%1").arg(killed_enemies ));
    killedFront->setAlignment(Qt::AlignHCenter);
    killedFront->show();
    killedFront->raise();
}
void Scene::getbaselife(){
    baselife++;
    qDebug()<<"baselife"<<baselife<<endl;
    if(baselife>1)
       {
        qDebug()<<"dogameover"<<endl;
       // dogameover();
}
}
void Scene::getkilled_enemies(){
    killed_enemies++;
}

void Scene::dogameover()
{if (!gameEnded)
    {
        gameEnded = true;}
}
