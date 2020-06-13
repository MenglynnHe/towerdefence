#ifndef SCENE_H
#define SCENE_H
#include "towerposition.h"
#include <QMainWindow>
#include <QList>
#include <tower.h>
#include "QLabel"
#include "mypushbutton.h"
#include "QMovie"
#include "copy.h"
#include "QMouseEvent"
#include "travelpath.h"
#include "enemy.h"
#include "bullet.h"
#include "bloodbar.h"
//场景布置
class Enemy;
class Tower;
class Bullet;
class BloodBar;
class TowerPosition;
class BaseScene : public QLabel
{
    Q_OBJECT
public:
    Copy* settleCopy=nullptr;//@
    QPoint currentPos;
    QList<Copy*> towerCopy;
    QPoint pp;//用在mousemovement

    Tower* currenttower;//@

    explicit BaseScene(QWidget *parent = 0);
    virtual  ~BaseScene();
    void mouseMoveEvent(QMouseEvent *event);


 //   QTimer* timer = nullptr;//@
    QLabel* WaveFront = new QLabel(this);//波数
    QLabel* baselifeFront = new QLabel(this);//基地生命值
    QLabel* MoneyFront = new QLabel(this);//金币
    QLabel* killedFront = new QLabel(this);//击杀敌人数

    QLabel* attack      = new QLabel(this);//攻击力
    QLabel* attackRate   = new QLabel(this);//攻击速度
    QLabel* Level       = new QLabel(this);//级别
    QLabel* upgradeBar1 = new QLabel(this);//点升级
    QMovie* upgradebar1 = new QMovie(":/picture/upgrade.png");
    QLabel* upgradeBar2 = new QLabel(this);
    QMovie* upgradebar2 = new QMovie(":/picture/upgrade.png");
    QLabel* upgradeBar3 = new QLabel(this);
    QMovie* upgradebar3 = new QMovie(":/picture/upgrade.png");

    QLabel* copyBar = new QLabel(this);
    QMovie* copyBarPic = new QMovie(":/picture/copybase.png");
    QLabel* statusBar = new QLabel(this);
    QMovie* statusBarPic = new QMovie(":/picture/statebar.png");
    QLabel* attributeBar = new QLabel(this);
    QMovie* attributeBarPic = new QMovie(":/picture/attribute.png");


    // move to base class
    void addBullet(Bullet *bullet);//@
    virtual void removedEnemy(Enemy *enemy) = 0;//@
    void removedBullet(Bullet *bullet);//@
    void removedBlood(BloodBar *blood);
    QList<Enemy *> enemyList() const;//@
    void awardMoney(int money);//@
 //   void getHpDamage(int damage);
    void getbaselife();
    void getkilled_enemies();
    bool canBuyTower() const;
    void dogameover();//@
    void drawhaveMoney();
    void drawWave();
    void drawbaselife();
    void drawkillednum();//击杀的敌人数
 //   AudioPlayer* audioPlayer() const;

    QList<Bullet *>			bulletList;//@
    QList<Enemy *>			m_enemyList;//@
    QList<BloodBar *>       bloodbarList;
    QList<Tower *>			m_towersList;//@
    MyPushButton *exit=new MyPushButton(":/picture/u=3817788749,2795166190&fm=26&gp=0.jpg");
    int						waves;//@
    bool                    gameEnded;//@
    bool                    gameWin;//@
 //   int						m_playerHp;
    int                     haveMoney;
    int                     settletower=-1;//默认最开始的塔为-1---ashetower@
    int                     upgradestate = 0;//表示能否升级的状态@
    int                     towerkind;
    int                     baselife;
    int                     killed_enemies;

 //   AudioPlayer *		    m_audioPlayer;

signals:
 //   void toTitle(); //返回信号，返回主界面


public slots:
    void MorIceattack();//攻击效果实现，只有Mor控制效果和ashe的减速效果
};


//******************
//*****选择关卡******
//******************
class CanyonScene;
class Scene;
class ChoiceScene : public QLabel
{
    Q_OBJECT
public:
    explicit ChoiceScene(QWidget* parent = 0);
    ~ChoiceScene();

private:
    QMovie* background = new QMovie(":/picture/choicescene.png");
    Scene * scene=nullptr;
    CanyonScene * canyonscene= nullptr;

public slots:
    void playPolar();//开始游戏
    void playCanyon();

};

