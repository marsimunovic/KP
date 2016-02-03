#ifndef PIANOKEYBOARD_H
#define PIANOKEYBOARD_H

#include <QGraphicsView>

class PianoScene;

class PianoKeyboard : public QGraphicsView
{
    Q_OBJECT
public:
    PianoKeyboard(QWidget *parent = 0);
    PianoKeyboard(short const baseOctave, short const numKeys, short const startKey, QWidget *parent = 0);
    virtual ~PianoKeyboard();

    QSize sizeHint() const;
    PianoScene* getPianoScene() { return m_scene; }

signals:
    void noteOn(short midiNote, int velocity);
    void noteOff(short midiNote, int velocity);

protected:
    void initalize();
    void initScene(short baseOctave, short numKeys, short startKey, QColor const &c = QColor());
    void resizeEvent(QResizeEvent *event);

private:
    PianoScene *m_scene;
};

#endif // PIANOKEYBOARD_H
