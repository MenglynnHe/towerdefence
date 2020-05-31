#ifndef TRAVELPATH_H
#define TRAVELPATH_H
#include "QPoint"
#include "QPainter"
//小兵行进路线
class TravelPath
{
public:
    TravelPath(QPoint pos);
    void setNextTravelPoint(TravelPath *nextPoint);
    TravelPath* get_nextTravelPoint() const;
    const QPoint get_pos() const;

    void draw(QPainter *painter) const;//画线
    TravelPath operator +(const TravelPath &t){
        TravelPath tt(QPoint(this->get_pos().x()+t.get_pos().x(),this->get_pos().y()+t.get_pos().y()));

        return tt;
    }
private:
    QPoint m_pos;//记下节点
    TravelPath * m_nextTravelPoint;

};

#endif // TRAVELPATH_H
