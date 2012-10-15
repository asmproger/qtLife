#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initLife();
    void drawCurrent();
    void nextStep();
    char processCell(int i, int j);
    void changeSteps();
    
private:
    Ui::MainWindow *ui;
public:
    int n, m;
    char **current;
    char **next;
    QTimer timer;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
