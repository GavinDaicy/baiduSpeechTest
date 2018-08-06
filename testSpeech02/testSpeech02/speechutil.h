#ifndef SPEECHUTIL_H
#define SPEECHUTIL_H

#include <QObject>

class SpeechUtil : public QObject
{
	Q_OBJECT

public:
	SpeechUtil(QObject *parent = 0);
	~SpeechUtil();

	// ��ȡtoken
	QString getToken();
	// ʶ������
	QString identifySpeech(QString filename);
	// �ϳ�����
	QString composeSpeech(QString text);

private:
	QString getJsonvalue(QByteArray replydata, QString key);

	QString jsonvalueToString(QJsonValue &json_value);

	bool genFileByByteArray(QByteArray replydata, QString filename);

	QString urlEncoding(QString text);
};

#endif // SPEECHUTIL_H
