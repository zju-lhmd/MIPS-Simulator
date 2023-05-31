
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcodeedit.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#include <vector>
#include <QPushButton>
using namespace std;
class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_2_triggered();

    void on_Code_Button_1_clicked();
    void on_Code_Button_2_clicked();
    void on_Code_Button_3_clicked();

    void on_Display_Button_1_clicked();
    void on_Display_Button_2_clicked();
    void on_Display_Button_3_clicked();

    void on_Number_Button_1_clicked();
    void on_Number_Button_2_clicked();
    void on_Number_Button_3_clicked();

    void on_pushButton_5_clicked();

    void showDisplay();
    void errorMsg(QString msg);




    void on_chooseNumber_currentIndexChanged(int index);

    void on_inputNumber_editingFinished();

    void on_chooseRadix_currentIndexChanged(int index);

    void on_numberCalculateButton_clicked();

private slots:
    void on_debugButton_clicked();

    void on_exitButton_clicked();

    void on_nextStepButton_clicked();

private:
    Ui::MainWindow *ui;
    QCodeEdit *configEditor;
    QPushButton *btn[8000];
};

#endif // MAINWINDOW_H
