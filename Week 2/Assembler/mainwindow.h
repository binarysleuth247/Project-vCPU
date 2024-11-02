#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unordered_map>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_assembleButton_clicked();

private:
    Ui::MainWindow *ui;
    std::unordered_map<std::string, std::string> opcodes;
    std::string assembleInstruction(const std::string &instruction);
    std::string regToBin(const std::string &reg);
    std::string cleanRegister(std::string reg);
};

#endif // MAINWINDOW_H
