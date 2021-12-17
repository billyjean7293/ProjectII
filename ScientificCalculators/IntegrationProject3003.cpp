#include "scical.h"
#include "ui_scical.h"
#include <QtMath>
#include <math.h>
#include <QtCore/qmath.h>

//Global variables
double currentValue = 0;
bool addOperation = false;
bool subtractOperation = false;
bool mulitplyOperation = false;
bool divideOperation = false;
bool sineOperation = false;
bool cosineOperation = false;
bool tangentOperation = false;
bool lnOperation = false;
bool squareRootOperation = false;
bool inverseOperation = false;
bool tenExponentOperation = false;
bool squareOperation = false;
bool rootOperation = false;


//reference code to https://www.youtube.com/watch?v=txGRU7OrTZo
SciCal::SciCal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SciCal)
{
    ui->setupUi(this);
    connect(ui->piButton, SIGNAL(released()), this, SLOT(piNumberButton()));

    ui->Display->setText(QString::number(currentValue));
    QPushButton *numBttons[10];

    //initializing the button number to match button object when pressed
    for(int i = 0; i < 10; ++i){
        QString buttonName = "button" + QString::number(i);

        numBttons[i] = SciCal::findChild<QPushButton *>(buttonName);
        connect(numBttons[i], SIGNAL(released()), this, SLOT(numPressed()));



    }

    connect(ui->additionButton, SIGNAL(released()), this, SLOT(functionButtons()));
    connect(ui->subtractButton, SIGNAL(released()), this, SLOT(functionButtons()));
    connect(ui->multiplyButton, SIGNAL(released()), this, SLOT(functionButtons()));
    connect(ui->divideButton, SIGNAL(released()), this, SLOT(functionButtons()));
    connect(ui->enterButton, SIGNAL(released()), this, SLOT(enterButtonPressed()));
    connect(ui->negativeButton, SIGNAL(released()), this, SLOT(signChange()));






}


SciCal::~SciCal()
{
    delete ui;
}

//reference code to https://www.youtube.com/watch?v=txGRU7OrTZo
void SciCal::numPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
    QString displayValue = ui->Display->text();
    if ((displayValue.toDouble() == 0) || (displayValue.toDouble() == 0.0)){
        ui->Display->setText(buttonValue);

    }else{
        QString newValue = displayValue + buttonValue;
        double dblNewValue = newValue.toDouble();
        ui->Display->setText(QString::number(dblNewValue, 'g', 20));
    }


}

void SciCal::functionButtons(){
    addOperation = false;
    subtractOperation = false;
    mulitplyOperation = false;
    divideOperation = false;
    sineOperation = false;
    cosineOperation = false;
    tangentOperation = false;
    lnOperation = false;
    squareRootOperation = false;
    inverseOperation = false;
    tenExponentOperation = false;
    squareOperation = false;
    rootOperation = false;

    QString displayValue = ui->Display->text();
    currentValue = displayValue.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();

    //reference code to https://www.youtube.com/watch?v=txGRU7OrTZo

    if(QString::compare(buttonValue, "+") == 0 ){
        addOperation = true;
    }else if(QString::compare(buttonValue, "-") == 0){
        subtractOperation = true;
    }else if(QString::compare(buttonValue, "x") == 0){
        mulitplyOperation = true;
    }else if(QString::compare(buttonValue, "÷") == 0){
        divideOperation = true;
    }
    ui->Display->setText("");

}


//Set the value for pi in the calculator
void SciCal::piNumberButton(){
   const double pi = M_PI;
   ui->Display->setText(QString::number(pi));

}

void SciCal::enterButtonPressed(){
    double answer;
    answer = 0.0;
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    if (addOperation || subtractOperation || mulitplyOperation || divideOperation){
        if(addOperation){
            answer = currentValue + dblDisplayValue;
        }else if(subtractOperation){
            answer = currentValue - dblDisplayValue;
        }else if(mulitplyOperation){
            answer = currentValue * dblDisplayValue;
        }else{
            answer = currentValue / dblDisplayValue;
        }
    }
    ui->Display->setText(QString::number(answer));
}

void SciCal::signChange(){

    QPushButton * button = (QPushButton* ) sender();
    double signNum;
    QString newSignNum;

    if (button->text() == "(-)"){
        signNum = ui->Display->text().toDouble();
        signNum *= -1;
        newSignNum = QString::number(signNum, 'g', 15);
        ui->Display->setText(newSignNum);
    }
}



void SciCal::on_decimalButton_released()
{
    ui->Display->setText(ui->Display->text() + ".");


}


void SciCal::on_clearButton_pressed()
{
    double clearScreen = 0.0;
    ui->Display->setText(QString::number(clearScreen));
}


void SciCal::on_sinButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double sine = qSin(dblDisplayValue);
    ui->Display->setText(QString::number(sine));
}


void SciCal::on_cosButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double cosine = qCos(dblDisplayValue);
    ui->Display->setText(QString::number(cosine));
}


void SciCal::on_tanButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double tangent = qTan(dblDisplayValue);
    ui->Display->setText(QString::number(tangent));
}


void SciCal::on_inverseButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double inverse = (1/dblDisplayValue);
    ui->Display->setText(QString::number(inverse));
}


void SciCal::on_tenExponent_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double tenExponent = pow(10.0, dblDisplayValue);
    ui->Display->setText(QString::number(tenExponent, 'g', 20));
}


void SciCal::on_lnButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double naturalLog = (qLn(dblDisplayValue));
    ui->Display->setText(QString::number(naturalLog, 'g', 20));
}


void SciCal::on_sqaureRootButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double squareRoot = (qSqrt(dblDisplayValue));
    ui->Display->setText(QString::number(squareRoot, 'g', 20));
}


void SciCal::on_squareButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double square = (pow(dblDisplayValue, 2));
    ui->Display->setText(QString::number(square, 'g', 20));
}


void SciCal::on_exponentButton_pressed()
{
    double exponentNum = M_E;
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double exponent = (pow(exponentNum, dblDisplayValue));
    ui->Display->setText(QString::number(exponent, 'g', 20));
}


void SciCal::on_exponentButton_released()
{

}


void SciCal::on_logButton_pressed()
{

    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double logX = (log10(dblDisplayValue));
    ui->Display->setText(QString::number(logX, 'g', 20));
}

