#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include "travelpath.h"
#include "Scene.h"
#include <QSize>
#include"bloodbar.h"
#include "bullet.h"
#include "QSound"
class BaseScene;
class Tower;
class Bullet;
class Enemy : public QObject
{
    Q_OBJECT


public:
    //当前敌人前进的位置-nowPoint,在BaseScene场景中玩游戏，敌人的形象icon
    Enemy(TravelPath *nowPoint, BaseScene*game, const QPixmap &icon = QPixmap(":/enemy/enemy/dogface.png"));
    virtual ~Enemy();

    void draw(QPainter *painter) const;
    void move();

    void getDamage(Bullet *bullet);
    void getRemoved();
    int getLife() {return life;}  //生命长度
    int getOriginalLife()  {return origionlife;}
    void getAttacked(Tower *attacker);
    QList<Tower *>	attackTowersList;//攻击同一个敌人可能有多个列表
    QPoint getpos() const{return pos1;}
    bool getDamage(){return damage;}
    void removedBlood(BloodBar *blood);
    bool isChosen=0;
    QSound* enemydie = new QSound("://AudioConvert/enemydie_1_1.wav",this);
    bool			ifFree;//判断敌人是否空闲

    int             ice; //
    int             iceLevel;//减速效果持续时间
    int             apdamage;
    int             apLevel;//魔法伤害效果持续时间
    qreal           m_slowSpeed; //寒冰状态的速度
    qreal           m_normalSpeed; //正常状态的速度
    qreal			m_walkingSpeed;
    BloodBar *       blood;
 //   qreal			m_rotationSprite;
public slots:
    void setFree();
    void setischosen(bool b){isChosen=b;}
protected:

    bool            damage;
    int				m_maxHp;
    //int				m_currentHp;
    int             life;

    int             origionlife;//初始生命值
    QPoint			pos1;
    TravelPath *    targetPathPoint;//要去的目的地
    QPoint          size;
    BaseScene*	        game;
    int             award;//击杀后可获得的奖励
   // QList<Tower *>	attackedTowersList;

    const QPixmap	icon;
    static const QSize fixedSize;//固定敌人的尺寸



signals:

public slots:
};

class DogFace1:public Enemy{//血厚
    Q_OBJECT
public:
    DogFace1(TravelPath *startWayPoint, BaseScene *game, const QPixmap &sprite = QPixmap(":/enemy/enemy/dogface1.png"));
};
class DogFace2:public Enemy{//血厚
    Q_OBJECT
public:
    DogFace2(TravelPath *startWayPoint, BaseScene *game, const QPixmap &sprite = QPixmap(":/enemy/enemy/enemy2.png"));
};
class Wind:public Enemy{//血厚，移速快
    Q_OBJECT
public:
    Wind(TravelPath *startWayPoint, BaseScene *game, const QPixmap &sprite = QPixmap(":/enemy/enemy/dragon2.png"));
};

class Nashor:public Enemy{//血厚，移速慢
    Q_OBJECT
public:
    Nashor(TravelPath *startWayPoint, BaseScene *game, const QPixmap &sprite = QPixmap(":/enemy/enemy/dragon1.png"));
};
class Draven:public Enemy{//看着凶猛，血厚，升级功能？
    Q_OBJECT
public:
    Draven(TravelPath *startWayPoint, BaseScene *game, const QPixmap &sprite = QPixmap(":/enemy/enemy/draven.png"));
};

class Yasuo:public Enemy{//移速快
    Q_OBJECT
public:
    Yasuo(TravelPath *startWayPoint, BaseScene *game, const QPixmap &sprite = QPixmap(":/enemy/enemy/yasuo.png"));
};
#endif // ENEMY_H
