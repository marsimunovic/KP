#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "videowidget.h"

#include <QWidget>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QLabel;
class QMediaPlaylist;
class QModelIndex;
class QPushButton;
class QSlider;
class QVideoProbe;
QT_END_NAMESPACE

class PlaylistModel;

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

signals:
    void fullScreenChanged(bool fullScreen);

private slots:
    void open();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);
    void metaDataChanged();

    void previousClicked();

    void seek(int seconds);
    void jump(const QModelIndex &index);
    void playlistPositionChanged(int);

    void statusChanged(QMediaPlayer::MediaStatus status);
    void bufferingProgress(int progress);
    void videoAvailableChanged(bool available);

    void displayErrorMessage();
    void addToPlaylist(QStringList const &fileNames);
#ifndef PLAYER_NO_COLOROPTIONS
    void showColorDialog();
#endif

private:
    void setTrackInfo(QString const &info);
    void setStatusInfo(QString const &info);
    void handleCursor(QMediaPlayer::MediaStatus status);
    void updateDurationInfo(qint64 currentInfo);

    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    VideoWidget *videoWidget;
    QLabel *coverLabel;
    QSlider *slider;
    QLabel *labelDuration;
    QPushButton *fullScreenButton;
#ifndef PLAYER_NO_COLOROPTIONS
    QPushButton *colorButton;
    QDialog *colorDialog;
#endif

    PlaylistModel *playlistModel;
    QAbstractItemView *playlistView;
    QString trackInfo;
    QString statusInfo;
    qint64 duration;
};

#endif // VIDEOPLAYER_H
