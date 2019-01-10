#include "widget.h"
#include "ui_widget.h"
#include <QSerialPort>
#include <QSerialPortInfo>
 #include <QDebug>
#include<QTextLayout>
#include <QTextEdit>
#include <QScrollBar>
#include <QVector>
#define qout qDebug()
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    activePort = nullptr;
    ui->tEdit_shell->installEventFilter(this);
    ui->tEdit_shell->setHtml("<body bgcolor=\"#000000\"></body>");
    ui->tEdit_shell->setTextColor("red");
    ui->tEdit_shell->setFocus();
//    ui->tEdit_shell->setTextColor("red");
//    history.resize(10);
    scanport();
//    ui->tEdit_shell->setTextBackgroundColor("black");
}

Widget::~Widget()
{
    if(activePort->isOpen())
    {
        activePort->clear();
        activePort->close();
    }
    delete ui;
}

bool  Widget:: eventFilter(QObject* target,QEvent * event)
{

    if(target == ui->tEdit_shell)
    {
        QTextCursor txtcur = ui->tEdit_shell->textCursor();
        if(event->type()==QEvent::KeyPress)
        {

            QKeyEvent *k = static_cast<QKeyEvent *>(event);
                        if(k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter)
                        {
                            txtcur.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
                            txtcur.movePosition(QTextCursor::StartOfLine,QTextCursor::MoveAnchor);
                            txtcur.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
                            QString msg = txtcur.selectedText();
                            history.append(msg);
                            sendText(msg);

                            historyNum = history.size();
                            ui->tEdit_shell->append("");
                            return true;
                        }

        }else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Up) {
            QTextCursor tc =  ui->tEdit_shell->textCursor();
            tc.movePosition(QTextCursor::Down);
            ui->tEdit_shell->setTextCursor(tc);
            static int count = 0;
            if(count == 1)
            {
                count = 0;
                return true;
            }else count++;
            if(history.size() == 0) return true;


            if(historyNum != history.size())
            {
                if(historyNum == 0)
                    tc.movePosition(QTextCursor::Left,QTextCursor::KeepAnchor,history[0].length());
                else {
                    tc.movePosition(QTextCursor::Left,QTextCursor::KeepAnchor,history[historyNum].length());
                }
                tc.removeSelectedText();
//                tc.movePosition(QTextCursor::StartOfLine,QTextCursor::MoveAnchor);
//                tc.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
            }
            if(historyNum == 0)
                historyNum = history.size();

            ui->tEdit_shell->insertPlainText(history[historyNum-1]);
            qout<<history[historyNum-1]<<"history size "<< history.length();
            historyNum--;
//            QString msg = tc.selectedText();
//            msg.remove("123");

            qout<<"使用上一个记录"<<endl;

            return true;
        }else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Down) {
            qout<<"使用下一个记录"<<endl;

            return true;
        }else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Tab) {
            qout<<"tab"<<endl;
            ui->tEdit_shell->append("123");
            return true;
        }else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Backspace) {
            QTextCursor tc = ui->tEdit_shell->textCursor();
            int oldposition = tc.position();
            tc.movePosition(QTextCursor::EndOfLine);
            if((tc.blockNumber()+2) == maxline && oldposition == tc.position())
            {
                ui->tEdit_shell->append("");
            }

            return true;
        }
    }
    return QWidget::eventFilter(target,event);
}

void Widget::sendText(QString & text)
{
    text.append("\r\n");
    qout<<"send has be called,will send string:"<<text<<endl;
    activePort->write(text.toLocal8Bit());

//    activePort->w
}


void Widget:: scanport(void)
{
    /* 新建串口类 */
    if(activePort == nullptr)
     {   activePort = new QSerialPort();}
        if(activePort != nullptr)
        {
            /* 查找可用串口 */
            foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
            {
                QSerialPort serial;
                serial.setPort(info);
                /* 判断端口是否能打开 */
                if(serial.open(QIODevice::ReadWrite))
                {
                    int isHaveItemInList = 0;
                    /* 判断是不是已经在列表中了 */
                    for(int i=0; i<ui->cBox_Portlist->count(); i++)
                    {
                        /* 如果，已经在列表中了，那么不添加这一项了就 */
                        if(QString::compare( ui->cBox_Portlist->itemData(i).toString(), serial.portName()))
                        {
                            isHaveItemInList++;
                        }
                    }

                    if(isHaveItemInList == 0)
                    {

                        ui->cBox_Portlist->addItem(serial.portName());
                    }
                    serial.close();
                }
            }
            QString msg = "串口更新成功.共";
            msg.append (QString::number( ui->cBox_Portlist->count()));
           qDebug()
                 <<ui->cBox_Portlist->count();
            msg.append(" 个");

            ui->tLine_message->setText(msg);
            ui->cBox_Baudlist->setCurrentText("115200");
        }else
        {
            /* 串口没有初始化成功，先不处理异常 */
            // 警告对话框
            ui->tLine_message->setText("串口初始化失败");
        }

}

