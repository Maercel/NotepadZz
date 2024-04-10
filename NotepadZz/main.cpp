#include "mainwindow.h"
#include "searchpopup.h"

#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleFile("../style/Combinear.qss");
    styleFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream styleStream(&styleFile);
    a.setStyleSheet(styleStream.readAll());


    MainWindow w(&a);

    // Icon
    // w.setWindowIcon(QIcon("./img/ApplicationIcon/zz_notepad_logo.png"));
    //  qDebug() << "Current Path:" << QDir::currentPath();
    w.setWindowIcon(QIcon("../application_icon/zz_notepad_logo.png"));

    w.InitializeSearchPopup();
    w.show();
    return a.exec();
}
