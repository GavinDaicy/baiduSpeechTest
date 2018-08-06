#ifndef TESTSPEECH02_H
#define TESTSPEECH02_H

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QFile>
#include "audioutil.h"
#include "speechutil.h"

class testSpeech02 : public QWidget
{
	Q_OBJECT

public:
	testSpeech02(QWidget *parent = 0);
	~testSpeech02();
protected slots:
	void startRecord();
	void endRecord();

private:
	void initUI();
	void initConnect();

	void changeBtnText(const QString &value);
	void processText(QString &text);
	void beginIdentify();
	void endIdentify();
private:
	QPushButton *m_btnRecord; // 录音按钮
	QTextEdit   *m_edtShow; // 显示录音文字结果

	SpeechUtil m_speech;
	AudioUtil m_audioutil;
};

#endif // TESTSPEECH02_H
