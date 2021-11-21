#ifndef INITIALSCREEN_H
#define INITIALSCREEN_H

#include <QMainWindow>

namespace Ui {
class InitialScreen;
}

class InitialScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit InitialScreen(QWidget *parent = nullptr);
    ~InitialScreen();

private slots:
    void on_pushButton_8_clicked();

private:
    Ui::InitialScreen *ui;
};

#endif // INITIALSCREEN_H
