#ifndef SPEECHUTIL_H
#define SPEECHUTIL_H

#include <QObject>

class SpeechUtil : public QObject
{
	Q_OBJECT

public:
	SpeechUtil(QObject *parent = 0);
	~SpeechUtil();

	// 获取token
	QString getToken();
	// 识别语音
	QString identifySpeech(QString filename);
	// 合成语音
	QString composeSpeech(QString text);

private:
	QString getJsonvalue(QByteArray replydata, QString key);

	QString jsonvalueToString(QJsonValue &json_value);

	bool genFileByByteArray(QByteArray replydata, QString filename);

	QString urlEncoding(QString text);
};

#endif // SPEECHUTIL_H
