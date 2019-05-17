#include "mainwindow.h"
#include "ui_mainwindow.h"

double MainWindow::function(int functionNumber, double coefficientA, double coefficientB, double coefficientC, double x) {
    if(functionNumber == 0) return coefficientA * x * x + coefficientB * x + coefficientC;
    else if(functionNumber == 1) return coefficientA * sin( x ) + coefficientB * cos( coefficientC * x );
    else if(functionNumber == 2) return coefficientA * log( coefficientB * x );
    else if(functionNumber == 3) return coefficientA / ( sin( x * x ) * coefficientB);
    else { printf("ERROR: Unknown function number."); return -1; }
}

void MainWindow::saveFile(){
    std::ofstream savefile("data.txt");
    savefile << functionNumber << " " << coefficientA << " " << coefficientB << " " << coefficientC << " " << intervalFrom << " " << intervalTo << " " << step << " \n";
    for ( unsigned int i = 0; i < stepInfo.size(); i++)
        savefile << stepInfo[i] << " " << resultInfo[i] << " \n";
    savefile.close();
}

void MainWindow::loadFile(){
    std::ifstream savefile("data.txt");
    std::string data, sp = " ", subdata;
    size_t iter = 0;
    int i = 0;
    double dataArray[7];

    savefile >> data;
    while((iter = data.find(sp)) != std::string::npos) {
        subdata = data.substr(0, iter);
        dataArray[i] = atof(subdata.c_str());
        data.erase(0, iter + sp.length());
        i++;
    }
    functionNumber = int(ceil(dataArray[0])); //checkout
    coefficientA = dataArray[1];
    coefficientB = dataArray[2];
    coefficientC = dataArray[3];
    intervalFrom = dataArray[4];
    intervalTo = dataArray[5];
    step = dataArray[6];

    i = 0;
    while(!savefile.eof()) {
        savefile >> data;
        i = 0;
        while((iter = data.find(sp)) != std::string::npos) {
            subdata = data.substr(0, iter);
            dataArray[i] = atof(subdata.c_str());
            data.erase(0, iter + sp.length());
            i++;
        }
        stepInfo.push_back(dataArray[0]);
        resultInfo.push_back(dataArray[1]);
    }
    savefile.close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->coefficientA->setText(QString("%1").arg(coefficientA, 0, 'f', 4));
    ui->coefficientB->setText(QString("%1").arg(coefficientB, 0, 'f', 4));
    ui->coefficientC->setText(QString("%1").arg(coefficientC, 0, 'f', 4));
    ui->coefficientFrom->setText(QString("%1").arg(intervalFrom, 0, 'f', 4));
    ui->coefficientTo->setText(QString("%1").arg(intervalTo, 0, 'f', 4));
    ui->coefficientStep->setText(QString("%1").arg(step, 0, 'f', 4));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_coefficientA_editingFinished()
{
    QString str = ui->coefficientA->text();
    coefficientA = str.toDouble();
}

void MainWindow::on_coefficientB_editingFinished()
{
    QString str = ui->coefficientB->text();
    coefficientB = str.toDouble();
}

void MainWindow::on_coefficientC_editingFinished()
{
    QString str = ui->coefficientC->text();
    coefficientC = str.toDouble();
}

void MainWindow::on_coefficientFrom_editingFinished()
{
    QString str = ui->coefficientFrom->text();
    intervalFrom = str.toDouble();
}

void MainWindow::on_coefficientTo_editingFinished()
{
    QString str = ui->coefficientTo->text();
    intervalTo = str.toDouble();
}

void MainWindow::on_coefficientStep_editingFinished()
{
    QString str = ui->coefficientStep->text();
    step = str.toDouble();
}

void MainWindow::on_funcBox_currentIndexChanged(int index)
{
    functionNumber = index;
    printf("index %i\n", index);
}

void MainWindow::on_startButton_clicked()
{
    double x = intervalFrom, y = 0, progress = 0;
    QString progressStatus = "Progress 0%";
    blockInput(startButtonClicked);
    if(!startButtonClicked) {
        startButtonClicked = true;
        while( x <= intervalTo /*&& calculateStatus == CALCULATING*/) {
            y = function(functionNumber, coefficientA, coefficientB, coefficientC, x);
            stepInfo.push_back(x);
            resultInfo.push_back(y);
            x += step;
            progress = (x - intervalFrom) / (intervalTo - intervalFrom) * 100;
            progressStatus = QString("Progress: %1%").arg(progress, 0, 'f', 1);
            ui->startButton->setText(progressStatus);
            printf("f(%f) = %f\n", x, y);
        }
        saveFile();
    } else {
        startButtonClicked = false;
        ui->startButton->setText("Start");
    }
}

void MainWindow::on_pauseButton_clicked()
{
    if(!pauseButtonClicked) {
        pauseButtonClicked = true;
        ui->pauseButton->setText("Continue");
    } else {
        pauseButtonClicked = false;
        ui->pauseButton->setText("Pause");
    }
}

void MainWindow::on_breakButton_clicked()
{
    //команды для Break
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    //команды для нажатия на график -> вызов меню сохранения / загрузки данных
}

void MyThread::run(){
    //второй поток -> стоит вести работу GUI в нём? Разобраться с ошибкой, которая выскакивает при этом.
}

void MainWindow::blockInput(bool flag){
    ui->funcBox->setEnabled(flag);
    ui->coefficientA->setEnabled(flag);
    ui->coefficientB->setEnabled(flag);
    ui->coefficientC->setEnabled(flag);
    ui->coefficientFrom->setEnabled(flag);
    ui->coefficientTo->setEnabled(flag);
    ui->coefficientStep->setEnabled(flag);
}
