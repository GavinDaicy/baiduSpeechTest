#include "fileutil.h"
#include <QFile>

FileUtil::FileUtil(QObject *parent)
	: QObject(parent)
{

}

FileUtil::~FileUtil()
{

}

QByteArray FileUtil::getByteArray(QString filename)
{
	QFile file(filename);
	file.open(QIODevice::ReadOnly);
	QByteArray filedata = file.readAll();
	file.close();
	return filedata;
}
