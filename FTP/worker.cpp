#include "worker.h"

worker::worker(QObject *parent) : QObject(parent)
{
    connect(&manager,&QNetworkAccessManager::finished,this,&worker::finished);
}

void worker::upload(QString location, QString path)
{
    qInfo() << "Uploading" << path;
    file.setFileName(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        qInfo() << file.errorString();
        return;
    }
    QUrl url(location);
    //url.setPassword("anonymous");
    //url.setUserName("anonymous");
    //url.setPort(21);
    QNetworkRequest request=QNetworkRequest(url);
    QNetworkReply *reply=manager.put(request,&file);
    wire(reply);
}

void worker::download(QString location, QString path)
{
    qInfo() << "Downloading" << path;
    file.setFileName(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        qInfo() << file.errorString();
        return;
    }
    QUrl url(location);
    //url.setPassword("anonymous");
    //url.setUserName("anonymous");
    //url.setPort(21);
    QNetworkRequest request=QNetworkRequest(url);
    QNetworkReply *reply=manager.get(request);
    wire(reply);
}

void worker::readyRead()
{
    QNetworkReply *reply=qobject_cast<QNetworkReply*>(sender());
    if(reply){
        QByteArray data=reply->readAll();
        file.write(data);
    }
}

void worker::finished(QNetworkReply *reply)
{
    qInfo() << "Finished";
    file.close();
    reply->close();
}

void worker::uploadProgress(qint64 bytesSent, quint64 bytesTotal)
{
    if(bytesTotal<=0) return;
     qInfo() << "Uploading:" << bytesSent << " of " << bytesTotal;
}

void worker::downloadProgress(qint64 bytesReceived, quint64 bytesTotal)
{
    if(bytesTotal<=0) return;
     qInfo() << "Downloading:" << bytesReceived << " of " << bytesTotal;
}

void worker::error(QNetworkReply::NetworkError code)
{
    qInfo() << "Error:" << code;
}

void worker::wire(QNetworkReply *reply)
{
    connect(reply,&QNetworkReply::readyRead,this,&worker::readyRead);
    connect(reply,&QNetworkReply::uploadProgress,this,&worker::uploadProgress);
    connect(reply,&QNetworkReply::downloadProgress,this,&worker::downloadProgress);
    connect(reply,QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),this,&worker::error);
}
