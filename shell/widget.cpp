#include "widget.h"
#include "ui_widget.h"
#include <QSerialPort>
#include <QSerialPortInfo>
 #include <QDebug>
#include<QTextLayout>
#include <QTextEdit>
#include <QScrollBar>
#include <QVector>
#include <QTimer>
#include <QSettings>
#include <string.h>
#define qout qDebug()
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    minTextCurse = 0;
    ui->setupUi(this);
    activePort = nullptr;
    ui->checkBox_caseSensitive->setCheckState(Qt::CheckState::Checked);
    caseSensitive = Qt::CaseSensitive;
    ui->tEdit_shell->installEventFilter(this);
    ui->tEdit_shell->setHtml("<body bgcolor=\"#000000\"></body>");
    ui->tEdit_shell->setTextColor("red");
    ui->tEdit_shell->insertPlainText("UART SHELL V0.1\n");
    ui->tEdit_shell->setFocus();
    ui->checkBox_autoConect->setCheckState(Qt::CheckState::Checked);
//    ui->tEdit_shell->setTextColor("red");
//    history.resize(10);
    quickComplets.append("@CMD.clean");
    loadseting();
    scanport();

    minTextCurse = ui->tEdit_shell->textCursor().position();
    overTimer.stop();
    connect(&overTimer,SIGNAL(timeout()),this,SLOT(on_timerOver()));
//    ui->tEdit_shell->setTextBackgroundColor("black");
}

Widget::~Widget()
{
    saveseting();
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
            if(ui->tEdit_shell->textCursor().position()< minTextCurse)
                return true ;

            QKeyEvent *k = static_cast<QKeyEvent *>(event);
            if(k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter)
            {
                txtcur.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
                txtcur.setPosition(minTextCurse,QTextCursor::KeepAnchor);
                QString msg = txtcur.selectedText();
                if(history.isEmpty() || QString::compare(msg,history.back()) != 0)
                    history.append(msg);
                if(msg.compare("@CMD.clean") == 0)
                {
                    ui->tEdit_shell->setText("");
                    ui->tEdit_shell->setTextColor(ui->cBox_ColorList->currentText());
                    ui->tEdit_shell->setHtml("<body bgcolor=\"#000000\"></body>");

                    ui->tEdit_shell->append("clean");
                    minTextCurse = ui->tEdit_shell->textCursor().position();
//                    ui->tEdit_shell->setFocus();

                }else
                sendText(msg);

                historyNum = history.size();
                ui->tEdit_shell->append("");
                txtcur.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
                ui->tEdit_shell->setTextCursor(txtcur);
                minTextCurse = ui->tEdit_shell->textCursor().position();
                return true;
            }else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Up) {
                QTextCursor tc =  ui->tEdit_shell->textCursor();

                if(history.size() == 0) return true;//如果没有历史记录,则不操作


                    tc.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
                    tc.setPosition(minTextCurse,QTextCursor::KeepAnchor);
                    tc.removeSelectedText();
                if(historyNum == 0)
                    historyNum = history.size();
                if(historyNum > history.size())
                    historyNum = 1;
                ui->tEdit_shell->insertPlainText(history[historyNum-1]); //插入上一个输入的历史记录
                lastTextCurse = ui->tEdit_shell->textCursor().position();
                qout<<history[historyNum-1]<<"history size "<< history.length();
                historyNum--;
                qout<<"使用上一个记录"<<endl;

                return true;
            }else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Down) {
                QTextCursor tc =  ui->tEdit_shell->textCursor();

                if(history.size() == 0) return true;//如果没有历史记录,则不操作
                tc.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
                tc.setPosition(minTextCurse,QTextCursor::KeepAnchor);
                tc.removeSelectedText();
                if(historyNum > history.size())
                    historyNum = 1;
                if(historyNum == 0)
                    historyNum = history.size();
                ui->tEdit_shell->insertPlainText(history[historyNum-1]); //插入上一个输入的历史记录
                lastTextCurse = ui->tEdit_shell->textCursor().position();
                qout<<history[historyNum-1]<<"history size "<< history.length();
                historyNum++;
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
                if(tc.position()<=minTextCurse)
                {
                    qout << "delete over";
                    return true;
                }


            }else if(static_cast<QKeyEvent *>(event)->key() == Qt::Key_Left){
                if(minTextCurse == ui->tEdit_shell->textCursor().position())
                {
                    return  true;
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
            if(activePort->isOpen())
            {
                ui->tLine_message->setText("请先关闭串口再扫描串口");
                return;
            }
            ui->cBox_Portlist->clear();
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
                        if(QString::compare( ui->cBox_Portlist->itemData(i).toString(), serial.portName(),caseSensitive) == 0)
                        {
                            isHaveItemInList++;
                        }
                    }
                    qout<<"find a" << serial.portName() <<endl;
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
            ui->cBox_Baudlist->setCurrentText("");
            if(ui->checkBox_autoConect->checkState() == Qt::CheckState::Checked && ui->cBox_Portlist->count() == 1)
            {
                qout<<"auto conect";
                ui->cBox_Portlist->setCurrentIndex(0);
                openprot(ui->cBox_Portlist->currentText(),ui->cBox_autoBaud ->currentText().toInt());
                qout<<ui->cBox_Baudlist->currentText();
            }

        }else
        {
            /* 串口没有初始化成功，先不处理异常 */
            // 警告对话框
            ui->tLine_message->setText("串口初始化失败");
        }

}

