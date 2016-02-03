#ifndef PIANOSCENE_H
#define PIANOSCENE_H

#include <QGraphicsScene>

class PianoKey;

class PianoHandler
{
public:
    virtual ~PianoHandler(){}

    virtual void noteOn(const short note, const int vel) = 0;
    virtual void noteOff(const short note, const int vel) = 0;
};

class PianoScene : public QGraphicsScene
{
    Q_OBJECT

public:
    PianoScene(const short baseOctave, const short numKeys,
               const short startKey, QColor const &keyPressedColor = QColor(),
               QObject *parent = 0);
    QSize sizeHint() const;
    PianoHandler* getPianoHandler() const { return m_handler; }
    void setPianoHandler(PianoHandler* handler) { m_handler = handler; }

    void keyOn(short const note);
    void keyOff(short const note);

    void showNoteOn(short const note, QColor color, int velocity = -1);

signals:
    void noteOn(short n, int v);
    void noteOff(short n, int v);

protected:
    void showKeyOn( PianoKey* key, QColor color, int velocity, bool setFromPol = false );
    void showKeyOn( PianoKey* key, int vel );
    void showKeyOff(PianoKey* key, int);
    void keyOn(PianoKey *key);
    void keyOff(PianoKey *key);
    void keyOn(PianoKey *key, qreal pressure);
    void keyOff(PianoKey *key, qreal pressure);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    PianoKey *getKeyFromCoordinate(const QPointF &point) const;

private:
    void hideOrShowKeys();
    void triggerNoteOn(short const note, int const velocity);
    void triggerNoteOff(short const note, int const velocity);
    void setColorFromPolicy(PianoKey *key, int const velocity);
private:
    short m_baseOctave;
    short m_numKeys;
    short m_startKey;
    short m_transpose;
    short m_minNote;
    short m_maxNote;
    bool  m_mouseEnabled;
    bool  m_mousePressed;
    bool  m_velocityTint;
    int   m_velocity;
    PianoHandler *m_handler;
    QColor m_keyPressedColor;

    QHash<short, PianoKey*> m_keys;

};

#endif // PIANOSCENE_H
