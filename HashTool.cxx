#include "HashTool.hxx"
#include <QFile>
#include <memory>
#include <QtConcurrent>
#include <QFileInfo>
#include <QCryptographicHash>

HashTool::HashTool()
{
}

HashTool::~HashTool()
{
    QThreadPool::globalInstance()->waitForDone();
}

void HashTool::start(const QString &fileName, bool md5, bool sha256)
{
    this->fileName = fileName;
    md5Byte.clear();
    sha256Byte.clear();
    QtConcurrent::run(this,&HashTool::_start,fileName,md5,sha256);
}

void HashTool::compare(const QString &str)
{
    if (md5Byte.isEmpty() && sha256Byte.isEmpty()) {
        emit signalMsg("请先计算");
        return;
    }
    const QByteArray byte = QByteArray::fromHex(str.toUtf8());
    if (byte == md5Byte) {
        emit signalMsg(QString("文件(%1)MD5相等").arg(QFileInfo(fileName).fileName()));
    }else if (byte == sha256Byte) {
        emit signalMsg(QString("文件(%1)SHA256相等").arg(QFileInfo(fileName).fileName()));
    }else {
        emit signalMsg(QString("文件(%1)MD5与SHA256均不相等").arg(QFileInfo(fileName).fileName()));
    }
}

void HashTool::_start(const QString &fileName, bool md5, bool sha256)
{
    if (!(md5 || sha256)) {
        emit signalMsg("请至少选择一种计算方式");
        return;
    }
    std::unique_ptr<QFile,void(*)(QFile *)> file(new QFile(fileName),[](QFile *f){ f->close(); delete f; });
    if (file->open(QIODevice::ReadOnly)) {
        if (md5) {
            emit signalMsg("开始计算MD5");
            QCryptographicHash hash(QCryptographicHash::Md5);
            file->seek(0);
            if (hash.addData(file.get())){
                md5Byte = hash.result();
                emit signalMsg("MD5：" + md5Byte.toHex());
            }else {
                emit signalMsg("读取文件失败");
            }
        }
        if (sha256) {
            emit signalMsg("开始计算SHA256");
            QCryptographicHash hash(QCryptographicHash::Sha256);
            file->seek(0);
            if (hash.addData(file.get())){
                sha256Byte = hash.result();
                emit signalMsg("SHA256：" + sha256Byte.toHex());
            }else {
                emit signalMsg("读取文件失败");
            }
        }
    }else {
        emit signalMsg("文件打开失败");
    }
}
