/********************************************************************************
** Form generated from reading UI file 'abilitypanel.ui'
**
** Created: Tue 14. Jun 13:26:55 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABILITYPANEL_H
#define UI_ABILITYPANEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_abilityPanel
{
public:

    void setupUi(QWidget *abilityPanel)
    {
        if (abilityPanel->objectName().isEmpty())
            abilityPanel->setObjectName(QString::fromUtf8("abilityPanel"));
        abilityPanel->resize(295, 240);

        retranslateUi(abilityPanel);

        QMetaObject::connectSlotsByName(abilityPanel);
    } // setupUi

    void retranslateUi(QWidget *abilityPanel)
    {
        abilityPanel->setWindowTitle(QApplication::translate("abilityPanel", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class abilityPanel: public Ui_abilityPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABILITYPANEL_H