//*************************
//*****分场景游戏1-Scene*****
//*************************
class Scene : public BaseScene
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = nullptr);
    ~Scene();
    void paintEvent(QPaintEvent *);
    void loadTowerPositions();

  //  bool canBuyTower() const;
    bool loadWave();//加载波数
    void setTowerup();//确定塔可以放的位置
    void setCopyup();//设置基塔放置的地方，就是选择塔的地方
    void mousePressEvent(QMouseEvent * event);


    QList<TravelPath *> m_pathPointsList;	// 在paintEvent中需要进行绘制
    void addPathPoints();			// 形成一条完整的travel节点列表，在构造函数中调用

    virtual void removedEnemy(Enemy *enemy);//去除enemy@

    void preLoadWavesInfo();
    QPoint whichtowerPos;//记录你选择的基塔的位置，之后移动基塔后还得放回去
    void stateBar(Tower * nowtower);

private:
     QLabel * lab1= new QLabel(this);
     QLabel * lab2= new QLabel(this);
     QLabel * lab3= new QLabel(this);
     QLabel * lab4= new QLabel(this);
     QLabel * lab5= new QLabel(this);
     QLabel * lab6= new QLabel(this);
     QLabel * lab7= new QLabel(this);
     QLabel * lab8= new QLabel(this);
     QLabel * lab9= new QLabel(this);
     QLabel * lab10= new QLabel(this);
     QLabel * lab11= new QLabel(this);
     QList<TowerPosition >    m_towerPositionsList;
     QList<QVariant >			wavesInfo;

   //  QList<TravelPath *>		travelPointList;//航点列表


signals:
//     void toPlay();
//     void toTitle();

public slots:
    void updateMap();
    void gameStart();  
};

//*************************
//*****分场景游戏2-CanyonScene*****
//*************************
class CanyonScene : public BaseScene
{
    Q_OBJECT
public:
    explicit CanyonScene(QWidget *parent = nullptr);//@
    ~CanyonScene();//@
    void paintEvent(QPaintEvent *);//@
    void loadTowerPositions();//@


  //  bool canBuyTower() const;
    bool loadWave();//加载波数@@
    void setTowerup();//确定塔可以放的位置 @@
    void setCopyup();//设置基塔放置的地方，就是选择塔的地方@@
    void mousePressEvent(QMouseEvent * event);//
//    QList<TravelPath *> m_pathPointsList;	// 在paintEvent中需要进行绘制


    virtual void removedEnemy(Enemy *enemy);//去除enemy@

    void preLoadWavesInfo();//@
    QPoint whichtowerPos;//记录你选择的基塔的位置，之后移动基塔后还得放回去
    void stateBar(Tower * nowtower);//用了会异常

private:
    //多条路一起走
      void addDF2Points();
      void addYasuoPoints();
      void addEnemyPoints();
      void addNashorPoints();
      void addWindPoints();

     QLabel * lab1= new QLabel(this);
     QLabel * lab2= new QLabel(this);
     QLabel * lab3= new QLabel(this);
     QLabel * lab4= new QLabel(this);
     QLabel * lab5= new QLabel(this);
     QLabel * lab6= new QLabel(this);
     QLabel * lab7= new QLabel(this);
     QLabel * lab8= new QLabel(this);
     QLabel * lab9= new QLabel(this);
     QLabel * lab10= new QLabel(this);
     QLabel * lab11= new QLabel(this);
     QList<TowerPosition >    m_towerPositionsList;
     QList<TravelPath *>    DF2PointsList;
     QList<TravelPath *>    YasuoPointsList;
     QList<TravelPath *>    EnemyPointsList;
     QList<TravelPath *>    NashorPointsList;
     QList<TravelPath *>    WindPointsList;
     QList<QVariant>			wavesInfo;

   //  QList<TravelPath *>		travelPointList;//航点列表


signals:
//     void toPlay();
//     void toTitle();

public slots:
    void updateMap();
    void gameStart();
};



#endif // SCENE_H
