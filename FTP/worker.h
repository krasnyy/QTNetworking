#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include<QDebug>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QFile>


class worker : public QObject
{
    Q_OBJECT
public:
    explicit worker(QObject *parent = nullptr);

    void upload(QString location,QString path);
    void download(QString location,QString path);
signals:
public slots:

private slots:
    void readyRead();
    void finished(QNetworkReply *reply);
    void uploadProgress(qint64 bytesSent,quint64 bytesTotal);
    void downloadProgress(qint64 bytesReceived,quint64 bytesTotal);
    void error(QNetworkReply::NetworkError code);
private:
    QNetworkAccessManager manager;
    QFile file;
    void wire(QNetworkReply *reply);
};

#endif // WORKER_H
