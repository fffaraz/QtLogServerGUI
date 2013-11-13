#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udp = new QUdpSocket(this);
    connect(udp, SIGNAL(readyRead()), this, SLOT(udp_readyRead()));
    udp->bind(QHostAddress::Any, 514, QUdpSocket::ReuseAddressHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::udp_readyRead()
{
    while (udp->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udp->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udp->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString data;
        data = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz") + " : " + datagram;
        ui->listLogs->addItem(data);
        ui->listLogs->scrollToBottom();
    }
}

void MainWindow::on_btnClear_clicked()
{
    ui->listLogs->clear();
}
