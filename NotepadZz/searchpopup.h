#ifndef SEARCHPOPUP_H
#define SEARCHPOPUP_H

#include <QWidget>
#include <QLineEdit>
#include <QFile>
#include <QMessageBox>
#include <QShortcut>
#include <QTextEdit>

class SearchPopup : public QWidget
{
    Q_OBJECT

public:
    SearchPopup(QWidget *parent, QTextEdit *textEdit);

    void handleVisibility();

signals:
    void searchRequested(const QString &text);

private:

    void onEnterPressed();
    void onSearchTextChanged(const QString &text);

    inline void clearHighlighting() const noexcept;

    void highlightFoundText(const QString &searchText);

    QLineEdit *textField;
    QTextEdit *uiTextEdit;
};

#endif // SEARCHPOPUP_H
