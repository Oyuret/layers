#include "include/xml_parser.h"


XML_Parser::XML_Parser()
{

}

CFG XML_Parser::getCFG(const QString fileName)
{

    QFile* file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        //Something went really wrong
        emit setStatusMsg("Error reading xml");
        CFG cfg;
        return cfg;
    }

    QXmlStreamReader xml(file);
    QList< QMap<QString,QString> > blocks;
    QString start;

    while(!xml.atEnd() &&
          !xml.hasError()) {

        QXmlStreamReader::TokenType token = xml.readNext();

        if(token == QXmlStreamReader::StartDocument) {
            continue;
        }

        if(token == QXmlStreamReader::StartElement) {

            if(xml.name() == "blocks") {
                QXmlStreamAttributes attributes = xml.attributes();
                start = attributes.value("start").toString();
                continue;
            }

            if(xml.name() == "block") {
                blocks.append(this->parseBlock(xml));
            }
        }
    }
    /* Error handling. */
    if(xml.hasError()) {

    }

    // clear everything
    xml.clear();


    CFG cfg;
    createCFG(blocks, start, cfg);
    return cfg;
}

QMap<QString, QString> XML_Parser::parseBlock(QXmlStreamReader& xml) {
    QMap<QString, QString> block;

    if(xml.tokenType() != QXmlStreamReader::StartElement &&
            xml.name() == "block") {
        return block;
    }

    QXmlStreamAttributes attributes = xml.attributes();

    if(attributes.hasAttribute("id")) {
        block["id"] = attributes.value("id").toString();
    }
    if(attributes.hasAttribute("predecessors")) {
        block["predecessors"] = attributes.value("predecessors").toString();
    }
    if(attributes.hasAttribute("successors")) {
        block["successors"] = attributes.value("successors").toString();
    }

    // Read next element
    xml.readNext();

    // Lets ignore nodes for now
    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "block")) {

        // keep reading
        xml.readNext();
    }
    return block;
}

void XML_Parser::createCFG(QList<QMap<QString, QString>> &blocks, QString start, CFG &cfg)
{
    while(!blocks.isEmpty()) {
        QMap<QString,QString> blockMap = blocks.takeFirst();
        QString id = blockMap["id"];
        QString predecessors = blockMap["predecessors"];
        QString successors = blockMap["successors"];

        Block block;
        block.setName(id);

        for(QString predecessor: predecessors.split(" ")) {
            block.addPredecessor(predecessor);
        }

        for(QString successor: successors.split(" ")) {
            block.addSuccessor(successor);
        }

        if(block.getName().compare(start) == 0) {
            cfg.addStartBlock(block);
        } else {
            cfg.addBlock(block);
        }


    }
}
