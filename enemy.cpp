#include "enemy.h"
#include "travelpath.h"
#include "tower.h"
#include "Qpainter"
#include "QDebug"
#include "bloodbar.h"
const QSize Enemy::fixedSize(40, 40);

Enemy::Enemy(TravelPath *nowPoint, Scene*game, const QPixmap &icon )
    : QObject(0)
    , ifFree(false)//初始空闲
    , m_maxHp(40)
    , m_walkingSpeed(2.0)
    , m_rotationSprite(0.0)
    , pos1(nowPoint->get_pos())//坐标赋值
    , targetPathPoint(nowPoint->get_nextTravelPoint())//目标点就是航点列表中的下一个点
    , game(game)
    , icon(icon)
    , size(0,0)
    ,damage(true)
    ,award(50)
{origionlife=80;
 life=80;
}

Enemy::~Enemy()
{
   // attackedTowersList.clear();
    targetPathPoint = NULL;
    game = NULL;
}

void Enemy::setFree()
{
    ifFree = true;
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
    painter->rotate(m_rotationSprite);

    // 绘制敌人
    painter->drawPixmap(offsetPoint, icon);
    painter->restore();
}



void Enemy::move()
{
    if (!ifFree)
        return;

    if (if_collision_inCircle(pos1, 1, targetPathPoint->get_pos(), 1))// 敌人抵达了一个航点
    {

        if (targetPathPoint->get_nextTravelPoint())// 如果还存在下一个点
        {

            pos1 = targetPathPoint->get_pos();//修改当前到达的位置，即到达了一个航点
            targetPathPoint = targetPathPoint->get_nextTravelPoint();//更新目标航点
        }
        else
        {
            // 表示进入基地
           // game->baselife--;
            game->getbaselife();
            game->removedEnemy(this);
          //  game->removedBlood();
           // game->bloodbarList.removeOne();
            return;
        }
    }

    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = targetPathPoint->get_pos();
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
    if (attackTowersList.empty())
        return;

    foreach (Tower *attacker, attackTowersList)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    game->removedEnemy(this);

}

void Enemy::getDamage(int damage)
{
   life -= damage;

    // 阵亡,需要移除
    if (life <= 0)
       {
        game->awardMoney(award);//击杀敌人奖励金钱
        game->getkilled_enemies();//不能确定是不是这里有问题
      //  qDebug()<<"killed ene"<<game->killed_enemies<<endl;
        getRemoved();
    }
}


DogFace1::DogFace1(TravelPath *startWayPoint, Scene *game, const QPixmap &sprite/* = QPixmap(":/image/enemy1.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/image/enemy1.png")*/)
{
    //this->fireLevel=15;
   // this->iceLevel=15;
   // this->HPdamage=1;

    this->pos1=startWayPoint->get_pos();
    this->origionlife=120;//增加血量
    this->life=120;
    this->award=70;
    this->targetPathPoint=startWayPoint->get_nextTravelPoint();

}
Wind::Wind(TravelPath *startWayPoint, Scene *game, const QPixmap &sprite/* = QPixmap(":/image/enemy2.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/image/enemy2.png")*/)
{
   // this->enemyKind=2;
  //  this->award=250;
   // this->m_maxHp = 75;
    this->origionlife=150;
    this->life=150;
  //  this->m_currentHp = 75;
  //  this->antiSlowspeed=2.0;
    this-> m_walkingSpeed=1.8;
   // this->fireLevel=20;
   // this->iceLevel=10;
   // this->HPdamage=1;
    this->m_rotationSprite = 0.0;
    this->pos1=startWayPoint->get_pos();
    this->size=QPoint(-114/2,-86/2);
    this->award=150;
    this->targetPathPoint=startWayPoint->get_nextTravelPoint();
}

Nashor::Nashor(TravelPath *startWayPoint, Scene *game, const QPixmap &sprite/* = QPixmap(":/image/enemy1.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/image/enemy1.png")*/)
{
    //this->fireLevel=15;
   // this->iceLevel=15;
   // this->HPdamage=1;
    this->award=300;
    this->pos1=startWayPoint->get_pos();
    this->origionlife=200;//增加血量
    this->life=200;
    this->m_walkingSpeed=1.0;
    this->size=QPoint(-60/2,-180/2);
    this->targetPathPoint=startWayPoint->get_nextTravelPoint();
}

Draven::Draven(TravelPath *startWayPoint, Scene *game, const QPixmap &sprite/* = QPixmap(":/image/enemy1.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/image/enemy1.png")*/)
{
    this->award=320;
    //this->fireLevel=15;
   // this->iceLevel=15;
   // this->HPdamage=1;

    this->pos1=startWayPoint->get_pos();
    this->size=QPoint(-80/2,-104/2);
    this->origionlife=140;//增加血量
    this->life=140;
    this->m_walkingSpeed=2.6;
    this->targetPathPoint=startWayPoint->get_nextTravelPoint();
}

Yasuo::Yasuo(TravelPath *startWayPoint, Scene *game, const QPixmap &sprite/* = QPixmap(":/image/enemy1.png")*/)
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
}
