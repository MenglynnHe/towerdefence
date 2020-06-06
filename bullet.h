#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include "QPoint"
#include "tower.h"
#include "enemy.h"
#include <QSize>
#include "QDebug"
class Bullet :public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint currentPos READ currentPos WRITE setCurrentPos)

public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
           Scene *game, qreal slow = 1,const QPixmap &icon= QPixmap(":/bullet/bulletcopy.png"));

    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;
    ~Bullet();
    int				damage;
    int             bulletKind;
    qreal           slow_speed;
protected:

private slots:
    void hitTarget();

private:
    const QPoint	startPos;
    const QPoint	targetPos;
    const QPixmap	icon;
    QPoint			current_Pos;
    Enemy *			target;
    Scene *	        game;


    static const QSize fixedSize;
};
class AsheBullet: public Bullet{
    Q_OBJECT

public:
    AsheBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, Scene *game, qreal slow = 1.0,const QPixmap &sprite = QPixmap(":/bullet/ashebullet.png"));

};
class TrisBullet: public Bullet
{
    Q_OBJECT

public:
    TrisBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, Scene *game, const QPixmap &sprite = QPixmap(":/picture/bullet/trisbullet1.png"));
};

class MorganaBullet: public Bullet
{
    Q_OBJECT

public:
    MorganaBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, Scene *game, const QPixmap &sprite = QPixmap(":/bullet/Morganabullet.png"));
};

#endif // BULLET_H
