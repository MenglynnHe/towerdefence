#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include "travelpath.h"
#include "scene.h"
#include <QSize>
#include"bloodbar.h"
class Scene;
class Tower;
class Enemy : public QObject
{
    Q_OBJECT


public:
    //当前敌人前进的位置-nowPoint,在scene场景中玩游戏，敌人的形象icon
    Enemy(TravelPath *nowPoint, Scene*game, const QPixmap &icon = QPixmap(":/enemy/dogface.png"));
    ~Enemy();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage);
    void getRemoved();
    int getLife() {return life;}  //生命长度
    int getOriginalLife()  {return origionlife;}
    void getAttacked(Tower *attacker);
    QList<Tower *>	attackTowersList;//攻击同一个敌人可能有多个列表
    QPoint getpos() const{return pos1;}
    bool getDamage(){return damage;}
    void removedBlood(BloodBar *blood);
    bool isChosen=0;
    bool			ifFree;//判断敌人是否空闲
public slots:
    void setFree();
    void setischosen(bool b){isChosen=b;}
protected:

    bool            damage;
    int				m_maxHp;
    //int				m_currentHp;
    int             life;
    qreal			m_walkingSpeed;
    qreal			m_rotationSprite;
    int             origionlife;//初始生命值
    QPoint			pos1;
    TravelPath *    targetPathPoint;//要去的目的地
    QPoint          size;
    Scene*	        game;
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
    DogFace1(TravelPath *startWayPoint, Scene *game, const QPixmap &sprite = QPixmap(":/enemy/dogface1.png"));
};

class Wind:public Enemy{//血厚，移速快
    Q_OBJECT
public:
    Wind(TravelPath *startWayPoint, Scene *game, const QPixmap &sprite = QPixmap(":/enemy/dragon2.png"));
};

class Nashor:public Enemy{//血厚，移速慢
    Q_OBJECT
public:
    Nashor(TravelPath *startWayPoint, Scene *game, const QPixmap &sprite = QPixmap(":/enemy/dragon1.png"));
};
class Draven:public Enemy{//看着凶猛，血厚，升级功能？
    Q_OBJECT
public:
    Draven(TravelPath *startWayPoint, Scene *game, const QPixmap &sprite = QPixmap(":/enemy/draven.png"));
};

class Yasuo:public Enemy{//移速快
    Q_OBJECT
public:
    Yasuo(TravelPath *startWayPoint, Scene *game, const QPixmap &sprite = QPixmap(":/enemy/yasuo.png"));
};
#endif // ENEMY_H
