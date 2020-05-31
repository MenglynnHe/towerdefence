#ifndef COPY_H
#define COPY_H

#include "QLabel"
#include "QMovie"


class Copy : public QLabel
{
public:
    Copy(QLabel * parent =0);
    ~Copy();
};

class AsheTowerCopy :public Copy
{
public:
    AsheTowerCopy(QLabel *parent =0);
    ~AsheTowerCopy();
private:
    QMovie * copypic= new QMovie(":/picture/ashecopy.jpg");
};

class TristanaTowerCopy :public Copy
{
public:
    TristanaTowerCopy(QLabel *parent =0);
    ~TristanaTowerCopy();
private:
    QMovie * copypic= new QMovie(":/picture/tristana.jpg");
};

class MorganaTowerCopy :public Copy
{
public:
    MorganaTowerCopy(QLabel *parent =0);
    ~MorganaTowerCopy();
private:
    QMovie * copypic= new QMovie("://tower/mogana.png");
};
#endif // COPY_H
