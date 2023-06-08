#include "painter.h"

Painter::Painter(QWidget *parent) :QWidget(parent) {
    painter = new QPainter(this);
    painter->setPen( QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap) );
    //setEnabled(true);
}

Painter::~Painter(){
    delete painter;
    consoleLog("~Painter()");
}

void Painter::draw(int8_t _cnt){
    cnt = _cnt;

    repaint();
}

void Painter::setSimpleColor(const Qt::GlobalColor& value){
    simpleColor = value;
}

void Painter::paintEvent(QPaintEvent* _event){
    Q_UNUSED(_event);
    //QPainter p(this);
    //p.drawEllipse(100, 50, 50, 50);
     if ( simpleColor == Qt::green ){
         painter->setBrush( QBrush(Qt::green, Qt::SolidPattern) );
     } else if ( simpleColor == Qt::red ){
         painter->setBrush( QBrush(Qt::red, Qt::SolidPattern) );
     }
         int8_t  _xDrawRect = 0, _yDrawRect = 50;

     for(int8_t  _i = 1; _i <= cnt; ++_i ){
         if ( _i <= maxFigures ){
             _xDrawRect = 50 * _i;
             _yDrawRect = 50 * _i;
             painter->drawEllipse(_xDrawRect, _yDrawRect, 50, 50);
         }
         else{
             _xDrawRect =  50 * _i - 200;
             _yDrawRect =  50 * _i - 200;
             painter->drawEllipse(_xDrawRect, _yDrawRect, 50, 50);
         }
     }

     painter->end();
    
//    if ( painter ){
//        if ( simpleColor == Qt::green ){
//            painter->setBrush( QBrush(Qt::green, Qt::SolidPattern) );
//        } else if ( simpleColor == Qt::red ){
//            painter->setBrush( QBrush(Qt::red, Qt::SolidPattern) );
//        }
//    }
}

