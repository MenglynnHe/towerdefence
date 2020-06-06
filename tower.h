#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include "scene.h"
#include <QtMath>
#include"QTimer"
#include "enemy.h"
class Enemy;
//碰撞检测
inline bool if_collision_inCircle(QPoint point1, int radius1, QPoint point2, int radius2)
{
    const int xdif = point1.x() - point2.x();
    const int ydif = point1.y() - point2.y();
    const int distance = qSqrt(xdif * xdif + ydif * ydif);
    if (distance <= radius1 + radius2)
        return true;
    return false;
}


class Scene;
class Tower : public QObject
{
    Q_OBJECT
public:
    //Tower(QObject *parent = nullptr);
    Tower(QPoint pos,Scene * game,const   QPixmap &sprite= QPixmap(":/picture/towerashe.png") );
    ~Tower();
    virtual void draw(QPainter *painter) const;//画塔
    void drawelli(QPainter *painter) const;
    void checkEnemyInRange();
    void forgiveEnemy();
    void set_attacked_Enemy(Enemy *enemy);//改变这个enemy的状态
    void targetKilled();
    int getRange(){
        return attackRange;
    }
    int returnAttack(){
        return damage;
    }
    int getRate(){
        return attackRate;
    }
    int             m_level;
    int             kind;
    virtual void upgrade() = 0;
protected:
    int            timerId2;
    bool			attacking;
    qreal			rotationIcon;

    int				attackRange;	// 代表塔可以攻击到敌人的距离
    int				damage;		// 代表攻击敌人时造成的伤害
    int				attackRate;		// 代表再次攻击敌人的时间间隔


    const QPoint	pos; //塔的圆心
    const QPixmap	icon; //塔的图片
    Scene *         game;
    QTimer *		attackTimer;
    Enemy *         choosed_enemy;//敌人的选择
    static const QSize ms_fixedSize;

signals:

public slots:
    virtual void startShooting()=0;
};


class AsheTower: public Tower
{
    Q_OBJECT
public:
    AsheTower(QPoint pos, Scene * game, const QPixmap &sprite = QPixmap(":/picture/towerashe.png"));
    ~AsheTower();
    virtual void upgrade() ;



protected slots:
    virtual void startShooting();
private:
    qreal         toslow;
};

class TristanaTower: public Tower
{
    Q_OBJECT
public:
   TristanaTower(QPoint pos, Scene * game, const QPixmap &sprite = QPixmap(":/picture/tristower.png"));
    ~TristanaTower();

    virtual void upgrade() ;

protected slots:
    virtual void startShooting();
};

class MorganaTower: public Tower
{
    Q_OBJECT
public:
   MorganaTower(QPoint pos, Scene * game, const QPixmap &sprite = QPixmap(":/picture/Morgana.png"));
    ~MorganaTower();

   virtual void upgrade() ;

protected slots:
    virtual void startShooting();
};
#endif // TOWER_H
