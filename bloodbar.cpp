#include "bloodbar.h"
#include <QPainter>
#include "QDebug"
BloodBar::BloodBar(Enemy *parent,BaseScene *game):
    parent(nullptr)
{   this->game=game;
    this->parent=parent;
    setMinimum(0);//设置进度条的最小值
    setMaximum(500);//设置进度条的最大值
    rect = QRect(parent->getpos().x(), parent->getpos().y()-10, 60, 15);
    textRect = QRect(parent->getpos().x(), parent->getpos().y()-10, 60, 15);
    buttomMap = QPixmap(":/enemy/enemy/blood1.png");
    fillMap = QPixmap(":/enemy/enemy/blood2.png");
    font = QFont("Microsoft YaHei", 10, QFont::Bold);//设置字体样式
}
BloodBar ::~BloodBar(){

}

void BloodBar::draw(QPainter *p)
{
    if (!parent->ifFree)//空闲状态的enemy
        return;
   // qDebug()<<"draw bloodbar"<<endl;
    if(parent->getDamage())
    {
        k = (double)(value() - minimum()) / (maximum()-minimum());
        x = (int)(rect.width() * k);
        fillRect = rect.adjusted(0, 0, x-rect.width(), 0);
        //画进度条
        rect.moveTo(parent->getpos().x()-10, parent->getpos().y()-10);
        textRect.moveTo(parent->getpos().x()-10, parent->getpos().y()-10);
        fillRect.moveTo(parent->getpos().x()-10, parent->getpos().y()-10);
        p->drawPixmap(rect, buttomMap);
        p->drawPixmap(fillRect, fillMap);
        //qDebug()<<"fillmap"<<endl;

        //画文字
        p->setFont(font);
        p->setPen(QColor("white"));
        p->drawText(textRect, Qt::AlignCenter, valueStr);
        valueStr = QString("%1").arg(QString::number(value()));
        //this->setValue(100*(parent->getLife())/(parent->getOriginalLife()));
        this->setValue(parent->getLife());

    }
}
void BloodBar::getremoved(){
     game->removedBlood(this);
}

