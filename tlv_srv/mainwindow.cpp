#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cstdlib>
#include <common.h>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QDir _dir("./");
    basePath = _dir.absolutePath().toStdString();
    QHBoxLayout*    _boxLayout = new QHBoxLayout;
    centralWidget()->setLayout(_boxLayout);
    if ( auto   _btn = this->findChild<QPushButton*>("btn_startServer") ){
        elements.btn_start = _btn;
        _boxLayout->addWidget( _btn );
    }
    if ( auto   _btn = this->findChild<QPushButton*>("btn_stopServer") ){
        elements.btn_stop = _btn;
        _boxLayout->addWidget( _btn );
    }
    if ( auto _menuBar = this->findChild<QMenuBar*>("menubar") ){
        elements.menuBar = new Elements::MenuBar();
        elements.menuBar->qmenuBar = _menuBar;
        if ( auto menu_1 = _menuBar->findChild<QMenu*>("menu_1") ){
            if ( auto menu_settings = menu_1->findChild<QMenu*>("settings") ){
                Elements::MenuBar::Menu* _menu_settings = new Elements::MenuBar::Menu();
                _menu_settings->qmenu = menu_settings;
                _menu_settings->name = menu_settings->objectName().toStdString();
                elements.menuBar->menu.push_back( _menu_settings );
                auto _view = formVariables.findChild<QListWidget*>("view");
                _menu_settings->elements.push_back( _view );
                connect(menu_settings, &QMenu::triggered, this, &MainWindow::trigered_action_menu_settings);

            }
        }
    }
//    if ( auto _graphicsView = this->findChild<QGraphicsView*>("graphicsView") ) {
//        elements.graficsView = _graphicsView;
//    }
        if ( auto _graphicsView = this->findChild<QWidget*>("drawWidget") ) {
            elements.drawWidget = _graphicsView;
            painter = new Painter( _graphicsView );
            _boxLayout->addWidget( painter );
        }

}

MainWindow::~MainWindow() {
    delete ui;
}

MainWindow::Elements::MenuBar::Menu*    MainWindow::getMenuByName(const string &_name){
    Elements::MenuBar::Menu*    _find = { nullptr };
    for(const auto& _item: elements.menuBar->menu ){
        if ( _item->name == _name ) {
            _find = _item;
            break;
        }
    }

    return _find;

}

void MainWindow::on_btn_startServer_clicked() {
    //srv = std::make_shared<Server>();
    srv = new Server( basePath, this );
    if ( elements.btn_start ){
        elements.btn_start->setEnabled( false );
        elements.btn_stop->setEnabled( true );
        if ( painter && srv->isLoadedDb() ) {
            painter->setSimpleColor( Qt::green );
            const auto& _volume2 = srv->getDb()->getDbByFilter(2, TYPE::tc);
            painter->draw( _volume2.size() );
        }
    }
}

void MainWindow::on_btn_stopServer_clicked() {
    if ( srv ){
        delete srv;
        srv = nullptr;
        elements.btn_start->setEnabled( true );
        elements.btn_stop->setEnabled( false );
        if ( painter ) {
            painter->setSimpleColor( Qt::red );
            //painter->draw(srv->getDb()->getDbByFilter(1)->size());
        }
    }
}

void MainWindow::trigered_action_menu_settings(QAction *_action){
    if ( _action->text() == "Переменные" ){
        consoleLog("Нажали кнопку Переменные в меню");
        formVariables.setVisible( true );
        const auto _widget = getMenuByName("settings");

        for(const auto& _w : _widget->elements ){
            if ( _w->objectName() == "view" ){
                QListWidget* _wList = static_cast<QListWidget*>(_w);
                _wList->clear();
                        if ( QFile::exists( QString::fromStdString( basePath + "/config" ) ) ) {
                            auto _config = readFile( basePath + "/config" );
                            std::for_each(_config.begin(), _config.end(), [&_wList](QString& _row){
//                                if ( _row.contains("$") ){
//                                    QStringList _array = _row.split("$");
//                                    QString _var = _array.at(0).split("/")[1];
//                                    if ( !_var.isEmpty() ){
//                                        const char* _value = getenv( _var.toStdString().c_str() );
//                                        consoleLog("tick");
//                                    }
//                                }
                                    _wList->addItem( _row );
                            });
                        }

                }
            }
    }

}

int8_t MainWindow::drawDb() {
    shared_ptr<Db>  _db = srv->getDb();
    return 0;

}
