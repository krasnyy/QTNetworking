#include <QCoreApplication>
#include "worker.h"
#include <QDebug>
#include <QDateTime>

void upload(worker* worker)
{
    QString location = "ftp://speedtest.tele2.net/upload/VoidRealms-" + QString::number(QDateTime::currentSecsSinceEpoch()) + ".bin";
    QString path = "path";
    worker->upload(location,path);

}

void download(worker* worker)
{
    QString location = "ftp://speedtest.tele2.net/512KB.zip";
    QString path = "path";
    worker->download(location,path);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    worker worker;
    upload(&worker);
    download(&worker);

    return a.exec();
}
