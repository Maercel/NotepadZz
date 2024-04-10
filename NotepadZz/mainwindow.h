#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "searchpopup.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QShortcut>
#include <QKeySequence>
#include <QLineEdit>
#include <QStandardPaths>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QApplication *app, QWidget *parent = nullptr);
    ~MainWindow();

    void InitializeSearchPopup();

private slots:

    void closeMainWindow();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionRedo_2_triggered();

    void on_actionAbout_Notepad_triggered();

    void on_actionUndo_triggered();

    void on_actionAbout_2_triggered();

    void on_actiontheme_triggered();

private:
    Ui::MainWindow *ui;
    QString file_path;
    bool lightTheme = false;
    QApplication *app;
    QAction* saveAsAction;

    SearchPopup *searchPopup;

};
#endif // MAINWINDOW_H
