#include "testspeech02.h"
#include "speechutil.h"
#include "speechconst.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAudioDeviceInfo>
#include <QMessageBox>
#include <QMediaPlayer>

testSpeech02::testSpeech02(QWidget *parent)
	: QWidget(parent)
{
	initUI();
	initConnect();
}

testSpeech02::~testSpeech02()
{

}

void testSpeech02::startRecord()
{
	m_audioutil.startRecord("1.pcm");
	changeBtnText(CUpToEndSpeek);
}

void testSpeech02::endRecord()
{
	changeBtnText(CAnalyzingSpeech);
	beginIdentify();
	m_audioutil.stopRecord();
	QString result = m_speech.identifySpeech("1.pcm");
	m_edtShow->setText(result);
	processText(result);
	QString mp3File = m_speech.composeSpeech(result);
	m_audioutil.play(mp3File);
	changeBtnText(CPressToSpeek);
	endIdentify();
}

void testSpeech02::initUI()
{
	m_btnRecord = new QPushButton();
	m_btnRecord->setText(CPressToSpeek);

	m_edtShow = new QTextEdit();

	QHBoxLayout *hlayout = new QHBoxLayout();
	hlayout->addWidget(m_btnRecord);
	hlayout->addWidget(m_edtShow);
	setLayout(hlayout);
}

void testSpeech02::initConnect()
{
	connect(m_btnRecord, SIGNAL(pressed()), this, SLOT(startRecord()));
	connect(m_btnRecord, SIGNAL(released()), this, SLOT(endRecord()));
}

void testSpeech02::changeBtnText(const QString &value)
{
	m_btnRecord->setText(value);
}

void testSpeech02::processText(QString &text)
{
	if (text.isEmpty())
		text = QString::fromLocal8Bit("您没有说话");
	else
		text = QString::fromLocal8Bit("您说的是 ") + text;
}

void testSpeech02::beginIdentify()
{
	this->setEnabled(false);
}

void testSpeech02::endIdentify()
{
	this->setEnabled(true);
}
