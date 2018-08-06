#ifndef AUDIOUTIL_H
#define AUDIOUTIL_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioInput>
#include <QFile>

class AudioUtil : public QObject
{
	Q_OBJECT

public:
	AudioUtil(QObject *parent = 0);
	~AudioUtil();
	void startRecord(QString filename);
	void stopRecord();
	void play(QString file);
protected slots:
	void playerStateChanged(QMediaPlayer::State state);
private:
	bool m_isPlaying;
	QMediaPlayer *m_player;
	QAudioInput *m_audioInput;
	QFile m_file;
};

#endif // AUDIOUTIL_H
