/** @file scical.cpp

 *  @brief scical.cpp to implement slots
           
 *
 *  scical.cpp file is use to implement and
    define slot/math functions. File contains
    connecters for slots. Referenced to youtube
    video: https://www.youtube.com/watch?v=txGRU7OrTZo
    helped to set up and understans functions/slots
    and signals are used in QT.
  
      
 *
 *  @author Billy Jean Baptiste
 
 *  @bug Not able to delete on_exponentButton_released()
         without reference error. Also, syntax for slots is in
         snake case. Unable to refractor without a reference
         error. Functions are automatically created in this
         file (in snake case) when created in scical.ui.
 */

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


//reference code to https://www.youtube.com/watch?v=txGRU7OrTZo
//This code is to connect match object names (button0 - button 9) with signals
SciCal::SciCal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SciCal)
{
    ui->setupUi(this);
    connect(ui->piButton, SIGNAL(released()), this, SLOT(piNumberButton()));

    ui->Display->setText(QString::number(currentValue));
    QPushButton *numBttons[10];

    //initializing the button number to match button object when pressed
    //Can do this individually but a for loop is more efficient/less code
    for(int i = 0; i < 10; ++i){
        QString buttonName = "button" + QString::number(i);

        numBttons[i] = SciCal::findChild<QPushButton *>(buttonName);
        connect(numBttons[i], SIGNAL(released()), this, SLOT(numPressed()));
    }

        //connectors: connecting the objects's name to slots
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
//This slot function is used to set up the number objects 
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
//reference code to https://www.youtube.com/watch?v=txGRU7OrTZo
//set up the math operations
void SciCal::functionButtons(){
    addOperation = false;
    subtractOperation = false;
    mulitplyOperation = false;
    divideOperation = false;

    QString displayValue = ui->Display->text();
    currentValue = displayValue.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();

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

//reference code to https://www.youtube.com/watch?v=txGRU7OrTZo
//set up the enter button object
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


//Slot to set the value for pi on the calculator
void SciCal::piNumberButton(){
   const double pi = M_PI;
   ui->Display->setText(QString::number(pi));

}

//set up the sign button object
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


//set up the deciaml button object
void SciCal::on_decimalButton_released()
{
    ui->Display->setText(ui->Display->text() + ".");


}

//set up the clear button object
void SciCal::on_clearButton_pressed()
{
    double clearScreen = 0.0;
    ui->Display->setText(QString::number(clearScreen));
}

//set up the sine button object
void SciCal::on_sinButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double sine = qSin(dblDisplayValue);
    ui->Display->setText(QString::number(sine));
}

//set up the cosine button object
void SciCal::on_cosButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double cosine = qCos(dblDisplayValue);
    ui->Display->setText(QString::number(cosine));
}

//set up the tangent button object
void SciCal::on_tanButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double tangent = qTan(dblDisplayValue);
    ui->Display->setText(QString::number(tangent));
}

//set up the inverse button object
void SciCal::on_inverseButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double inverse = (1/dblDisplayValue);
    ui->Display->setText(QString::number(inverse));
}

//set up the ten to the x button object
void SciCal::on_tenExponent_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double tenExponent = pow(10.0, dblDisplayValue);
    ui->Display->setText(QString::number(tenExponent, 'g', 20));
}

//set up the natural log button object
void SciCal::on_lnButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double naturalLog = (qLn(dblDisplayValue));
    ui->Display->setText(QString::number(naturalLog, 'g', 20));
}

//set up the square root button object
void SciCal::on_sqaureRootButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double squareRoot = (qSqrt(dblDisplayValue));
    ui->Display->setText(QString::number(squareRoot, 'g', 20));
}

//set up the squared button object
void SciCal::on_squareButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double square = (pow(dblDisplayValue, 2));
    ui->Display->setText(QString::number(square, 'g', 20));
}

//set up the exponent button object
void SciCal::on_exponentButton_pressed()
{
    double exponentNum = M_E;
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double exponent = (pow(exponentNum, dblDisplayValue));
    ui->Display->setText(QString::number(exponent, 'g', 20));
}

//Unused function. Cannot delete without reference error
//Not able to figure out how to delete without error
void SciCal::on_exponentButton_released()
{

}

//set up the log button object
void SciCal::on_logButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double logX = (log10(dblDisplayValue));
    ui->Display->setText(QString::number(logX, 'g', 20));
}

