/** @file scical.cpp
 *  @brief scical.cpp file to implement slots.
           Slots are functions in QT.
           
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
SciCal::SciCal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SciCal)
{
    ui->setupUi(this);



    ui->Display->setText(QString::number(currentValue));
    QPushButton *numBttons[10];

    //initializing the button number to match button object when pressed
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
    connect(ui->piButton, SIGNAL(released()), this, SLOT(piNumberButton()));

}


SciCal::~SciCal()
{
    delete ui;
}

/** @brief Function for when the
 *  numPressed object is clicked


 *  reference code to https://www.youtube.com/watch?v=txGRU7OrTZo
    This slot function is used to set up the numbers on the
    calculator. When user clicks a number, the corresponding number
    is displayed.


 *  @return void, the cooresponding math operation is performed
 *

 */
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
/** @brief Function for when the
 *  functionButton object is clicked


 *  reference code to https://www.youtube.com/watch?v=txGRU7OrTZo
    This slot function is used to set up the math
    function objects, when the user clicks any of the
    basic math operations '+, -, x or ÷'


 *  @return void, the cooresponding math operation is performed
 *

 */
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

/** @brief Pi number


 *  when the user clicks the symbol 'π', pi,
 *  the value 3.14159 is displayed


 *  @return void, returns number for pi
 *

 */
//Set the value for pi in the calculator
void SciCal::piNumberButton(){
   const double pi = M_PI;
   ui->Display->setText(QString::number(pi));

}

/** @brief function for enterButton object


 *  representation for an equals button. When a user
 *  wants to get the results of a math operation of two numbers,
 *  the enterButton object is pressed


 *  @return void, return the return of a math operation or function
 *

 */
void SciCal::enterButtonPressed(){
    calculate cal;
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    if (addOperation || subtractOperation || mulitplyOperation || divideOperation){
        if(addOperation){
            ui->Display->setText(QString::number(cal.add(currentValue, dblDisplayValue)));
        }else if(subtractOperation){
            ui->Display->setText(QString::number(cal.subtract(currentValue, dblDisplayValue)));
        }else if(mulitplyOperation){
            ui->Display->setText(QString::number(cal.multiply(currentValue, dblDisplayValue)));
        }else{
            ui->Display->setText(QString::number(cal.divide(currentValue, dblDisplayValue)));
        }
    }
}

/** @brief changeSign function


 *  when a user wants to change the sign value of a number,
 *  the signChange object is pressed.


 *  @return void, returns the negative number of the current number
 *

 */
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


/** @brief decimal function


 *  adds a demical place


 *  @return void, returns a deicaml
 *

 */
void SciCal::on_decimalButton_released()
{
    ui->Display->setText(ui->Display->text() + ".");


}

/** @brief function for clearButton object


 *  when user wants to clear the display.


 *  @return void, return a 0 when pressed
 *

 */


void SciCal::on_clearButton_pressed()
{
    double clearScreen = 0.0;
    ui->Display->setText(QString::number(clearScreen));
}


/** @brief function for sinButton object


 *  a trigonometry function for sine.


 *  @return void, returns the sine of a value, the value in radians
 *  by default
 *

 */
void SciCal::on_sinButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double sine = qSin(dblDisplayValue);
    ui->Display->setText(QString::number(sine));
}


/** @brief function for cosinButton object


 *  a trigonometry function for cosine.


 *  @return void, returns the cosine of a value, the value in radians
 *  by default
 *

 */
void SciCal::on_cosButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double cosine = qCos(dblDisplayValue);
    ui->Display->setText(QString::number(cosine));
}


/** @brief function for tanButton object


 *  a trigonometry function for tangent.


 *  @return void, returns the tangent of a value, the value in radians
 *  by default
 *

 */
void SciCal::on_tanButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double tangent = qTan(dblDisplayValue);
    ui->Display->setText(QString::number(tangent));
}


/** @brief function for inverse object


 *  a function for the inverse of a value


 *  @return void, returns the inverse value
 *

 */
void SciCal::on_inverseButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double inverse = (1/dblDisplayValue);
    ui->Display->setText(QString::number(inverse));
}


/** @brief function for tenExponent object


 *  a function for the number of zero a user
 *  wants, base ten


 *  @return void, returns value ten to the number of the current value
 *

 */
void SciCal::on_tenExponent_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double tenExponent = pow(10.0, dblDisplayValue);
    ui->Display->setText(QString::number(tenExponent, 'g', 20));
}

/** @brief function for lnButton object


 *  a function for natural log function


 *  @return void, returns the natural log of current value
 *

 */
void SciCal::on_lnButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double naturalLog = (qLn(dblDisplayValue));
    ui->Display->setText(QString::number(naturalLog, 'g', 20));
}


/** @brief function for squareRoot object


 *  takes the square root of the current value


 *  @return void, returns square root of the current value
 *

 */
void SciCal::on_sqaureRootButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double squareRoot = (qSqrt(dblDisplayValue));
    ui->Display->setText(QString::number(squareRoot, 'g', 20));
}


/** @brief function for squareButton object


 *  sqaure the current value


 *  @return void, return the current number squared
 *

 */
void SciCal::on_squareButton_pressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double square = (pow(dblDisplayValue, 2));
    ui->Display->setText(QString::number(square, 'g', 20));
}


/** @brief function for sinButton object


 *  a trigonometry function for sine.


 *  @return void, returns the sine of a value, the value in radians
 *  by default
 *

 */
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

/** @brief function for logButton object


 *  a trigonometry function for sine.


 *  @return void, returns the sine of a value, the value in radians
 *  by default
 *

 */
void SciCal::on_logButton_pressed()
{

    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double logX = (log10(dblDisplayValue));
    ui->Display->setText(QString::number(logX, 'g', 20));
}
