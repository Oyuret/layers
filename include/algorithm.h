#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <QObject>

class Algorithm : public QObject
{
    Q_OBJECT
public:
    Algorithm();
    virtual void run();
    virtual ~Algorithm() {}

signals:
    void setStatusMsg(QString msg);
};

#endif // ALGORITHM_H
