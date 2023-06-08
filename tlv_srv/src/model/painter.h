#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QPainter>
#include <common.h>

class Painter : public QWidget
{
    Q_OBJECT
public:
    explicit    Painter(QWidget *parent = nullptr);
    virtual     ~Painter();
    void        draw(int8_t _cnt);

    void        setSimpleColor(const Qt::GlobalColor&   value);

private:
    QPainter*           painter;
    Qt::GlobalColor     simpleColor;
    int8_t              cnt = 0;
    void                paintEvent(QPaintEvent* _event) override;
    const int8_t        maxFigures = 4;

signals:

};

#endif // PAINTER_H
