#include "speechutil.h"
#include "httputil.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "fileutil.h"
#include <QTextCodec>
#include <QJsonParseError>
#include <QJsonArray>
#include <QFile>
#include <QHostInfo>
#include "speechconst.h"

SpeechUtil::SpeechUtil(QObject *parent)
	: QObject(parent)
{

}

SpeechUtil::~SpeechUtil()
{

}

QString SpeechUtil::getToken()
{
	QString url = CBaiduTokenUrl;
	QByteArray requestdata, replydata;
	QString sRequestdata = CBaiduTokenData.arg(CBaiduClientId).arg(CBaiduClientSecret);
	requestdata.append(sRequestdata);
	QMap<QByteArray, QByteArray> headers;
	headers.insert(QString("Content-Type").toLatin1(), QString("application/json").toLatin1());
	HttpUtil httputil;
	bool success = httputil.post_syn(url, headers, requestdata, replydata);
	if (success)
	{
		QString key = "access_token";
		return getJsonvalue(replydata, key);
	}
	return "";
}

QString SpeechUtil::identifySpeech(QString filename)
{
	// 文件生成二进制
	QByteArray filedata = FileUtil::getByteArray(filename);
	// 请求百度语音 获取Response
	QString url = QString(CBaiduIdentfySpeechUrl).arg(QHostInfo::localHostName()).arg(getToken());
	QMap<QByteArray, QByteArray> headers;
	headers.insert(QString("Content-Type").toLatin1(), QString("audio/pcm;rate=16000").toLatin1());
	HttpUtil http;
	QByteArray replydata;
	bool success = http.post_syn(url, headers, filedata, replydata);
	// 根据Response获取识别结果
	if (success)
	{
		QString key = "result";
		QString result = getJsonvalue(replydata, key);
		return result;
	}
	return "";
}

QString SpeechUtil::composeSpeech(QString text)
{
	// 对要合成文本编码
	QString text_encoding = urlEncoding(urlEncoding(text));
	// 访问百度云合成音频
	QString url = CBaiduComponseSpeechUrl;
	QString sRequestData = QString(CBaiduComponseSpeechData).arg(text_encoding).arg(QHostInfo::localHostName()).arg(getToken());
	QByteArray requestdata;
	requestdata.append(sRequestData);
	HttpUtil http;
	QByteArray replydata; 
	QMap<QByteArray, QByteArray> headers;
	bool success = http.post_syn(url, headers, requestdata, replydata);
	// 根据Response获取识别结果
	if (success)
	{
		// 写入文件
		QString filename = "1.mp3";
		bool gened = genFileByByteArray(replydata, filename);
		if (gened)
			return filename;
		else
			return "";
	}
	return "";
}

QString SpeechUtil::urlEncoding(QString text)
{
	QByteArray ba = QUrl::toPercentEncoding(text);
	return QString(ba);
}

QString SpeechUtil::getJsonvalue(QByteArray replydata, QString key)
{
	QJsonParseError jsonerror;
	QJsonDocument json_document = QJsonDocument::fromJson(replydata, &jsonerror);
	if (jsonerror.error == QJsonParseError::NoError)
	{
		if (json_document.isObject())
		{
			QJsonObject json_object = json_document.object();
			if (json_object.contains(key))
			{
				QJsonValue json_value = json_object.value(key);
				QString svalue = jsonvalueToString(json_value);
				return svalue;
			}
		}
	}
	return "";
}

QString SpeechUtil::jsonvalueToString(QJsonValue &json_value)
{
	QString svalue;
	if (json_value.isString()){
		svalue = json_value.toString();
	}
	else if (json_value.isArray()){
		QJsonArray arr = json_value.toArray();
		for each (QJsonValue value in arr)
		{
			svalue = svalue + ";" + jsonvalueToString(value);
		}
		svalue = svalue.right(svalue.size() - 1);
	}				
	return svalue;
}

bool SpeechUtil::genFileByByteArray(QByteArray replydata, QString filename)
{
	QFile file(filename);
	bool success = file.open(QIODevice::WriteOnly | QIODevice::Truncate);
	if (success)
	{
		file.write(replydata);
		file.close();
		return true;
	}
	return false;
}
