#ifndef DB_H
#define DB_H

#include <map>
#include <iostream>
#include <common.h>
#include <QtXml>

using namespace std;


class Db
{
public:
    Db();
    virtual ~Db();

    void                setPathNciDb(const string &value);

    string              getPathNciDb() const;
    status              readDb();
    map<VTI, int32_t>*  getDbByFilter(int8_t _volume);
    map<VTI, int32_t>   getDbByFilter(int8_t _volume, int8_t _type);

private:
    map<int8_t, map<VTI, int32_t>*>    db; // key1 - volume, value1 - [ key2 - type, value2 - id ]
    string      pathNciDb = "../../../resources/DataBase/NciDb/";


};

#endif // DB_H
