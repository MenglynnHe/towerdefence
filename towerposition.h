#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H
#include <QPoint>
#include "QPainter"
#include <QSize>
#include <QPixmap>
#include "tower.h"
class Tower;
class TowerPosition
{

public:
    TowerPosition(QPoint pos, const QPixmap &sprite = QPixmap(":/picture/buttom2.png"));

    void setHasTower(bool hasTower = true);
    bool hasTower() const;
    const QPoint centerPos() const;
    bool containPoint(const QPoint &pos) const;

    void draw(QPainter *painter) const;
    Tower*       m_tower;
    bool		m_hasTower;
private:
    QPoint		m_pos;

    QPixmap		m_sprite;

    static const QSize ms_fixedSize;
};


#endif // TOWERPOSITION_H
