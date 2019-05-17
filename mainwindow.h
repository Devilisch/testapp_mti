#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double coefficientA = 1, coefficientB = 1, coefficientC = 1, intervalFrom = 0, intervalTo = 1, step = 0.01;
    bool startButtonClicked = false, pauseButtonClicked = false;
    int functionNumber = 1;
    std::vector<double> resultInfo, stepInfo;
    double function(int functionNumber, double coefficientA, double coefficientB, double coefficientC, double x);
    void saveFile();
    void loadFile();
    void blockInput(bool flag);

private slots:
    void on_coefficientA_editingFinished();

    void on_coefficientB_editingFinished();

    void on_coefficientC_editingFinished();

    void on_coefficientFrom_editingFinished();

    void on_coefficientTo_editingFinished();

    void on_coefficientStep_editingFinished();

    void on_funcBox_currentIndexChanged(int index);

    void on_startButton_clicked();

    void on_pauseButton_clicked();

    void on_breakButton_clicked();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

class MyThread : public QThread {
public:
    void run();
};

#endif // MAINWINDOW_H
