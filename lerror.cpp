#include "lerror.h"
#include <QString>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>

typedef struct {
    int id;
    QString text;
} typeErrorTable;

const typeErrorTable ErrorTable[] = {
    Error_QFFmpegDemuxerReopen, "Demuxer ujranyitási kisérlet.",

    Error_FileNotFound,     "A fájl nem létezik.",
    Error_FileAccessError,  "A fájlhoz való hozzáférés megtagadva.",
    Error_FileCreateError,  "A fájl letrehozása nem sikerűlt",
    Error_FileOpenError,    "A fájl megnyitása nem sikerűlt",
    Error_FileReadError,    "Fájl olvasási hiba.",
    Error_FileWriteError,   "A fájl írása nem sikerűlt.",
    Error_FileFormatError,  "Ismeretlen, vagy rossz a fájl formátuma.",

    Error_NotEnoughMemory,   "Nincs elég memória.",
    Error_NoError,          "Nincs hiba."
};

const int ErrorTableNum = sizeof(ErrorTable) / sizeof(typeErrorTable);
const QString UnknowErrorText("Ismeretlen hiba.");

lError::lError(int ErrorCode)
    :QObject()
{
    if (ErrorCode > 0)
        ErrorCode = Error_NoError;

    m_ErrorCode = ErrorCode;
    if (m_ErrorCode < Error_NoError)
        Log << QObject::tr("Hiba") + ": "+ errorText();
}

void lError::setError(int ErrorCode)
{
    if (ErrorCode > 0)
        ErrorCode = Error_NoError;

    m_ErrorCode = ErrorCode;
    Log << tr("Hiba") + ": " + errorText();
}

void lError::copyFrom(lError &Error)
{
    m_ErrorCode = Error.ErrorCode();
}

void lError::clear()
{
    m_ErrorCode = Error_NoError;
}

void lError::show(QWidget *parent)
{
    QString title = tr("Hiba");

    QMessageBox* box = new QMessageBox(parent);
    box->setIcon(QMessageBox::Critical);
    box->setWindowTitle(QApplication::applicationName().append(" - ").append(title));
    box->setText(errorText());
//    box->setInformativeText("informative text");
    box->exec();

    delete box;
}

bool lError::isError()
{
    return m_ErrorCode != Error_NoError;
}

// ToDo: Nyelvkezelés hiányzik.
QString lError::errorText()
{
    QString Str = UnknowErrorText;
    int i;

    for( i = 0; i < ErrorTableNum; i++)
        if (ErrorTable[i].id == m_ErrorCode)
            Str = ErrorTable[i].text;

    return Str;
}