void Widget::on_tEdit_shell_cursorPositionChanged()
{
    //do nothing;
    if(ui->tEdit_shell->textCursor().position()<minTextCurse)
        ui->tEdit_shell->setReadOnly(true);
    else {
        ui->tEdit_shell->setReadOnly(false);
    }
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
    static int flag = 0;
    qint64 recnum =  activePort->readLine((receiverBuff+flag),2048);
    if(recnum > 0)
    {

        qout<<"received:>"<<receiverBuff<<endl;
        flag += recnum;
        if(receiverBuff[flag-1] != '\n')
        {
            overTimer.stop();
            overTimer.start(50);
//            overTimer.setSingleShot(true);
            return;
        }
        else
        {
             overTimer.stop();
             overTimer.start(50);
        }


    }else {
        return;
    }
    QString str = QString::fromLocal8Bit(receiverBuff);

    qout<<"send msg";
    ui->tEdit_shell->insertPlainText(str);
        flag = 0;
        QString nstr = str;
        if(nstr.indexOf("QuickComplet:") == 0)
        {
            str.remove("QuickComplet:");
            if(ui->plaintEdit_quickCompleat->textCursor().position()!= 0)
            {
                ui->plaintEdit_quickCompleat->insertPlainText(",\n");
            }
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
                    if(QString::compare( quickComplets[j],strlist[i],caseSensitive) == 0)
                    {
                        isrepead = true;break;
                    }
                }
                if(isrepead) continue;
                quickComplets.append(strlist[i]);
                ui->plaintEdit_quickCompleat->insertPlainText(strlist[i]);
                if(i != (strlist.size()-1))
                {
                    ui->plaintEdit_quickCompleat->insertPlainText(",\n");
                }
                qout<<"strlist["<<i<<"]:"<<strlist[i]<<endl;
            }
            ui->tEdit_shell->append("检测到快捷关键字.已添加\n");

        }
        minTextCurse = ui->tEdit_shell->textCursor().position();
//        receiveBuff.clear();
//    }else{
//        if(overTimer.isActive()) overTimer.stop();
//        overTimer.start(10);
//        overTimer.setSingleShot(true);
//        qout<<"timestar:"<<receiveBuff<<endl;
//        connect(&overTimer,SIGNAL(timeout()),this,SLOT(on_timerOver()));
//    }
        qDebug()<<"receive info:"<<receiverBuff;
         receiverBuff[0] = '\0';
}

