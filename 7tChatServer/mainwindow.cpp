#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // задаем мин размеры главного окна
    this->setMinimumHeight(480);
    this->setMinimumWidth(640);

    QMenuBar* menuBar = new QMenuBar;
    QMenu* users = new QMenu("&Users");
    QMenu* messages = new QMenu("&Messages");
    menuBar->addMenu(users);
    menuBar->addMenu(messages);

    layoutMain = new QVBoxLayout();
    QWidget* widget = new QWidget();
    widget->setLayout(layoutMain);
    setCentralWidget(widget);
    layoutMain->setMenuBar(menuBar);

    layoutT = new QVBoxLayout();
    layoutMain->addLayout(layoutT);
    layoutB = new QHBoxLayout();
    buttonDelete = new QPushButton("Delete");
    buttonRefresh = new QPushButton("Refresh");
    layoutB->addWidget(buttonDelete);
    layoutB->addWidget(buttonRefresh);
    layoutMain->addLayout(layoutB);

    // запускаем сервер, порт 7077
    Server tChatServer(7077);

    tableUsers = new QTableView;

    modelU4View = new QSqlTableModel(this, tChatServer.db);
    modelU4View->setTable("Users");
    modelU4View->select();
    tableUsers->setModel(modelU4View);

    layoutT->addWidget(tableUsers);

    QObject::connect(buttonDelete, SIGNAL(clicked(bool)), this, SLOT(on_buttonDelete_clicked()));
    QObject::connect(buttonRefresh, SIGNAL(clicked(bool)), this, SLOT(on_buttonRefresh_clicked()));
    QObject::connect(tableUsers, SIGNAL(clicked(QModelIndex)), this, SLOT(on_tableUsers_clicked(QModelIndex)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_buttonDelete_clicked()
{
    modelU4View->removeRow(row);
}

void MainWindow::on_buttonRefresh_clicked()
{
    modelU4View->setTable("Users");
    modelU4View->select();
    tableUsers->setModel(modelU4View);
}

void MainWindow::on_tableUsers_clicked(const QModelIndex &index)
{
    row = index.row();
}
