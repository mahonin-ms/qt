#include "server.h"
#include <regex>

Server::Server(string _basePath, QMainWindow*   _mainWindow ){
    basePath = _basePath;
    mainWin = _mainWindow;
    QVector<QString>    _config;
    if ( QFile::exists( QString::fromStdString( _basePath + "/config" ) ) ) {
        _config = readFile(_basePath + "/config" );
    } else
        _config = readFile("../../resources/config");
    QString _dataBasePath = "../../resources/DataBase";

    for(const auto& _row: _config ){
        if ( _row.contains("server.port") ){
            port = _row.split("=")[1].toInt();
        } else if ( _row.contains("DataBase") ){
            auto _trim = _row.trimmed();
            _dataBasePath = _trim.split("=")[1].trimmed();

            if ( _dataBasePath.contains("$") ){
                int         _start = _dataBasePath.indexOf("$");
                int         _end = _dataBasePath.indexOf("/");
                QString     _variable = _dataBasePath.mid(_start + 1, _end - 1);
                const char* _value = getenv( _variable.toStdString().c_str() );
                _dataBasePath.replace( _start, _end, _value );

            }
        }
    }
    qTcpServer = std::make_shared<QTcpServer>(this);
    db = make_shared<Db>();
    if ( !_dataBasePath.isEmpty() ){
        db->setPathNciDb( _dataBasePath.toStdString() );
    }
    dbLoad  =  db->readDb() == status::ok ? true : false;

    connect( qTcpServer.get(), &QTcpServer::newConnection, this, &Server::newConnection );
    if( !qTcpServer->listen(QHostAddress::Any, port) ){
        consoleLog("Сервер не запущен на порту " + std::to_string(port) );
    } else {
        consoleLog("Сервер запущен на порту " + std::to_string(port) );
    }

}

Server::~Server() {

    consoleLog("Сервер " + std::to_string(port) + " остановлен");
    qTcpServer->close();

}

shared_ptr<Db> Server::getDb() const
{
    return db;
}

int16_t Server::getPort() const
{
    return port;
}

bool Server::isLoadedDb() const {
    return dbLoad;

}

void Server::newConnection() {
    QTcpSocket* _sock = qTcpServer->nextPendingConnection();
    _sock->write("Hello, World!!! I am echo server!\r\n");
    consoleLog("Подключение клиента " + static_cast<QAbstractSocket*>(_sock)->peerName().toStdString() );
}

