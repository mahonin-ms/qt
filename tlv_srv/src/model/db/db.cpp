#include "db.h"

Db::Db(){
}

Db::~Db() {

}

status Db::readDb() {
    QDir            _nciDbDir;
    _nciDbDir.setFilter( QDir::Dirs );
    _nciDbDir.setCurrent( QString::fromStdString(pathNciDb + "/NciDb/" ) );
    QStringList _volumes = _nciDbDir.entryList();
    for(const auto& _v : _volumes) {
        QFile           _file( QString::fromStdString(pathNciDb + "/NciDb/" + _v.toStdString() + "/db.xml") );
        QDomDocument    _doc;
        if ( _file.open(QIODevice::ReadOnly | QIODevice::Text) ){
            consoleLog("Загрузка параметров направления #" + _v.toStdString() );
            if ( _doc.setContent( &_file ) ){
                QDomElement _root = _doc.firstChildElement();
                auto _content = readXml(_root, "p");
                for(const auto& _el: _content ){
                    map<VTI, int32_t>*   _volume { nullptr };
                     int            __volume = atoi( _el.attrs.at("volume").c_str() );

                    if ( db.count(__volume) > 0 ) {
                        _volume = db.at(__volume);
                    } else {
                        _volume = new map<VTI, int32_t>();
                        db.emplace( __volume, _volume );
                    }
                    VTI _vti;
                    _vti.volume = atoi( _el.attrs.at("volume").c_str() );
                    _vti.type = atoi( _el.attrs.at("type").c_str() );
                    _vti.id = atoi( _el.value.c_str() );
                    cout << "VTI:" << _vti ;
                    _volume->emplace( _vti, 1 );

                }


            }
            _file.close();
        }
    }

    if( db.size() > 0 ) return status::ok;

    return status::fail;
}

map<VTI, int32_t>*  Db::getDbByFilter(int8_t _volume){
    if ( db.count(_volume) != 0 ) return db[_volume];

    return nullptr;
}

map<VTI, int32_t>   Db::getDbByFilter(int8_t _volume, int8_t _type){
    map<VTI, int32_t> _dbByVolumeAndType;
    if ( db.count(_volume) != 0 ) {
        const auto _v = db[ _volume ];
        for(const auto& _item: *_v){
            if ( _item.first.type == _type ){
                VTI _vti(_item.first);
                _dbByVolumeAndType[ _vti ] = _vti.value;
            }
        }
    }

    return _dbByVolumeAndType;
}


string Db::getPathNciDb() const
{
    return pathNciDb;
}

void Db::setPathNciDb(const string &value)
{
    pathNciDb = value;
}


