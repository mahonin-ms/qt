#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <server.h>
#include <memory>
#include <QPushButton>
#include <QListWidget>
#include <QGraphicsView>
#include <QPainter>
#include <list>
#include "./model/painter.h"
#include <../forms/variables.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    struct Elements{

        struct MenuBar{

            struct Menu{
                string              name = "";
                QAction*            action { nullptr };
                QMenu*              qmenu { nullptr };
                list<QWidget*>      elements;
            };

            QMenuBar*    qmenuBar{nullptr};
            list<Menu*>  menu; // menu_1->settings
        };

        QPushButton*    btn_start { nullptr };
        QPushButton*    btn_stop { nullptr };
        MenuBar*        menuBar { nullptr };
        //QGraphicsView*  graficsView { nullptr};
        //QGraphicsScene* grphicsScene;
        QWidget*           drawWidget { nullptr };
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Elements::MenuBar::Menu*    getMenuByName(const string& _name);
    int8_t                      drawDb();

private slots:

    void on_btn_startServer_clicked();

    void on_btn_stopServer_clicked();

    void trigered_action_menu_settings(QAction* _action);

private:
    Ui::MainWindow *ui;
    //std::shared_ptr<Server> srv;
    Server*     srv {nullptr};
    Elements    elements;
    Variables   formVariables;
    string      basePath = "";
    Painter*    painter {nullptr};
};
#endif // MAINWINDOW_H

