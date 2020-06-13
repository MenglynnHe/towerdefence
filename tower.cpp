#include "tower.h"
#include "scene.h"
#include "QDebug"
#include "bullet.h"
const QSize Tower::ms_fixedSize(70, 70);
Tower::Tower(QPoint pos,BaseScene * game, const QPixmap &sprite):
     attackRange(180)
    , damage(10)
    , pos(pos)
    , icon(sprite)
    , game(game)
    , attackRate(1000)
    , m_level(1)
{    choosed_enemy=nullptr;
    attackTimer = new QTimer(this);
    connect(attackTimer, SIGNAL(timeout()), this, SLOT(startShooting()));//每隔一定时间就开始攻击
}
Tower::~Tower(){
    delete attackTimer;
    attackTimer = NULL;
}
void Tower::draw(QPainter *painter) const
{
    painter->save();//保存画家状态
    painter->setPen(Qt::white);
    // 绘制攻击范围
    painter->drawEllipse(pos, attackRange, attackRange);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint  offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    // 绘制炮塔并选择炮塔
    painter->translate(pos);//画家移动到m_pos
  //  qDebug()<<"translate"<<m_pos.x()<<" "<<m_pos.y()<<endl;
    painter->rotate(rotationIcon);//旋转角度

    painter->drawPixmap(offsetPoint, icon);//从回到左上角开始画塔的图片
   // qDebug()<<offsetPoint<<endl;
    painter->restore();//画家还原位置
}
void Tower::drawelli(QPainter *painter) const{
    painter->drawEllipse(pos, attackRange, attackRange);
}

void Tower::checkEnemyInRange()
{
    if (choosed_enemy)
    {
        // 这种情况下,需要旋转炮台对准敌人
        // 向量标准化??
        QVector2D normalized(choosed_enemy->getpos() - pos);
        normalized.normalize();
        rotationIcon = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;

        // 如果敌人脱离攻击范围,就忘记敌人
        if (!if_collision_inCircle(pos, attackRange, choosed_enemy->getpos(), 1))
            forgiveEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<Enemy *> enemyList = game->enemyList();
        foreach (Enemy *enemy, enemyList)
        {
           // qDebug()<<"what enemis"<<endl;
            if (if_collision_inCircle(pos, attackRange, enemy->getpos(), 1))
            {
                set_attacked_Enemy(enemy);
                break;
            }
        }
    }
}

void Tower::set_attacked_Enemy(Enemy *enemy)
{
    choosed_enemy= enemy;
    attackTimer->start(attackRate);
    choosed_enemy->getAttacked(this);//把该塔加入攻击塔列表中
}

//void Tower::startShooting()
//{
//   // qDebug()<<"i can shoot"<<endl;
//    Bullet *bullet = new Bullet(pos, choosed_enemy->getpos(), damage, choosed_enemy, game);
//    bullet->move();
//    game->addBullet(bullet);


// }


void Tower::targetKilled()
{
    if (choosed_enemy)
        choosed_enemy = NULL;

    attackTimer->stop();//暂停攻击
    rotationIcon= 0.0;
}

void Tower::forgiveEnemy()
{
    choosed_enemy->attackTowersList.removeOne(this);
    if (choosed_enemy)
        choosed_enemy = NULL;

    attackTimer->stop();
    rotationIcon = 0.0;
}
AsheTower::AsheTower(QPoint pos, BaseScene * game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{
    kind=0;
   // attackRate=100;
    toslow=1.0;
}

AsheTower::~AsheTower()
{

}
void AsheTower::startShooting()
{
    Bullet *bullet = new AsheBullet(pos, choosed_enemy->getpos(), damage, choosed_enemy, game,toslow);
    bullet->move();
    game->addBullet(bullet);
}
void AsheTower::upgrade(){
    if (m_level == 18) //5级为最高级
        return;
    m_level+=3;
 //   damage += 5; //每升一个单位级子弹加5点伤害
    attackRate-=100;//攻速加快100
    //减速功能
 //     drawelli(QPainter *painter);
    toslow-=0.12;//每升一级攻速减0.12百分比

}
TristanaTower::TristanaTower(QPoint pos, BaseScene * game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{
    attackRange=150;
    kind=1;


}

TristanaTower::~TristanaTower()
{

}
void TristanaTower::startShooting()
{
    Bullet *bullet = new TrisBullet(pos, choosed_enemy->getpos(), damage, choosed_enemy, game);
    bullet->move();
    game->addBullet(bullet);
}
void TristanaTower::upgrade(){

        if (m_level == 18) //5级为最高级
            return;
        m_level+=3;
        damage += 5; //每升一级子弹加5点伤害
        attackRange+=5;//攻击范围
        attackRate-=100;//攻速加快100
}

MorganaTower::MorganaTower(QPoint pos, BaseScene * game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{
    kind=2;
    attackRange=120;
}

MorganaTower::~MorganaTower()
{

}
void MorganaTower::startShooting()
{
    Bullet *bullet = new MorganaBullet(pos, choosed_enemy->getpos(), damage, choosed_enemy, game);
    bullet->move();
    game->addBullet(bullet);
}
void MorganaTower::upgrade(){

        if (m_level == 18) //5级为最高级
            return;
        m_level+=3;
        damage += 5; //每升一级子弹加5点伤害
       //能不能实现控敌人一段时间
        attackRange+=5;
}
