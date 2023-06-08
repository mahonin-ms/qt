#include "common.h"
#include <QFile>
#include <QTextStream>
#include <fstream>
#include <sstream>


namespace versions {
    int DATASTREAM = QDataStream::Qt_5_12;
};


std::string                     getTime(){
    time_t              _now = time(0);
    tm*                 _infoTime = gmtime(&_now);
    timeb               _tb; // для мсек
    ftime(&_tb);
    char                _ts_pretty[4096];
    memset(_ts_pretty, '0', sizeof(_ts_pretty));
    sprintf( _ts_pretty, "[ %04d/%02d/%02d %02d:%02d:%02d.%d ] ", 1900 + _infoTime->tm_year, 1 + _infoTime->tm_mon, _infoTime->tm_mday, _infoTime->tm_hour, _infoTime->tm_min, _infoTime->tm_sec, _tb.millitm );
    std::string         _Ts( _ts_pretty );
    memset(_ts_pretty, '0', sizeof(_ts_pretty));
    return _Ts;
}

void                            consoleLog(const std::string& msg){
    std::mutex                     _mutex;
    std::lock_guard<std::mutex>     _lock(_mutex);
    std::string         message = "";
    message += getTime();
    message += msg;
    std::cout<<message<<std::endl<<std::flush;
    message.clear();
}

std::string                     runCmd (const char *command) {
    char            _tmpfile[] = "/tmp/qt_XXXXXX";
    mkstemp( _tmpfile);
    std::string     _command = command;
    std::string     cmd = _command + " >> " + _tmpfile;
    std::system( cmd.c_str() );
    std::ifstream   _file( _tmpfile, std::ios::in | std::ios::binary );
    std::string     _stdOut;
    if (_file) {
        while ( !_file.eof() ) _stdOut.push_back( _file.get() );
        _file.close();
    }
    std::remove(_tmpfile);
    return _stdOut;
}

QVector<QString>                readFile(const std::string &_path) {
    QVector<QString>        _content;
    QFile                   _f( _path.c_str() );
    QTextStream             _stream( &_f );

    if ( ! _f.open(QIODevice::ReadOnly) ) {
        return _content;
    }

    while( !_stream.atEnd() ){
        QString _row = _stream.readLine();
        _content += _row;
    }

    _f.close();
    return _content;
}

int8_t                          appendFile(const std::string& _path, const QVector<QString> &_content) {

    QFile   _f( _path.c_str() );
    if ( _f.exists() ){
        _f.open( QIODevice::Append| QIODevice::Text );
    }
        QTextStream _stream( &_f );
        for( const auto& _row: _content ){
            _stream << _row;
        }


    _f.close();



    return 0;

}

std::vector<std::string>        split( const std::string& _in, const std::string& _separator){
    std::vector<std::string> _return;

    size_t _index = 0l;
    std::string __in = _in;
    while( (_index = __in.find(_separator)) != std::string::npos ){
        _return.emplace_back( __in.substr(0, _index) );
       __in =  __in.substr( _index + _separator.size(), __in.size() - _index );
    }
    _return.emplace_back( __in );


    return _return;

}

std::list<XmlContent>           readXml(const QDomElement& _e, const QString& _tag) {
        std::list<XmlContent>   _content;
        QDomNodeList nodes = _e.elementsByTagName(_tag);
        for( int  _i = 0; _i < nodes.count(); _i++ ){
            QDomNode _node = nodes.at(_i);
            if ( _node.isElement() ){
                QDomElement _el = _node.toElement();
                if ( _el.tagName() == _tag ){

                    XmlContent _xmlElement;
                    _xmlElement.tag = _el.tagName().toStdString();
                    _xmlElement.value = _el.text().toStdString();
                    if ( _el.hasAttributes() ) {
                        QDomNamedNodeMap _attributes = _el.attributes();
                        for(int _i = 0; _i < _attributes.count(); ++_i ){
                            QDomAttr _attr = _attributes.item( _i ).toAttr();
                            _xmlElement.attrs[ _attr.name().toStdString() ] = _attr.value().toStdString();
                            //cout << _attr.name().toStdString() << " " << _attr.value().toStdString() << endl;
                        }


                    }
                    _content.push_back( _xmlElement );
                    //cout << _el.text().toStdString() << endl                }
            }
                //cout << "Прочитан #" << _i << " тэг" << endl;
            }

        }

        return _content;
}

std::ostream& operator<<(ostream& _o, const VTI& _vti){
   _o << _vti.volume << "." << _vti.type << "." << _vti.id << endl;
   return _o;

}
