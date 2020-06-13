#include "enemy.h"
#include "travelpath.h"
#include "tower.h"
#include "Qpainter"
#include "QDebug"
#include "bloodbar.h"
const QSize Enemy::fixedSize(40, 40);

Enemy::Enemy(TravelPath *nowPoint, BaseScene*game, const QPixmap &icon )
    : QObject(0)
    , ifFree(false)//初始空闲
    , m_maxHp(40)
    , m_walkingSpeed(2.0)
   // , m_rotationSprite(0.0)
    , pos1(nowPoint->get_pos())//坐标赋值
  //  , targetPathPoint(nowPoint->get_nextTravelPoint())//目标点就是航点列表中的下一个点
    , game(game)
    , icon(icon)
    , size(0,0)
    ,damage(true)
    ,award(50)
    ,ice(0)
    ,apdamage(0)
    ,m_normalSpeed(2.0)
    ,m_slowSpeed(2.0)

{
    origionlife=80;
    life=80;
    blood = new BloodBar(this,game);
 //    qDebug()<<"ok to create an base enemy"<<endl;
     targetPathPoint=nowPoint->get_nextTravelPoint();
}

Enemy::~Enemy()
{
    attackTowersList.clear();
    targetPathPoint = NULL;
    game = NULL;
    blood= NULL;
}

void Enemy::setFree()
{
    ifFree = true;
 //   qDebug()<<"ok to setfree"<<endl;
}



 void Enemy::draw(QPainter *painter) const
{
    if (!ifFree)//空闲状态的enemy
        return;
    // 血条的长度
    // 其实就是2个方框,红色方框表示总生命,固定大小不变
    // 绿色方框表示当前生命,受m_currentHp / m_maxHp的变化影响
//	static const int Health_Bar_Width = 20;
    painter->save();

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-fixedSize.width() / 2, -fixedSize.height() / 2);
    painter->translate(pos1+size); //这里将坐标原点移到m_pos
   // painter->rotate(m_rotationSprite);

    // 绘制敌人
    painter->drawPixmap(offsetPoint, icon);
    painter->restore();
//    qDebug()<<"ok to draw an enemy"<<endl;
}



void Enemy::move()
{
    if (!ifFree)
    {
        //qDebug()<<"ok to iffree"<<endl;
        return;}
//qDebug()<<"ok to move999"<<endl;
//qDebug()<<"ok to !11"<<targetPathPoint->get_pos()<<endl;
    if (if_collision_inCircle(pos1, 1, targetPathPoint->get_pos(), 1))// 敌人抵达了一个航点
    {
//qDebug()<<"ok to move1"<<endl;
        if (targetPathPoint->get_nextTravelPoint())// 如果还存在下一个点
        {
//qDebug()<<"ok to move2"<<endl;
            pos1 = targetPathPoint->get_pos();//修改当前到达的位置，即到达了一个航点
            targetPathPoint = targetPathPoint->get_nextTravelPoint();//更新目标航点
//qDebug()<<"ok to move3"<<endl;
        }
        else
        {
            // 表示进入基地
           // game->baselife--;
            game->getbaselife();
            getRemoved();
//qDebug()<<"ok to move4"<<endl;
          //  game->removedBlood();
           // game->bloodbarList.removeOne();
            return;
        }
    }
//qDebug()<<"ok to **********"<<endl;
    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = targetPathPoint->get_pos();
 //   qDebug()<<"ok to move5"<<endl;
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值

    // 向量标准化(整不明白）
    qreal movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - pos1);
    normalized.normalize();
    pos1 = pos1 + normalized.toPoint() * movementSpeed;
 //   qDebug()<<"ok to enemy_move"<<endl;

    // 确定敌人选择方向
    // 默认图片向左,需要修正180度转右
    //m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;
}

void Enemy::getAttacked(Tower *attacker)
{
    attackTowersList.push_back(attacker);
}
void Enemy::getRemoved()
{
 //   qDebug()<<"ok to getremoved enmey"<<endl;
    if (!attackTowersList.empty())
    foreach (Tower *attacker, attackTowersList)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡

    game->removedEnemy(this);

}

