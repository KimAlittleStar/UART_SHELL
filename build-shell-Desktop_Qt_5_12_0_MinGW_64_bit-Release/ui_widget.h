/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_UI;
    QLineEdit *tLine_message;
    QTextEdit *tEdit_shell;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QHBoxLayout *hLayout_Baudlist;
    QLabel *label_Baudlist;
    QComboBox *cBox_Baudlist;
    QWidget *layoutWidget1;
    QHBoxLayout *hLayout_Portlist;
    QLabel *label_Portlist;
    QComboBox *cBox_Portlist;
    QPushButton *pButton_send;
    QFrame *line;
    QWidget *tab_Set;
    QLabel *lable_quickCompelatList;
    QPushButton *pButton_AddquickCompelat;
    QPushButton *pButton_delquickCompelat;
    QCheckBox *checkBox_autoConect;
    QPlainTextEdit *plaintEdit_quickCompleat;
    QCheckBox *checkBox_caseSensitive;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_colorlist;
    QComboBox *cBox_ColorList;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *cBox_autoBaud;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1089, 709);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        Widget->setFont(font);
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 1091, 711));
        QFont font1;
        font1.setPointSize(9);
        tabWidget->setFont(font1);
        tabWidget->setTabletTracking(false);
        tabWidget->setAcceptDrops(false);
        tab_UI = new QWidget();
        tab_UI->setObjectName(QString::fromUtf8("tab_UI"));
        tLine_message = new QLineEdit(tab_UI);
        tLine_message->setObjectName(QString::fromUtf8("tLine_message"));
        tLine_message->setGeometry(QRect(460, 640, 251, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(7);
        tLine_message->setFont(font2);
        tLine_message->setReadOnly(true);
        tEdit_shell = new QTextEdit(tab_UI);
        tEdit_shell->setObjectName(QString::fromUtf8("tEdit_shell"));
        tEdit_shell->setGeometry(QRect(10, 10, 1061, 611));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Consolas"));
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        tEdit_shell->setFont(font3);
        tEdit_shell->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        pushButton_2 = new QPushButton(tab_UI);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(860, 640, 81, 31));
        pushButton = new QPushButton(tab_UI);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(730, 640, 121, 31));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Consolas"));
        font4.setPointSize(10);
        pushButton->setFont(font4);
        layoutWidget = new QWidget(tab_UI);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(230, 640, 221, 28));
        hLayout_Baudlist = new QHBoxLayout(layoutWidget);
        hLayout_Baudlist->setSpacing(6);
        hLayout_Baudlist->setContentsMargins(11, 11, 11, 11);
        hLayout_Baudlist->setObjectName(QString::fromUtf8("hLayout_Baudlist"));
        hLayout_Baudlist->setContentsMargins(0, 0, 0, 0);
        label_Baudlist = new QLabel(layoutWidget);
        label_Baudlist->setObjectName(QString::fromUtf8("label_Baudlist"));
        label_Baudlist->setFont(font);

        hLayout_Baudlist->addWidget(label_Baudlist);

        cBox_Baudlist = new QComboBox(layoutWidget);
        cBox_Baudlist->addItem(QString());
        cBox_Baudlist->addItem(QString());
        cBox_Baudlist->addItem(QString());
        cBox_Baudlist->addItem(QString());
        cBox_Baudlist->addItem(QString());
        cBox_Baudlist->setObjectName(QString::fromUtf8("cBox_Baudlist"));
        QPalette palette;
        QBrush brush(QColor(85, 0, 127, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(122, 122, 122, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        cBox_Baudlist->setPalette(palette);
        cBox_Baudlist->setFont(font4);

        hLayout_Baudlist->addWidget(cBox_Baudlist);

        layoutWidget1 = new QWidget(tab_UI);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 640, 201, 28));
        hLayout_Portlist = new QHBoxLayout(layoutWidget1);
        hLayout_Portlist->setSpacing(6);
        hLayout_Portlist->setContentsMargins(11, 11, 11, 11);
        hLayout_Portlist->setObjectName(QString::fromUtf8("hLayout_Portlist"));
        hLayout_Portlist->setContentsMargins(0, 0, 0, 0);
        label_Portlist = new QLabel(layoutWidget1);
        label_Portlist->setObjectName(QString::fromUtf8("label_Portlist"));
        label_Portlist->setEnabled(true);
        label_Portlist->setFont(font);

        hLayout_Portlist->addWidget(label_Portlist);

        cBox_Portlist = new QComboBox(layoutWidget1);
        cBox_Portlist->setObjectName(QString::fromUtf8("cBox_Portlist"));
        cBox_Portlist->setFont(font4);

        hLayout_Portlist->addWidget(cBox_Portlist);

        pButton_send = new QPushButton(tab_UI);
        pButton_send->setObjectName(QString::fromUtf8("pButton_send"));
        pButton_send->setGeometry(QRect(950, 640, 101, 31));
        pButton_send->setFont(font);
        line = new QFrame(tab_UI);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 620, 1041, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        tabWidget->addTab(tab_UI, QString());
        tab_Set = new QWidget();
        tab_Set->setObjectName(QString::fromUtf8("tab_Set"));
        lable_quickCompelatList = new QLabel(tab_Set);
        lable_quickCompelatList->setObjectName(QString::fromUtf8("lable_quickCompelatList"));
        lable_quickCompelatList->setGeometry(QRect(20, 160, 111, 21));
        pButton_AddquickCompelat = new QPushButton(tab_Set);
        pButton_AddquickCompelat->setObjectName(QString::fromUtf8("pButton_AddquickCompelat"));
        pButton_AddquickCompelat->setGeometry(QRect(20, 520, 71, 28));
        pButton_delquickCompelat = new QPushButton(tab_Set);
        pButton_delquickCompelat->setObjectName(QString::fromUtf8("pButton_delquickCompelat"));
        pButton_delquickCompelat->setGeometry(QRect(120, 520, 81, 28));
        checkBox_autoConect = new QCheckBox(tab_Set);
        checkBox_autoConect->setObjectName(QString::fromUtf8("checkBox_autoConect"));
        checkBox_autoConect->setGeometry(QRect(21, 90, 251, 21));
        checkBox_autoConect->setAcceptDrops(true);
        checkBox_autoConect->setTristate(true);
        plaintEdit_quickCompleat = new QPlainTextEdit(tab_Set);
        plaintEdit_quickCompleat->setObjectName(QString::fromUtf8("plaintEdit_quickCompleat"));
        plaintEdit_quickCompleat->setGeometry(QRect(20, 190, 241, 301));
        plaintEdit_quickCompleat->setCenterOnScroll(false);
        checkBox_caseSensitive = new QCheckBox(tab_Set);
        checkBox_caseSensitive->setObjectName(QString::fromUtf8("checkBox_caseSensitive"));
        checkBox_caseSensitive->setGeometry(QRect(150, 160, 111, 22));
        layoutWidget2 = new QWidget(tab_Set);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(21, 51, 241, 28));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_colorlist = new QLabel(layoutWidget2);
        label_colorlist->setObjectName(QString::fromUtf8("label_colorlist"));

        horizontalLayout->addWidget(label_colorlist);

        cBox_ColorList = new QComboBox(layoutWidget2);
        cBox_ColorList->addItem(QString());
        cBox_ColorList->addItem(QString());
        cBox_ColorList->addItem(QString());
        cBox_ColorList->addItem(QString());
        cBox_ColorList->addItem(QString());
        cBox_ColorList->setObjectName(QString::fromUtf8("cBox_ColorList"));

        horizontalLayout->addWidget(cBox_ColorList);

        layoutWidget3 = new QWidget(tab_Set);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(21, 117, 241, 28));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        cBox_autoBaud = new QComboBox(layoutWidget3);
        cBox_autoBaud->addItem(QString());
        cBox_autoBaud->addItem(QString());
        cBox_autoBaud->addItem(QString());
        cBox_autoBaud->addItem(QString());
        cBox_autoBaud->addItem(QString());
        cBox_autoBaud->setObjectName(QString::fromUtf8("cBox_autoBaud"));

        horizontalLayout_2->addWidget(cBox_autoBaud);

        tabWidget->addTab(tab_Set, QString());
        QWidget::setTabOrder(pButton_send, tEdit_shell);
        QWidget::setTabOrder(tEdit_shell, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);
        QWidget::setTabOrder(pushButton_2, cBox_Portlist);
        QWidget::setTabOrder(cBox_Portlist, cBox_Baudlist);

        retranslateUi(Widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "\344\270\262\345\217\243\345\221\275\344\273\244\350\241\214", nullptr));
        tLine_message->setText(QApplication::translate("Widget", "MessageWindow:", nullptr));
        pushButton_2->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        pushButton->setText(QApplication::translate("Widget", "\346\211\253\346\217\217\344\270\262\345\217\243/F5", nullptr));
