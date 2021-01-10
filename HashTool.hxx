#pragma once

#include <QObject>

class HashTool : public QObject
{
    Q_OBJECT
public:
    explicit HashTool();
    ~HashTool();
    Q_INVOKABLE void start(const QString& fileName,bool md5,bool sha256);

protected:
    void _start(const QString& fileName,bool md5,bool sha256);

signals:
    void signalMsg(const QString& msg);
};