void Enemy::getDamage(Bullet *bullet)
{
   life -= bullet->damage;

    // 阵亡,需要移除
    if (life <= 0)
       {
  //      qDebug()<<"kill one*******"<<endl;
        game->awardMoney(award);//击杀敌人奖励金钱
        game->getkilled_enemies();//不能确定是不是这里有问题
 //   qDebug()<<"killed ene"<<game->killed_enemies<<endl;
        getRemoved();
    }
    switch(bullet->bulletKind)
    {
        case 0://ashe
        ice = iceLevel;
        m_slowSpeed=m_normalSpeed* bullet->slow_speed;
        m_walkingSpeed =m_slowSpeed;//速度更新为slowspeed
            break;
        case 1://tris
            break;
        case 2://mor
       // apdamage=apLevel;
      //   m_walkingSpeed = 0.0;
        break;
    }
}


DogFace1::DogFace1(TravelPath *startWayPoint, BaseScene *game, const QPixmap &sprite/* = QPixmap(":/image/enemy1.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/image/enemy1.png")*/)
{


    this->pos1=startWayPoint->get_pos();
    this->origionlife=120;//增加血量
    this->life=120;
    this->award=70;
    this->targetPathPoint=startWayPoint->get_nextTravelPoint();
    this->iceLevel=15;
    this->apLevel=8;

}
DogFace2::DogFace2(TravelPath *startWayPoint, BaseScene *game, const QPixmap &sprite/* = QPixmap(":/image/enemy1.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/image/enemy1.png")*/)
{


    this->pos1=startWayPoint->get_pos();
    this->origionlife=120;//增加血量
    this->life=120;
    this->award=70;
    this->targetPathPoint=startWayPoint->get_nextTravelPoint();
    this->iceLevel=15;
    this->apLevel=8;

}
Wind::Wind(TravelPath *startWayPoint, BaseScene *game, const QPixmap &sprite/* = QPixmap(":/image/enemy2.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/image/enemy2.png")*/)
{
    this->origionlife=150;
    this->life=150;

    this-> m_walkingSpeed=1.8;

    this->pos1=startWayPoint->get_pos();
    this->size=QPoint(-114/2,-86/2);
    this->award=150;
    this->targetPathPoint=startWayPoint->get_nextTravelPoint();
    this->iceLevel=0;
    this->apLevel=0;
}

Nashor::Nashor(TravelPath *startWayPoint, BaseScene *game, const QPixmap &sprite/* = QPixmap(":/image/enemy1.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/image/enemy1.png")*/)
{

    this->award=300;
    this->pos1=startWayPoint->get_pos();
    this->origionlife=200;//增加血量
    this->life=200;
    this->m_walkingSpeed=1.0;
    this->size=QPoint(-60/2,-180/2);
    this->targetPathPoint=startWayPoint->get_nextTravelPoint();
    this->iceLevel=0;
    this->apLevel=0;
}

Draven::Draven(TravelPath *startWayPoint, BaseScene *game, const QPixmap &sprite/* = QPixmap(":/image/enemy1.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/image/enemy1.png")*/)
{
    this->award=320;

    this->pos1=startWayPoint->get_pos();
    this->size=QPoint(-80/2,-104/2);
    this->origionlife=140;//增加血量
    this->life=140;
    this->m_walkingSpeed=2.6;
    this->targetPathPoint=startWayPoint->get_nextTravelPoint();
    this->iceLevel=10;
    this->apLevel=8;
 //   qDebug()<<"ok to create an draven enemy!!"<<endl;
}

Yasuo::Yasuo(TravelPath *startWayPoint, BaseScene *game, const QPixmap &sprite/* = QPixmap(":/image/enemy1.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/image/enemy1.png")*/)
{
    this->award=320;
    //this->fireLevel=15;
   // this->iceLevel=15;
   // this->HPdamage=1;
    this->origionlife=100;
    this->life=100;
    this->pos1=startWayPoint->get_pos();
    this->size=QPoint(-138/2,-76/2);
    this->m_walkingSpeed=4.0;
    this->targetPathPoint=startWayPoint->get_nextTravelPoint();
    this->iceLevel=10;
    this->apLevel=8;
}
