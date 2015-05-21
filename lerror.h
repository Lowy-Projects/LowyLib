#ifndef LERROR_H
#define LERROR_H

#include <QObject>
#include <QWidget>
#include "llog.h"

enum {
    ErrorCategory_QFFMpeg       = -5000,
    Error_QFFmpegDemuxerReopen  = ErrorCategory_QFFMpeg,
    Error_QFFmpegDemuxerNotFound,
    ErrorCategory_File          = -1100,
    Error_FileNotFound          = ErrorCategory_File,
    Error_FileAccessError,
    Error_FileCreateError,
    Error_FileOpenError,
    Error_FileReadError,
    Error_FileWriteError,
    Error_FileFormatError,
    ErrorCategory_System        = -1000,
    Error_NotEnoughMemory       = ErrorCategory_System,
    Error_NoError               = 0
};

class lError: public QObject
{
    Q_OBJECT

public:
    lError(int ErrorCode = Error_NoError);
    void    setError(int ErrorCode);
    void    copyFrom(lError &Error);
    void    clear();
    void    show(QWidget* parent = 0);
    bool    isError();
    int     ErrorCode() {return m_ErrorCode;}
    QString errorText();

private:
    int     m_ErrorCode;
};

#endif // LERROR_H
