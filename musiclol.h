#ifndef MUSICLOL_H
#define MUSICLOL_H

#include <QObject>
#include <QDir>

// 使用绝对路径可以完成声音输出
static const QString s_curDir = "C:/Users/Windows/Documents/MyTowerDefence/musiclol";

class QMediaPlayer;

enum SoundType
{
    //放塔
    AshetowerSound,
    TristowerSound,
    MorgtowerSound,
    //击中敌人声音
    AshehitSound,
    TrishitSound,
    MorghitSound,
    //敌人死亡
    HitenemySound1,
    HitenemySound2,
    HitenemySound3,
    //开场音乐
    GetDoneSound,
    //选择关卡
    showtimeSound,
    chooseSound,


};

class Musiclol : public QObject
{
public:
    explicit Musiclol(QUrl backgroundMusicUrl,QObject *parent = 0);
    void startBGM();
    void stopBGM();
    void playSound(SoundType soundType);
    void playWinSound();
    void playLoseSound();
    QMediaPlayer * getMusic();

private:
    QMediaPlayer *m_backgroundMusic; // 只用来播放背景音乐
    QMediaPlayer *m_winMusic;
    QMediaPlayer *m_loseMusic;
};

#endif // MUSICLOL_H
