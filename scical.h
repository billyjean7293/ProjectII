/** @file scicall.h

 *  @brief Header file
           

 *

 *  Header file created that contains all of the slots. 
    Slots are functions that can be connected to signals
    There are 18 slots but I was only able to use 17 with
    error
    

 *

 *  @author Billy Jean Baptiste

 *  @bug Not able to delete 'void on_exponentButton_released()'
         slot without getting a reference to it error.

 */

#ifndef SCICAL_H
#define SCICAL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SciCal; }
QT_END_NAMESPACE


//LO1. LO1a. SciCal class I created that inherits from QMainWindow, from QT frameWork
class SciCal : public QMainWindow
{
    Q_OBJECT

public:
   explicit SciCal(QWidget *parent = 0);
    ~SciCal();

private:
    Ui::SciCal *ui;


//syntax for slots is in
         snake case. Unable to refractor without a reference
         error. Functions are automatically created in this
         file (in snake case) when created in scical.ui.
//These slots are created for the all of the buttons on calculator UI
private slots:
    void piNumberButton();
    void numPressed();
    void functionButtons();
    void enterButtonPressed();
    void signChange();
    void on_decimalButton_released();
    void on_clearButton_pressed();
    void on_sinButton_pressed();
    void on_cosButton_pressed();
    void on_tanButton_pressed();
    void on_inverseButton_pressed();
    void on_tenExponent_pressed();
    void on_lnButton_pressed();
    void on_sqaureRootButton_pressed();
    void on_exponentButton_pressed();
    void on_squareButton_pressed();
    void on_exponentButton_released();
    void on_logButton_pressed();
};

class calculate : public SciCal{
public:
    double A, B;
public:

    double add(double A, double B) {
           return A + B;
       }
    double subtract(double A, double B) {
           return A - B;
       }
    double multiply(double A, double B) {
           return A * B;
       }
    double divide(double A, double B) {
        return A / B;
    }
};

#endif // SCICAL_H
