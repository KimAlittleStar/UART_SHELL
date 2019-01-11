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
                if(history.isEmpty() || QString::compare(msg,history.back()) != 0)
                    history.append(msg);
                sendText(msg);

                historyNum = history.size();
                ui->tEdit_shell->append("");
                txtcur.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
                ui->tEdit_shell->setTextCursor(txtcur);
                return true;
            }else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Up) {
                QTextCursor tc =  ui->tEdit_shell->textCursor();

                if(history.size() == 0) return true;//如果没有历史记录,则不操作

                if(historyNum != history.size())//如果当前不是第一次按上键,则要删除上一次补全的历史记录
                {
                    if(historyNum == 0)
                        tc.movePosition(QTextCursor::Left,QTextCursor::KeepAnchor,history[0].length());
                    else {
                        tc.movePosition(QTextCursor::Left,QTextCursor::KeepAnchor,history[historyNum].length());
                    }
                    tc.removeSelectedText();
                }
                if(historyNum == 0)
                    historyNum = history.size();

                ui->tEdit_shell->insertPlainText(history[historyNum-1]); //插入上一个输入的历史记录
                qout<<history[historyNum-1]<<"history size "<< history.length();
                historyNum--;
                qout<<"使用上一个记录"<<endl;

                return true;
            }else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Down) {
                qout<<"使用下一个记录"<<endl;

                return true;
            }else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Tab) {

                qout<<"tab"<<endl;
                //得到最后一行的字符
                QTextCursor txtcur = ui->tEdit_shell->textCursor();
                txtcur.movePosition(QTextCursor::StartOfLine,QTextCursor::KeepAnchor);
                QString msg = txtcur.selectedText();
                int index = msg.lastIndexOf(' ');
                if(index == -1) index = 0;else index++;
                QString ins = msg.mid(index);
                const QString insertStr = findQuickCompletString( ins);
                if(insertStr != "")
                {
                    txtcur = ui->tEdit_shell->textCursor();
                    txtcur.movePosition(QTextCursor::Left,QTextCursor::KeepAnchor,ins.length());
                    txtcur.removeSelectedText();
                    ui->tEdit_shell->insertPlainText(findQuickCompletString( msg.mid( msg.lastIndexOf(' ')+1)));
                }
                qout<<"ins :" <<ins <<endl;


                return true;
            }else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Backspace) {
                QTextCursor tc = ui->tEdit_shell->textCursor();
                qout<<"back";
                int oldposition = tc.position();
                tc.movePosition(QTextCursor::StartOfLine);
                if((tc.blockNumber()+1) == maxline && oldposition == tc.position())
                {
                    qout << "delete over";
                    return true;
                }


            }
        }
    }
    return QWidget::eventFilter(target,event);
}

void Widget::sendText(QString & text)
{
//    int indx;
    for(int i = 0;i<text.length();i++)
    {
        if(text.at(i) == '\\' && (i+1)<text.length())
        {
            if(text.at(i+1) == '\\')
            {
                text.remove(i+1,1);
            }else if(text.at(i+1) == 't') {
                text.replace(i,1,'\t');
                text.remove(i+1,1);
            }else if (text.at(i+1) == 'n') {
                text.replace(i,1,'\n');
                text.remove(i+1,1);
            }
        }
    }
    text.append("\r\n");qout<<text<<endl;
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
    QTextCursor txtcur = ui->tEdit_shell->textCursor();
    txtcur.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
    txtcur.movePosition(QTextCursor::StartOfLine,QTextCursor::MoveAnchor);
    txtcur.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
    QString msg = txtcur.selectedText();
    if(history.isEmpty() || QString::compare(msg,history.back()) != 0)
        history.append(msg);
    sendText(msg);

    historyNum = history.size();
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

    if(info.lastIndexOf("\n") == (info.length()-1) || info.lastIndexOf("\r\n")== (info.length()-2))
    {
//        receiveBuff.remove(receiveBuff.length()-2,2);
//        ui->tEdit_shell->insertPlainText("@"+ui->cBox_Portlist->currentText()+":> "+receiveBuff+"\n");
        ui->tEdit_shell->insertPlainText(receiveBuff);
        QString nstr = receiveBuff;
        if(nstr.indexOf("QuickComplet:") == 0)
        {
            str.remove("QuickComplet:");
            QStringList strlist = nstr.split("\",\"");
            for(int i = 0;i<strlist.size();i++)
            {
                bool isrepead = false;
                if(i== 0) strlist[i].remove(0,strlist[i].indexOf("\"")+1);
                if(i == (strlist.size()-1))
                    strlist[i].remove(strlist[i].lastIndexOf("\""),
                                      strlist[i].length()-strlist[i].lastIndexOf("\""));
                for(int j = 0;j<quickComplets.size();j++)
                {
                    if(QString::compare( quickComplets[j],strlist[i]) == 0)
                    {
                        isrepead = true;break;
                    }
                }
                if(isrepead) continue;
                quickComplets.append(strlist[i]);
                qout<<"strlist["<<i<<"]:"<<strlist[i]<<endl;
            }
        }
        receiveBuff.clear();
    }
        qDebug()<<"receive info:"<<info;
}

void Widget::openprot()
{
    if(activePort->isOpen()) //如果串口打开着就关闭
    {
//        activePort->clear();
        activePort->close();
        ui->pushButton_2->setText("打开串口");
        ui->tLine_message->setText("串口"+ui->cBox_Portlist->currentText()+"已关闭");
    }else{ //关闭着就打开
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

const QString & Widget::findQuickCompletString(const QString & str)
{
    int retindex = -1;
    for(int i = 0;i<quickComplets.size();i++)
    {

            qout<<"find quitck index :" << i<<"quickComplets[i].indexOf("<<str<<") == "<<quickComplets[i].indexOf(str) <<endl;

            if(quickComplets[i].indexOf(str) == 0)
            {
                if(retindex == -1)
                    retindex = i;
                else {
                    retindex = -1;
                    break;
                 }
            }

    }
    if(retindex == -1)
        return  emptyStr;
    else
        return quickComplets[retindex];
}
