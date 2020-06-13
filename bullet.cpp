#include "bullet.h"
#include "QDebug"
#include <QPropertyAnimation>
const QSize Bullet::fixedSize(8, 8);

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
              BaseScene *game,qreal slow, const QPixmap &icon)
    : startPos(startPos)//子弹开始的位置
    , targetPos(targetPoint)//目标的位置
    , icon(icon)
    , current_Pos(startPos)
    , target(target)
    , game(game)//游戏中
    , damage(damage)//子弹伤害
    , bulletKind(0)
    , slow_speed(slow)
{//qDebug()<<"bullet icon"<<endl;
}
Bullet ::~ Bullet(){}
void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(current_Pos, icon);
  // qDebug()<<this->icon<<endl;
}

void Bullet::move()
{
    // 100毫秒内击中敌人
    static const int duration = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "currentPos");
    animation->setDuration(duration);
    animation->setStartValue(startPos);
    animation->setEndValue(targetPos);
    animation->setEasingCurve(QEasingCurve::OutBounce);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
 //   qDebug()<<"already to bullet move"<<endl;
}

void Bullet::hitTarget()
{
    // 这样处理的原因是:
    // 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
    // 后续炮弹再攻击到的敌人就是无效内存区域
    // 因此先判断下敌人是否还有效
    if (game->enemyList().indexOf(target) != -1)
        target->getDamage(this);
    game->removedBullet(this);
}

void Bullet::setCurrentPos(QPoint pos)
{
    current_Pos = pos;
}

QPoint Bullet::currentPos() const
{
    return current_Pos;
}
AsheBullet::AsheBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, BaseScene *game, qreal slow,const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game,slow,sprite)
{

}

TrisBullet::TrisBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, BaseScene *game,  const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game,1, sprite)
{
    bulletKind=1;
}

MorganaBullet::MorganaBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, BaseScene *game,  const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game,1,sprite)
{
    bulletKind=2;
}
