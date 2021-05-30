#ifndef UIFORM_H
#define UIFORM_H

#include <QMainWindow>
#include <QLocalSocket>
#include <QtDebug>
#include <QVector>
#include <QDataStream>
#include <QByteArray>
#include <QIODevice>
#include <QMessageBox>
#include <QString>
#include <QtEndian>


QT_BEGIN_NAMESPACE
namespace Ui { class uiform; }
QT_END_NAMESPACE

class uiform : public QMainWindow
{
    Q_OBJECT

public:
    uiform(QWidget *parent = nullptr);
    ~uiform();

private slots:
    void on_d_btn_clicked();
    void on_c_Btn_clicked();
    void on_e_btn_clicked();

    void on_com_Btn_clicked();

    void on_function_box_currentIndexChanged(int index);

private:
    void setup_everything();
    QByteArray create_wchar_from_string(QString string, int general_size);
    QByteArray r_packet;
    QLocalSocket* local_socket = new QLocalSocket(this);
    QVector<double> x_Coordinate, y_Coordinate;
    QByteArray prep_packet_to_send();
    Ui::uiform*ui;
};
#endif // UIFORM_H
