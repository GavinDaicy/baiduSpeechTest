#include "httputil.h"
#include <qeventloop.h>
#include <QTextCodec>

HttpUtil::HttpUtil(QObject *parent)
	: QObject(parent)
{
	m_statecode = 0;
}

HttpUtil::~HttpUtil()
{

}

int HttpUtil::getLastStateCode()
{
	return m_statecode;
}

bool HttpUtil::post_syn(const QString &url, QMap<QByteArray, QByteArray> headerdata, QByteArray data, QByteArray& replydata)
{
	QNetworkAccessManager manager;
	QNetworkRequest request;
	request.setUrl(QUrl(url));
	QMapIterator<QByteArray, QByteArray> map(headerdata);
	while (map.hasNext()) {
		map.next();
		request.setRawHeader(map.key(), map.value());
	}
	QNetworkReply *reply = manager.post(request, data);
	QEventLoop l;
	connect(reply, SIGNAL(finished()), &l, SLOT(quit()));
	l.exec();
	if (reply != nullptr && reply->error() == QNetworkReply::NoError)
	{
		replydata = reply->readAll();
		QString ss = reply->header(QNetworkRequest::ContentTypeHeader).toString();
		m_statecode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		return true;
	}
	else{
		QNetworkReply::NetworkError error = reply->error();
		QString serror = reply->errorString();
		return false;
	}
}

