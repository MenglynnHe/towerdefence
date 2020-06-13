#ifndef BLOODBAR_H
#define BLOODBAR_H

#include <QObject>
#include <QProgressBar>
#include "enemy.h"
class Enemy;
class BaseScene;
class BloodBar : public QProgressBar
{
    Q_OBJECT
public:
    BloodBar(Enemy * parent,BaseScene *game);
    void draw(QPainter *p);
    void getremoved();
    ~BloodBar();
    void check();
private:
    Enemy *parent;
    QRect rect;
    QRect textRect;
    QFont font;
    double k;
    int x;
    QRect fillRect;
    BaseScene*	        game;
    QString valueStr;
    QPixmap buttomMap;
    QPixmap fillMap;
};
#endif // BLOODBAR_H
