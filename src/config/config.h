#ifndef CONFIG_H
#define CONFIG_H

#include <QTcpSocket>
#include <QHostAddress>

QString ipv4_addr = "127.0.0.1";
QHostAddress *hostAddr = new QHostAddress(ipv4_addr);
quint16 hostPort = 27015;
QAbstractSocket::BindMode bind_mode = 0;

#endif // CONFIG_H

