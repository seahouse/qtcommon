//#include <QCoreApplication>
#include <QApplication>

#include "mainhandler.h"
#include "connection.h"

#include <QDir>
#include <QDate>

#include <QTextDocumentFragment>
#include <QDebug>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QDir dir(".");
    if (!dir.exists("logs"))
        dir.mkdir("logs");
    QFile file("logs/" + QDate::currentDate().toString("yyyy-MM-dd") + ".txt");
    if (file.open(QIODevice::Append))
    {
        QTextStream out(&file);
        QByteArray localMsg = msg.toLocal8Bit();
        switch (type) {
        case QtDebugMsg:
            out << QString("Debug: %1 (%2:%3, %4)\n")
                   .arg(localMsg.constData())
                   .arg(context.file)
                   .arg(QString::number(context.line))
                   .arg(context.function);
            fprintf(stdout, "%s\n", localMsg.constData());
            fflush(stdout);
            break;
        case QtFatalMsg:
            out << QString("Fatal: %1 (%2:%3, %4)\n")
                   .arg(localMsg.constData())
                   .arg(context.file)
                   .arg(QString::number(context.line))
                   .arg(context.function);
            fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtSystemMsg:
            out << QString("Critical: %1 (%2:%3, %4)\n")
                   .arg(localMsg.constData())
                   .arg(context.file)
                   .arg(QString::number(context.line))
                   .arg(context.function);
            fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        default:
            break;
        }

        file.close();
    }

}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
//    QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

//    QFile file("t1.txt");
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        return -1;


//    QString sContent = file.readAll();
////    QString sContent = "<html><body><h1>12345</h1></body></html>";
//    QTextDocumentFragment textDoc = QTextDocumentFragment::fromHtml(sContent);
//    QString sPlainText = textDoc.toPlainText();
//    qDebug() << sPlainText;

    if (!createConnection())
        return -1;

    MainHandler mh;
    mh.run();

    return a.exec();
}