void Widget::openprot(const QString & portname,const int baud)
{
//    if(activePort == nullptr)
//        scanport();
    if(activePort->isOpen()) //如果串口打开着就关闭
    {
//        activePort->clear();
        qout<<"port close";
        activePort->clear();
        activePort->close();

//        delete  activePort;
        ui->cBox_Portlist->setEnabled(true);
        ui->cBox_Baudlist ->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setText("打开串口");
        ui->tLine_message->setText("串口"+ui->cBox_Portlist->currentText()+"已关闭");
    }else{ //关闭着就打开
        activePort->setPortName(portname);

        if(activePort->open(QIODevice::ReadWrite)== true)
        {
            qout<<"port open";
            activePort->setBaudRate(baud,QSerialPort::AllDirections);//设置波特率和读写方向
            activePort->setDataBits(QSerialPort::Data8);      //数据位为8位
            activePort->setFlowControl(QSerialPort::NoFlowControl);//无流控制
            activePort->setParity(QSerialPort::NoParity); //无校验位
            activePort->setStopBits(QSerialPort::OneStop); //一位停止位
            ui->tLine_message->setText(ui->cBox_Portlist->currentText()+"打开成功");
            connect(activePort,SIGNAL(readyRead()),this,SLOT(receiveInfo()));

            ui->pushButton_2->setText("关闭串口");
            ui->tEdit_shell->setFocus();
            ui->cBox_Portlist->setEnabled(false);
            ui->cBox_Baudlist ->setEnabled(false);
            ui->pushButton->setEnabled(false);
        }else {
            ui->tLine_message->setText("打开失败,检查串口是否被占用");
            ui->pushButton_2->setText("打开串口");
        }
    }
}

