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
	// 判断本地设备是否支持该格式
	QAudioDeviceInfo audioDeviceInfo = QAudioDeviceInfo::defaultInputDevice();
	// 判断本地是否有录音设备;
	if (!audioDeviceInfo.isNull())
	{
		m_file.setFileName(filename);
		m_file.open(QIODevice::WriteOnly | QIODevice::Truncate);

		// 设置音频文件格式;
		QAudioFormat format;
		// 设置采样频率;
		format.setSampleRate(16000);
		// 设置通道数;
		format.setChannelCount(1);
		// 设置每次采样得到的样本数据位值;
		format.setSampleSize(16);
		// 设置编码方法;
		format.setCodec("audio/pcm");
		// 设置采样字节存储顺序;
		//format.setByteOrder(QAudioFormat::LittleEndian);
		// 设置采样类型;
		//format.setSampleType(QAudioFormat::UnSignedInt);

		// 判断当前设备设置是否支持该音频格式;
		if (!audioDeviceInfo.isFormatSupported(format))
		{
			format = audioDeviceInfo.nearestFormat(format);
		}
		// 开始录音;
		m_audioInput = new QAudioInput(format, this);
		m_audioInput->start(&m_file);
	}
	else
	{
		// 没有录音设备;
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

