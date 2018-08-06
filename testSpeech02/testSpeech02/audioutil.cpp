#include "audioutil.h"
#include <QMessageBox>

AudioUtil::AudioUtil(QObject *parent)
	: QObject(parent)
{
	m_isPlaying = false;
	m_audioInput = NULL;
}

AudioUtil::~AudioUtil()
{

}

void AudioUtil::startRecord(QString filename)
{
	// �жϱ����豸�Ƿ�֧�ָø�ʽ
	QAudioDeviceInfo audioDeviceInfo = QAudioDeviceInfo::defaultInputDevice();
	// �жϱ����Ƿ���¼���豸;
	if (!audioDeviceInfo.isNull())
	{
		m_file.setFileName(filename);
		m_file.open(QIODevice::WriteOnly | QIODevice::Truncate);

		// ������Ƶ�ļ���ʽ;
		QAudioFormat format;
		// ���ò���Ƶ��;
		format.setSampleRate(16000);
		// ����ͨ����;
		format.setChannelCount(1);
		// ����ÿ�β����õ�����������λֵ;
		format.setSampleSize(16);
		// ���ñ��뷽��;
		format.setCodec("audio/pcm");
		// ���ò����ֽڴ洢˳��;
		//format.setByteOrder(QAudioFormat::LittleEndian);
		// ���ò�������;
		//format.setSampleType(QAudioFormat::UnSignedInt);

		// �жϵ�ǰ�豸�����Ƿ�֧�ָ���Ƶ��ʽ;
		if (!audioDeviceInfo.isFormatSupported(format))
		{
			format = audioDeviceInfo.nearestFormat(format);
		}
		// ��ʼ¼��;
		m_audioInput = new QAudioInput(format, this);
		m_audioInput->start(&m_file);
	}
	else
	{
		// û��¼���豸;
		QMessageBox::information(NULL, tr("Record"), tr("Current No Record Device"));
	}
}

void AudioUtil::stopRecord()
{
	if (m_audioInput != NULL)
	{
		m_audioInput->stop();
		m_file.close();
		delete m_audioInput;
		m_audioInput = NULL;
	}
}

void AudioUtil::play(QString file)
{
	if (file.isEmpty())
		return;
	if (!m_isPlaying)
	{
		m_isPlaying = true;
		m_player = new QMediaPlayer();
		m_player->setMedia(QUrl::fromLocalFile(file));
		m_player->setVolume(30);
		m_player->play();
		connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(playerStateChanged(QMediaPlayer::State)));
	}
}

void AudioUtil::playerStateChanged(QMediaPlayer::State state)
{
	if (state == QMediaPlayer::StoppedState)
	{
		m_player->deleteLater();
		m_isPlaying = false;
	}
}

