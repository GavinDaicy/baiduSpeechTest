#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QObject>

class FileUtil : public QObject
{
	Q_OBJECT

public:
	FileUtil(QObject *parent = 0);
	~FileUtil();

	static QByteArray getByteArray(QString filename);
private:
	
};

#endif // FILEUTIL_H
