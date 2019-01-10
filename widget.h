#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>
#include <QVector>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    void scanport(void);
    QString reciver(void);
    void sendText(QString& text);
    void openprot(void);
    ~Widget();

private slots:
    void on_tEdit_shell_cursorPositionChanged();

    void on_pButton_send_clicked();

    void on_pushButton_2_clicked();

    void receiveInfo();

    void on_pushButton_clicked();

    void on_tEdit_shell_textChanged();

private:

    bool  eventFilter(QObject* target,QEvent * event);
    QVector<QString> history;
    int historyNum;
    int maxline;
    Ui::Widget *ui;
    bool isopen;
    QSerialPort* activePort;
    QString receiveBuff;
    int baud;
};

#endif // WIDGET_H
