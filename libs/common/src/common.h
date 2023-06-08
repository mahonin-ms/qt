#ifndef COMMON_H
#define COMMON_H


#include <iostream>
#include <time.h>
#include <string.h>
#include <mutex>
#include <vector>
#include <sys/timeb.h>
#include <QVector>
#include <QDataStream>
#include <QtXml>
#include <map>
#include <unordered_map>
#include <list>

namespace versions {
    extern int DATASTREAM;
};

using namespace std;

struct XmlContent{
    string                          tag = "";
    string                          value = "";
    unordered_map<string, string>   attrs;
};

enum TYPE{
    tc = 1,
    ti = 2,
    tu = 3,
    str = 57,
    tr = 5,
    SIZE_TYPE = 5
};

struct VTI{
    int16_t volume = 0;
    int16_t type = 0;
    int32_t id = 0;
    double value = 0;

    bool operator<(const VTI& _vti) const {
        if ( volume == _vti.volume ){
            if ( type == _vti.type ){
                if ( id == _vti.id ) return true;
                return id < _vti.id;
            }
            else{
                return type < _vti.type;
            }
        }
        else{
            return volume < _vti.volume;
        }

        return false;
    }


};
std::ostream& operator<<(ostream& _o, const VTI& _vti);

enum status {
    ok = 0,
    warning,
    fail,
    SIZE
};

std::string                     getTime();
void                            consoleLog(const std::string& msg);
std::string                     runCmd (const char *command);
QVector<QString>                readFile( const std::string& _path );
int8_t                          appendFile( const std::string& _path, const QVector<QString>& _content );
std::vector<std::string>        split( const std::string& _in, const std::string& _separator = " ");
std::list<XmlContent>           readXml(const QDomElement& _e, const QString& _tag);

#endif // COMMON_H
