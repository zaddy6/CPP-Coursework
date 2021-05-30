#include "uiform.h"
#include "ui_uiform.h"
uiform::uiform(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::uiform){
    ui->setupUi(this);
    setup_everything();
}

uiform::~uiform()
{
    delete ui;
}


void uiform::on_c_Btn_clicked()
{

    local_socket->connectToServer("\\\\.\\pipe\\ICS0025");
    if(local_socket->state() == QLocalSocket::ConnectedState){
        ui->d_btn->setEnabled(true);
        ui->c_Btn->setEnabled(false);
        ui->log_txt_browser->append("Connected successfully");
    }else{
        ui->log_txt_browser->append(local_socket->errorString());
    }
}

void uiform::on_d_btn_clicked()
{
    int general_size = 0;
    if(ui->order_edit->isEnabled()) general_size-=4;
    QByteArray stop_message = create_wchar_from_string("Stop", general_size);
    local_socket->write(stop_message);
    local_socket->disconnectFromServer();
    if(local_socket->state() == QLocalSocket::UnconnectedState){
        ui->c_Btn->setEnabled(true);
        ui->d_btn->setEnabled(false);
        ui->log_txt_browser->append("Disconnected from the pipe");
    }
}

void uiform::on_function_box_currentIndexChanged(int index)
{
    if(index == 2){
        ui->order_edit->setEnabled(true);
    }else{
        ui->order_edit->setEnabled(false);
        ui->order_edit->setText("");
    }
}

void uiform::on_e_btn_clicked()
{
    local_socket->disconnectFromServer();
    close();
}

void uiform::on_com_Btn_clicked()
{
    if(local_socket->state() != QLocalSocket::ConnectedState){
        ui->log_txt_browser->append("Error: Check your connection to the pipe!");
        return;
    }

    QByteArray packet_to_send = prep_packet_to_send();
    if(packet_to_send.isEmpty()){
        ui->log_txt_browser->append("Error in inputs");
        return;}
    local_socket->write(packet_to_send);

    if(local_socket->waitForReadyRead(1000)){
    r_packet = local_socket->readAll();
    }else{
        ui->log_txt_browser->append(local_socket->errorString());
    }

    QDataStream received(&r_packet, QIODevice::ReadOnly);
    int received_size = 0;
    received >> received_size;
    QByteArray wchar_text;
    wchar_text.resize(12);
    received.readRawData(wchar_text.data(), 12);
    if(!wchar_text.startsWith(0x43)){
        QMessageBox::critical(this, "Critical", "The server returned an error");
        if(local_socket->state() == QLocalSocket::ConnectedState) ui->log_txt_browser->append("Error received from the server.");
        return;
    }
    x_Coordinate.clear();
    y_Coordinate.clear();
    while(!received.atEnd()){
        received.setByteOrder(QDataStream::LittleEndian);
        double x, y;
        received >> x;
        received >> y;
        x_Coordinate.push_back(x);
        y_Coordinate.push_back(y);
    }
    double minimum_y = y_Coordinate.at(0);
    double maximum_y = y_Coordinate.at(0);
    std::for_each(y_Coordinate.begin(), y_Coordinate.end(),[&minimum_y](double coordinate){if(minimum_y > coordinate ) minimum_y = coordinate;});
    std::for_each(y_Coordinate.begin(), y_Coordinate.end(),[&maximum_y](double coordinate){if(maximum_y < coordinate ) maximum_y = coordinate;});
    ui->customPlot->clearGraphs();
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x_Coordinate, y_Coordinate);
    ui->customPlot->xAxis->setRange(ui->xs_edit->text().toInt(),ui->xn_edit->text().toInt());
    ui->customPlot->yAxis->setRange(minimum_y, maximum_y);
    ui->customPlot->replot();
    ui->log_txt_browser->append("Graph plot successfully");

}

void uiform::setup_everything()
{
    ui->d_btn->setEnabled(false);
    ui->c_Btn->setEnabled(true);
    ui->order_edit->setEnabled(false);
    ui->xs_edit->setText("0");
    ui->xn_edit->setText("20");
    ui->points_edit->setText("200");
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
}

QByteArray uiform::create_wchar_from_string(QString string, int general_size)
{
    QByteArray to_return;
    QDataStream dataStream(&to_return,QIODevice::WriteOnly);
    dataStream.setByteOrder(QDataStream::BigEndian);
    int len = string.length();
    char null = '\0';
    wchar_t* word = new wchar_t[len];
    string.toWCharArray(word);
    if(ui->order_edit->isEnabled()) general_size+=4;
    int packet_len = general_size + 2 * (len + 1) + sizeof(int);
    dataStream << qToBigEndian(packet_len);
    dataStream.writeRawData(reinterpret_cast<char*>(word), (len*2));
    dataStream.writeRawData(&null, 1);
    dataStream.writeRawData(&null, 1);
    delete[] word;
    return to_return;
}

QByteArray uiform::prep_packet_to_send()
{
    QString function_to_draw = ui->function_box->currentText();
    int general_size = 20;
    QByteArray byte_array = create_wchar_from_string(function_to_draw, general_size);
    bool is_cast_OK;
    QDataStream dataStream(&byte_array, QIODevice::WriteOnly | QIODevice::Append);
    double startingRange = ui->xs_edit->text().toDouble(&is_cast_OK);
    if(!is_cast_OK){
        QMessageBox::critical(this, "Critical", "Please, add double or integers");
        byte_array.clear();
        return byte_array;
    }
    double endingRange = ui->xn_edit->text().toDouble(&is_cast_OK);
    if(!is_cast_OK){
        QMessageBox::critical(this, "Critical", "Please, add double or integers");
        byte_array.clear();
        return byte_array;
    }
    if(startingRange > endingRange){
        QMessageBox::critical(this, "Critical", "X0 is bigger than Xn");
        byte_array.clear();
        return byte_array;
    }
    int points = ui->points_edit->text().toInt(&is_cast_OK);
    if(!is_cast_OK){
        QMessageBox::critical(this, "Critical", "Please, add double or integers");
        byte_array.clear();
        return byte_array;
    }
    dataStream << qToBigEndian(startingRange);
    dataStream << qToBigEndian(endingRange);
    dataStream << qToBigEndian(points);
    if(ui->order_edit->isEnabled()){
        int order = ui->order_edit->text().toInt(&is_cast_OK);
        if(!is_cast_OK){
            QMessageBox::critical(this, "Critical", "Please, add double or integers");
            byte_array.clear();
            return byte_array;
        }
        dataStream << qToBigEndian(order);
    }
    return byte_array;
}
