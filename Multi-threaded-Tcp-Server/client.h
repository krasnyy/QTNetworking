#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include<QThread>
#include<QTcpSocket>
#include<QRunnable>
#include<QDebug>


class Client : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr,quintptr handle=0);
    void run();

signals:

private:
    quintptr handle;


};

#endif // CLIENT_H