void Widget::openprot()
{

    Widget::openprot(ui->cBox_Portlist->currentText(),ui->cBox_Baudlist->currentText().toInt());
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

            qout<<"find quitck index :" << i<<"quickComplets[i].indexOf("<<str<<") == "<<quickComplets[i].indexOf(str,0,caseSensitive) <<endl;
            
            if(quickComplets[i].indexOf(str,0,caseSensitive) == 0)
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


void Widget::on_timerOver(void)
{
    qout<<"timerOver"<<endl;
    if(receiverBuff[0] != '\0')
    {
        QTextCursor tc = ui->tEdit_shell->textCursor();
        tc.movePosition(QTextCursor::End);
        ui->tEdit_shell->setTextCursor(tc);
        ui->tEdit_shell->insertPlainText( QString::fromLocal8Bit(receiverBuff));
        minTextCurse = ui->tEdit_shell->textCursor().position();
    }else {

        QByteArray rec = activePort->readAll();

        QString str = QString::fromLocal8Bit(rec);
        QTextCursor tc = ui->tEdit_shell->textCursor();
        tc.movePosition(QTextCursor::End);
        ui->tEdit_shell->setTextCursor(tc);
        ui->tEdit_shell->insertPlainText(str);
        minTextCurse = ui->tEdit_shell->textCursor().position();

    }
//    if(! receiveBuff.isEmpty())
//    {
//        qout<<"resc"<<receiveBuff<<endl;
//        QTextCursor tc = ui->tEdit_shell->textCursor();
//        tc.movePosition(QTextCursor::End);
//        ui->tEdit_shell->setTextCursor(tc);
//        ui->tEdit_shell->insertPlainText(receiveBuff);
//        receiveBuff.clear();
//        minTextCurse = ui->tEdit_shell->textCursor().position();
//    }
    overTimer.stop();
}

void Widget::on_cBox_ColorList_currentTextChanged(const QString &arg1)
{
    qout<<"change str"<<arg1<<endl;

    ui->tEdit_shell->setTextColor(arg1);
    QTextCursor tc = ui->tEdit_shell->textCursor();
    tc.movePosition(QTextCursor::End);
//    ui->tEdit_shell->setTextCursor(tc);
    ui->tEdit_shell->insertPlainText("text color change :"+arg1+"\n");
    minTextCurse = ui->tEdit_shell->textCursor().position();
}

void Widget::on_pButton_AddquickCompelat_clicked()
{
    QString plaintext = ui->plaintEdit_quickCompleat->toPlainText();
    plaintext.remove('\n');
    plaintext.remove(' ');
    qout<<"plaintext"<<plaintext;
    QStringList sliplist = plaintext.split(',');

    //插入到快捷补全的数组中去.
    for(int i = 0;i<sliplist.size();i++)
    {
        bool is_exist = false;
        if(sliplist[i].size() == 0) continue;
        for(int j = 0;j<quickComplets.size();j++)
        {
            if(QString::compare(sliplist[i],quickComplets[j],caseSensitive) == 0)
            {
                qout<<"检测到"<<sliplist[i]<<"重复"<<endl;
                is_exist = true;
                break;
            }
        }
        if(is_exist == true)
            continue;
        else {
            quickComplets.append(sliplist[i]);
        }
    }
}


void Widget::on_serialErrorOccured()
{
    qout<<"error serial "<<endl;

    if(activePort->isOpen())
        openprot();
}

void Widget::on_Widget_destroyed()
{
    qout<<"关闭"<<endl;
}

void Widget::saveseting(void)
{
    QSettings setting("KimalittleStar","UART_CommendLine");
    setting.setValue("isAutosive",1);
    setting.setValue("iscaseSensitive",caseSensitive);
    setting.setValue("textcolor",ui->cBox_ColorList->currentText());
    setting.setValue("defaultBaud",ui->cBox_autoBaud ->currentText());
    setting.setValue("autoConnect",ui->checkBox_autoConect->checkState());
    setting.sync();
}

void Widget::loadseting(void)
{
    QSettings setting("KimalittleStar","UART_CommendLine");
    if(setting.value("isAutosive").toInt() == 0)
        return ;
    if(setting.value("iscaseSensitive").toInt() == 1)
    {
        caseSensitive = Qt::CaseSensitive;
        ui->checkBox_caseSensitive->setCheckState(Qt::CheckState::Checked);
    }else
    {
        caseSensitive = Qt::CaseInsensitive;
        ui->checkBox_caseSensitive->setCheckState(Qt::CheckState::Unchecked);
    }
    if(setting.value("autoConnect").toInt() == 0)
    {
        ui->checkBox_autoConect->setCheckState(Qt::CheckState::Unchecked);
    }else
    {
        ui->checkBox_autoConect->setCheckState(Qt::CheckState::Checked);
    }
    ui->tEdit_shell->setTextColor(setting.value("textcolor").toString());
    ui->cBox_ColorList->setCurrentText(setting.value("textcolor").toString());
    ui->tEdit_shell->setTextColor(ui->cBox_ColorList->currentText());
    ui->cBox_autoBaud ->setCurrentText(setting.value("defaultBaud").toString());
    ui->cBox_Baudlist->setCurrentText(setting.value("defaultBaud").toString());
    setting.setValue("isAutosive",1);
    setting.sync();



}


void Widget::on_tabWidget_currentChanged(int index)
{
    qout<<"index"<<index;
    if(index == 1)
    {
        //reflash quick complet list
        QString listStr = "";
        for(int i = 0;i<quickComplets.size();i++)
        {
            listStr.append(quickComplets[i]+",\n");
        }
        listStr.remove( listStr.lastIndexOf(','),1);
        ui->plaintEdit_quickCompleat->clear();
        ui->plaintEdit_quickCompleat->setPlainText(listStr);
        //reflash over
    }
}

void Widget::on_pButton_delquickCompelat_clicked()
{
    QString selecttext =  ui->plaintEdit_quickCompleat->textCursor().selectedText() ;
    selecttext.remove(' ');
    selecttext.remove(',');
    selecttext.remove('\n');
    quickComplets.remove( quickComplets.indexOf(selecttext),1);
    ui->plaintEdit_quickCompleat->textCursor().removeSelectedText();
}

void Widget::on_checkBox_caseSensitive_stateChanged(int arg1)
{
    if(arg1== 0)
        caseSensitive = Qt::CaseInsensitive;
    else {
        caseSensitive = Qt::CaseSensitive;
    }
}
