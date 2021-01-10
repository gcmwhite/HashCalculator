#include "HashTool.hxx"
#include <QFile>
#include <memory>
#include <QtConcurrent>
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
    QtConcurrent::run(this,&HashTool::_start,fileName,md5,sha256);
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
            QCryptographicHash hash(QCryptographicHash::Md5);
            if (hash.addData(file.get())){
                emit signalMsg("MD5：" + hash.result().toHex());
            }else {
                emit signalMsg("读取文件失败");
            }
        }
        if (sha256) {
            QCryptographicHash hash(QCryptographicHash::Sha256);
            if (hash.addData(file.get())){
                emit signalMsg("SHA256：" + hash.result().toHex());
            }else {
                emit signalMsg("读取文件失败");
            }
        }
    }else {
        emit signalMsg("文件打开失败");
    }
}
