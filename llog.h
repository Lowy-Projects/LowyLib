#ifndef LLOG_H
#define LLOG_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QListWidget>

class lLog : public QObject
{
    Q_OBJECT
public:
    explicit lLog(QObject *parent = 0);

    int      setMainWidget(QWidget *mainWidget);
    int      setDirectMainWidget(QWidget *mainWidget);
    QWidget *MainWidget() {return m_MainWidget;}
    void     setPrefixText(QString prefText);
    void     text(QString logText);
    QString operator <<(QString txt);

signals:

public slots:

private:
    void         destroyLogWindow();

    QString       m_PrefixText;
    QWidget      *m_MainWidget;
    QListWidget  *m_ListView;
};

extern lLog Log;

#endif // LLOG_H
