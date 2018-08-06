#ifndef HTTPUTIL_H
#define HTTPUTIL_H

#include <QObject>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>

class HttpUtil : public QObject
{
	Q_OBJECT

public:
	HttpUtil(QObject *parent = 0);
	~HttpUtil();

	int getLastStateCode();

	bool post_syn(const QString &url, QMap<QByteArray, QByteArray> headerdata, QByteArray data, QByteArray &replydata);
private:
	int m_statecode;
};

#endif // HTTPUTIL_H
