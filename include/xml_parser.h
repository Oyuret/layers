#ifndef XML_PARSER_H
#define XML_PARSER_H
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>
#include <QMap>
#include <QString>
#include <QObject>
#include "cfg.h"

class XML_Parser : public QObject
{
    Q_OBJECT
public:
    XML_Parser();
    CFG getCFG(const QString fileName);
    virtual ~XML_Parser(){}
private:
    QMap<QString, QString> parseBlock(QXmlStreamReader& xml);
    void createCFG(QList<QMap<QString, QString> > &blocks, QString start, CFG& cfg);

signals:
    void setStatusMsg(QString msg);
};

#endif // XML_PARSER_H
