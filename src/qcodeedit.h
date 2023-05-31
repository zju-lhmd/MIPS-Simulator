#ifndef QCODEEDIT_H
#define QCODEEDIT_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QObject>

#include <QPaintEvent>
#include <QResizeEvent>
#include <QSize>
#include <QWidget>
#include <QSyntaxHighlighter>
class LineNumberArea;
typedef enum{
    BROWSE,
    EDIT,
}editorMode;

namespace Ui {
class QCodeEdit;
}

class QCodeEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit QCodeEdit(QWidget *parent = nullptr);
    void setMode(editorMode mode);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    ~QCodeEdit() = default;
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
private:
    Ui::QCodeEdit *ui;
    QWidget *lineNumberArea;
};

class LineNumberArea : public QWidget
{
    Q_OBJECT
public:
    LineNumberArea(QCodeEdit *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    QCodeEdit *codeEditor;
};

#endif // QCODEEDIT_H
