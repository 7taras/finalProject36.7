#include <QCoreApplication>
#include "server.h"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QVector>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // запускаем сервер, порт 7077
    Server tChatServer(7077);

    return a.exec();
}