#ifndef QT_NO_SHORTCUT
        pushButton->setShortcut(QApplication::translate("Widget", "F5", nullptr));
#endif // QT_NO_SHORTCUT
        label_Baudlist->setText(QApplication::translate("Widget", "\346\263\242\347\211\271\347\216\207:", nullptr));
        cBox_Baudlist->setItemText(0, QApplication::translate("Widget", "4800", nullptr));
        cBox_Baudlist->setItemText(1, QApplication::translate("Widget", "9600", nullptr));
        cBox_Baudlist->setItemText(2, QApplication::translate("Widget", "115200", nullptr));
        cBox_Baudlist->setItemText(3, QApplication::translate("Widget", "128000", nullptr));
        cBox_Baudlist->setItemText(4, QApplication::translate("Widget", "256000", nullptr));

        label_Portlist->setText(QApplication::translate("Widget", "\344\270\262\345\217\243\345\210\227\350\241\250:", nullptr));
        pButton_send->setText(QApplication::translate("Widget", "\345\217\221\351\200\201/Enter", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_UI), QApplication::translate("Widget", "\344\270\262\345\217\243\345\221\275\344\273\244\350\241\214", nullptr));
        lable_quickCompelatList->setText(QApplication::translate("Widget", "\345\277\253\346\215\267\350\241\245\345\205\250\345\210\227\350\241\250", nullptr));
        pButton_AddquickCompelat->setText(QApplication::translate("Widget", "\345\272\224\347\224\250", nullptr));