void Widget::on_tEdit_shell_cursorPositionChanged()
{
//    qDebug()<<"coming"<<endl;           //可以看到行号随着光标的改变而改变

    QTextCursor tc = ui->tEdit_shell ->textCursor();
 //   ui->tEdit_shell->setCursor();

    if(ui->tEdit_shell->document()->lineCount()>maxline)
    {
        maxline = ui->tEdit_shell->document()->lineCount();
        qDebug()<<"行数:"<<tc.blockNumber()<<"@@"<<ui->tEdit_shell->document()->lineCount()<<endl;
    }
    if((tc.blockNumber()+1)==maxline)
    {
        ui->tEdit_shell->setReadOnly(false);
    }else {
        ui->tEdit_shell->setReadOnly(true);
    }
//    QTextLayout *pLayout = tc.blockNumber();
//    //当前光标在本BLOCK内的相对位置
//    int nCurpos = tc.position() - tc.block().position();
//    int nTextline = pLayout->lineForTextPosition(nCurpos).lineNumber() + tc.block().firstLineNumber();
//    qDebug()<<nTextline<<endl;           //可以看到行号随着光标的改变而改变

}

void Widget::on_pButton_send_clicked()
{
    QTextCursor t = ui->tEdit_shell->textCursor();
    t.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
    t.movePosition(QTextCursor::StartOfLine,QTextCursor::MoveAnchor);
    t.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
    QString msg = t.selectedText();
    sendText(msg);
    ui->tEdit_shell->append("");
    ui->tEdit_shell->setFocus();
}

void Widget::on_pushButton_2_clicked()
{
    openprot();
}

void Widget::receiveInfo()
{
    QByteArray info = activePort->readAll();
    if(info.length() == 0) return;
    QString str = QString::fromLocal8Bit(info);
    receiveBuff.append(str);
//    if(info.lastIndexOf("\n") == (info.length()-1) || info.lastIndexOf("\r\n")== (info.length()-2))
//    {
//        receiveBuff.remove(receiveBuff.length()-2,2);
//        ui->tEdit_shell->insertPlainText("@"+ui->cBox_Portlist->currentText()+":> "+receiveBuff+"\n");
        ui->tEdit_shell->insertPlainText(receiveBuff);
        receiveBuff.clear();
//    }
        qDebug()<<"receive info:"<<info;
}

void Widget::openprot()
{
    if(activePort->isOpen())
    {
//        activePort->clear();
        activePort->close();
        ui->pushButton_2->setText("打开串口");
        ui->tLine_message->setText("串口"+ui->cBox_Portlist->currentText()+"已关闭");
    }else{
        activePort->setPortName(ui->cBox_Portlist->currentText());
        if(activePort->open(QIODevice::ReadWrite)== true)
        {
            int a = ui->cBox_Baudlist->currentText().toInt();
            activePort->setBaudRate(a,QSerialPort::AllDirections);//设置波特率和读写方向
            activePort->setDataBits(QSerialPort::Data8);      //数据位为8位
            activePort->setFlowControl(QSerialPort::NoFlowControl);//无流控制
            activePort->setParity(QSerialPort::NoParity); //无校验位
            activePort->setStopBits(QSerialPort::OneStop); //一位停止位
            ui->tLine_message->setText(ui->cBox_Portlist->currentText()+"打开成功");
            connect(activePort,SIGNAL(readyRead()),this,SLOT(receiveInfo()));
            ui->pushButton_2->setText("关闭串口");
            ui->tEdit_shell->setFocus();
        }else {
            ui->tLine_message->setText("打开失败,检查串口是否被占用");
            ui->pushButton_2->setText("打开串口");
        }
    }
}

void Widget::on_pushButton_clicked()
{
    scanport();
}

void Widget::on_tEdit_shell_textChanged()
{
    QScrollBar *qbar =  ui->tEdit_shell->verticalScrollBar();
    qbar->setValue(qbar->maximum());
}
