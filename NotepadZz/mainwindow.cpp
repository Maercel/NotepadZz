#include "mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QApplication *app, QWidget *parent)
    : QMainWindow(parent), app(app)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit); //Removes spaces
    this->setWindowTitle("Notepadzz");

    // Fixed size
    this->setFixedSize(this->width(), this->height());

    //Not working
    /*
    createAndConnectAction("Save as", QKeySequence::SaveAs, &MainWindow::on_actionSave_as_triggered); //QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
    createAndConnectAction("Save", QKeySequence::Save, &MainWindow::on_actionSave_triggered);
    createAndConnectAction("New", QKeySequence(Qt::CTRL + Qt::Key_N), &MainWindow::on_actionNew_triggered);
    createAndConnectAction("Open", QKeySequence(Qt::CTRL + Qt::Key_O), &MainWindow::on_actionOpen_triggered);
    createAndConnectAction("Cut", QKeySequence::Cut, &MainWindow::on_actionCut_triggered);
    createAndConnectAction("Undo", QKeySequence::Undo, &MainWindow::on_actionUndo_triggered);
    createAndConnectAction("Redo", QKeySequence::Redo, &MainWindow::on_actionRedo_2_triggered);
    createAndConnectAction("Close", QKeySequence(Qt::CTRL + Qt::Key_Q), &MainWindow::closeMainWindow);
    */
}


void MainWindow::InitializeSearchPopup() {
    searchPopup = new SearchPopup(this, ui->textEdit); // Adding current textEdit
    searchPopup->hide(); // Ensure it starts hidden


    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+F"), this);
    connect(shortcut, &QShortcut::activated, searchPopup, &SearchPopup::handleVisibility);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeMainWindow() {
    close();
}

void MainWindow::on_actionNew_triggered()
{
    file_path = "";
    ui->textEdit->setText("New File");
    ui->textEdit->selectAll();
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                    QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), //QDir::currentDir(); threw me to release directory
                                                    tr("Text files (*.txt)")); //3 Default location, 4 filters

    QFile file(file_name);
    file_path = file_name;


    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        //QMessageBox::warning(this, "..", "File not open");
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSave_triggered()
{

    QFile file(file_path);


    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        //QMessageBox::warning(this, "..", "File not open");
        return;
    }

    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    // Marking with tr for translation and any changes, use tr
    QString file_name = QFileDialog::getSaveFileName(this, tr("Save file"),
                                                    QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), //QDir::currentDir(); threw me to release directory
                                                    tr("Text files (*.txt)")); //3 Default location, 4 filters

    QFile file(file_name);
    file_path = file_name;


    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        //QMessageBox::warning(this, "..", "File not open");
        return;
    }


    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();

}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionRedo_2_triggered()
{

}


void MainWindow::on_actionAbout_Notepad_triggered()
{
    ui->textEdit->redo();

}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();

}


void MainWindow::on_actionAbout_2_triggered()
{
    QString about_text;
    about_text = "Made by Marcel \n";
    about_text += "(C) Notepadzz (R)";
    QMessageBox::about(this, "About Notepad", about_text);
}

void MainWindow::on_actiontheme_triggered()
{
    if (lightTheme)
    {
        QFile styleSheetFile("../style/Combinear.qss");
        styleSheetFile.open(QFile::ReadOnly);

        QString styleSheet = QLatin1String(styleSheetFile.readAll());

        app->setStyleSheet(styleSheet);
        lightTheme = false;
    } else
    {
        QFile styleSheetFile("../style/Integrid.qss");
        styleSheetFile.open(QFile::ReadOnly);

        QString styleSheet = QLatin1String(styleSheetFile.readAll());

        app->setStyleSheet(styleSheet);
        lightTheme = true;
    }
}