#ifndef QT_NO_SHORTCUT
        pButton_AddquickCompelat->setShortcut(QApplication::translate("Widget", "Alt+S", nullptr));
#endif // QT_NO_SHORTCUT
        pButton_delquickCompelat->setText(QApplication::translate("Widget", "\345\210\240\351\231\244\345\275\223\345\211\215", nullptr));
        checkBox_autoConect->setText(QApplication::translate("Widget", "\345\215\225\344\270\252\344\270\262\345\217\243\350\207\252\345\212\250\344\273\245\351\273\230\350\256\244\346\263\242\347\211\271\347\216\207\350\277\236\346\216\245", nullptr));
        checkBox_caseSensitive->setText(QApplication::translate("Widget", "\345\244\247\345\260\217\345\206\231\346\225\217\346\204\237", nullptr));
        label_colorlist->setText(QApplication::translate("Widget", "\345\255\227\344\275\223\351\242\234\350\211\262:", nullptr));
        cBox_ColorList->setItemText(0, QApplication::translate("Widget", "RED", nullptr));
        cBox_ColorList->setItemText(1, QApplication::translate("Widget", "WHITE", nullptr));
        cBox_ColorList->setItemText(2, QApplication::translate("Widget", "BLUE", nullptr));
        cBox_ColorList->setItemText(3, QApplication::translate("Widget", "GREEN", nullptr));
        cBox_ColorList->setItemText(4, QApplication::translate("Widget", "YELLOW", nullptr));

        label->setText(QApplication::translate("Widget", "\351\273\230\350\256\244\346\263\242\347\211\271\347\216\207:", nullptr));
        cBox_autoBaud->setItemText(0, QApplication::translate("Widget", "4800", nullptr));
        cBox_autoBaud->setItemText(1, QApplication::translate("Widget", "9600", nullptr));
        cBox_autoBaud->setItemText(2, QApplication::translate("Widget", "115200", nullptr));
        cBox_autoBaud->setItemText(3, QApplication::translate("Widget", "128000", nullptr));
        cBox_autoBaud->setItemText(4, QApplication::translate("Widget", "256000", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab_Set), QApplication::translate("Widget", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
