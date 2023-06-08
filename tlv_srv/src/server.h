#ifndef SERVER_H
#define SERVER_H

#include <common.h>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMainWindow>
#include <memory>
#include "./model/db/db.h"
#include <QFile>
#include <QDir>

using namespace std;

class Server: public QTcpServer
{
public:
    Server(string _basePath,  QMainWindow*   _mainWindow);
    virtual ~Server();

    shared_ptr<Db>  getDb() const;
    int16_t         getPort() const;
    bool            isLoadedDb() const;

private:
    int16_t                         port = 9989;
    shared_ptr<QTcpServer>          qTcpServer;
    shared_ptr<Db>                  db;
    bool                            dbLoad {false};
    string                          basePath = "";
    QMainWindow*                    mainWin {nullptr};

    public slots:
    void newConnection();


};

#endif // SERVER_H
