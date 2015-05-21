/*********************************************************************
 *  lowyLog osztály V:1.0.0
 *  By: Lowy 2015.Március.20
 *  License: GNU 3.0
 *  Üzenetmegjelenítő osztály QT környetethez.
 *  Ez az osztály szerves részét képezi, a LowyLib segédkönyvtárnak.
 *********************************************************************/

#include "llog.h"
#include "lerror.h"
#include <QTime>
#include <QDebug>
#include <QtWidgets/QGridLayout>


lLog::lLog(QObject *parent) :
    QObject(parent)
{
    m_MainWidget = 0;
    m_ListView   = 0;
}

/**
 * @brief lLog::setMainWidget
 * Log ablak létrehozása.
 * Paraméterként kap egy üres ablakot, melyben felépíti a megjelenítő elemet (QListView)
 * Ha már létezik egy Log ablak, megszünteti vele a kapcsolatot.
 * Ha a paraméterként kapott szülőablak értéke 0, a kiírás a szabványos kimenetre kerűl.
 * @param mainWidget [in]   Szülő keretablak, amiben a megjelenítés létrejön. Ha értéke 0, a szabványos kimenetere fog írni.
 * @return lError hibakód Error_xxx
 */
int lLog::setMainWidget(QWidget *mainWidget)
{
    QGridLayout* layout = 0;

    if (m_MainWidget)
        destroyLogWindow();

    m_MainWidget = mainWidget;
    if (mainWidget == 0)
        return Error_NoError;

    m_ListView = new QListWidget(mainWidget);
    if (m_ListView == 0)
        return Error_NotEnoughMemory;
    m_ListView->setObjectName("lLog::ListWidget");

    layout = new QGridLayout(mainWidget);
    if (layout == 0)
    {
        delete m_ListView;
        m_ListView = 0;
        return Error_NotEnoughMemory;
    }

    layout->setMargin(2);
    layout->addWidget(m_ListView);


    return Error_NoError;
}

/**
 * @brief lLog::setDirectMainWidget
 * Egy másik lLog példánnyal létrehozott ablak használata.
 * Ha a megadott ablak nem lLog ablak, a kijelzés a szabványos kimeneten folytatódik.
 * @param mainWidget [in] QWidget tipusú mutató, az lLog ablakra.
 * @return lError hibakód. Error_xxx
 */
int lLog::setDirectMainWidget(QWidget *mainWidget)
{
    m_ListView = mainWidget->findChild<QListWidget *>("lLog::ListWidget");
    m_MainWidget = mainWidget;

    return Error_NoError;
}

/**
 * @brief lLog::setPrefixText
 * Prefix szöveg megadása.
 * Ez a szöveg az időbélyegző után minden alkalommal megjelenik.
 * @param prefText [in]  Prefix szöveget tartalmaző QString példány.
 */
void lLog::setPrefixText(QString prefText)
{
    m_PrefixText = prefText;
}

/**
 * @brief lLog::text
 * Szöveg megjelenítése a Log ablakban.
 * Ha nincs megadva log ablak, a szabványos kimenetre ír.
 * @param logText [in]  Megjelenítendő üzenet.
 */
void lLog::text(QString logText)
{
    QString timeText = QTime::currentTime().toString().append(": ");

    if (m_PrefixText.length())
        timeText.append(m_PrefixText).append(" >> ");

    if (m_ListView != 0)
    {
        m_ListView->addItem(timeText.append(logText));
    }
    else
        qDebug() << timeText.append(logText);
}

QString lLog::operator << (QString txt)
{
    text(txt);

    return txt;
}

/**
 * @brief lLog::destroyLogWindow
 * Belső tabfügvény !!!
 * Megszünteti a mainWidget-el a kapcsolatot, és törli a benne létrehozott elemeket.
 * A létrehozáskór kívűrlől kapot mainWidget-et nem tőrli meg.
 */
void lLog::destroyLogWindow()
{
    QGridLayout* layout;

    if (m_MainWidget != 0) return;

    layout = (QGridLayout*)m_MainWidget->layout();
    m_MainWidget->setLayout(0);

    if (m_ListView != 0)
    {
        delete m_ListView;
        m_ListView = 0;
    }

    if (layout != 0)
        delete layout;

    m_MainWidget = 0;
}

// Példányosítás
lLog Log;
