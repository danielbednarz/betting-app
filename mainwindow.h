#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <thread>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void ResetAfterBet();

    void on_pushButton_clicked();

    void on_betHomeButton_clicked();

    void on_betDrawButton_clicked();

    void on_betAwayButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
