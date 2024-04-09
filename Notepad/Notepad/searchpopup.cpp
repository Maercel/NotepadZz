#include "searchpopup.h"

SearchPopup::SearchPopup(QWidget *parent, QTextEdit *textEdit) : QWidget(parent), uiTextEdit(textEdit) {
    setWindowTitle("Search");
    resize(300, 200);

    if (parent) {
        int x = parent->geometry().x() + parent->width() - this->width();
        int y = parent->geometry().y();
        move(x, y + 20); // This moves the popup to the top right corner of its parent, + 20 is putting it on good position
    }

    textField = new QLineEdit(this);
    textField->setPlaceholderText("Search"); // Set placeholder text to "Search"
    textField->setGeometry(10, 10, 280, 30);

    QShortcut* enterShortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(enterShortcut, &QShortcut::activated, this, &SearchPopup::onEnterPressed);

    // Connecting trigger for text changed
    // connect(textField, &QLineEdit::textChanged, this, &SearchPopup::onSearchTextChanged); all, widget etc.
    connect(textField, &QLineEdit::textEdited, this, &SearchPopup::onSearchTextChanged); // user input
}

void SearchPopup::handleVisibility()
{
    if (this->isVisible()) {
        clearHighlighting();
        this->hide();
    } else {
        // Reseting text
        if(!this->textField->text().isEmpty()) {
            this->textField->setText("");
        }
        this->show();
        this->textField->setFocus();
    }
}

void SearchPopup::onSearchTextChanged(const QString &text) {
    highlightFoundText(text);
}

inline void SearchPopup::clearHighlighting() const noexcept {
    if (!uiTextEdit || uiTextEdit->toPlainText().isEmpty())
        return;

    QTextCursor cursor(uiTextEdit->document());
    cursor.select(QTextCursor::Document);

    QTextCharFormat defaultFormat;

    cursor.setCharFormat(defaultFormat);
}

// Was used before
void SearchPopup::onEnterPressed() {
    QString searchText = textField->text();
    qDebug() << uiTextEdit->toPlainText();
    highlightFoundText(searchText);
}

void SearchPopup::highlightFoundText(const QString &searchingText) {
    clearHighlighting();
    if (!uiTextEdit || uiTextEdit->toPlainText().isEmpty())
        return;

    // Searching in here
    QTextCursor cursor(uiTextEdit->document());
    cursor.select(QTextCursor::Document);
    QTextCharFormat plainFormat(cursor.charFormat());
    cursor.setCharFormat(plainFormat);

    // Highlighting
    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(QColor("#b78620"));
    highlightFormat.setForeground(QColor("#000000"));

    // Search & highlight
    cursor = QTextCursor(uiTextEdit->document());
    while (!cursor.isNull() && !cursor.atEnd()) {
        // Moving cursor to the next char
        cursor = uiTextEdit->document()->find(searchingText, cursor);

        // Found it, updating
        if (!cursor.isNull()) {
            cursor.mergeCharFormat(highlightFormat);
        }
    }
}
