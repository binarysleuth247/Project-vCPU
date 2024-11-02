#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <sstream>
#include <bitset>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Assembler");

    opcodes = {
        {"ADD", "0001"}, {"SUB", "0010"}, {"LOAD", "0011"},
        {"STORE", "0100"}, {"MUL", "0105"}, {"DIV", "0110"},
        {"AND", "0111"}, {"OR", "1000"}, {"XOR", "1009"},
        {"NOT", "1010"}, {"JMP", "1011"}, {"JZ", "1100"},
        {"JNZ", "1101"}, {"CALL", "1110"}, {"RET", "1111"},
        {"CMP", "0000"}
    };

    QVBoxLayout *layout = new QVBoxLayout(this);

    QString description =
        "Welcome to the Assembler Program!\n\n"
        "This tool allows you to convert assembly code into machine code.\n\n"
        "How to use the program:\n"
        "1. Enter your assembly code in the 'Input' section.\n"
        "2. Click the 'Assemble' button to convert the assembly code to machine code.\n"
        "3. The resulting machine code will be displayed in the 'Output' section.\n\n"
        "Sample Input:\n"
        "ADD R1, R2, R3\n"
        "SUB R4, R5, R6\n"
        "LOAD R1, [R2]\n"
        "STORE R3, [R4]\n\n"
        "Sample Output:\n"
        "0001000100100011\n"
        "0010010001010110\n"
        "0011000100100000\n"
        "0100001101000000\n";

    QLabel *descriptionLabel = new QLabel(description, this);
    descriptionLabel->setWordWrap(true); // Make the text wrap within the window

    layout->addWidget(descriptionLabel); // Add the label to the layout
    layout->addWidget(ui->inputEdit);
    layout->addWidget(ui->assembleButton);
    layout->addWidget(ui->outputEdit);

    QWidget *window = new QWidget();
    window->setLayout(layout);
    setCentralWidget(window);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_assembleButton_clicked() {
    QString input = ui->inputEdit->toPlainText();
    QStringList lines = input.split("\n");

    QStringList output;
    for (const QString &line : lines) {
        std::string machineCode = assembleInstruction(line.toStdString());
        output.append(QString::fromStdString(machineCode));
    }

    ui->outputEdit->setText(output.join("\n"));
}

std::string MainWindow::assembleInstruction(const std::string &instruction) {
    std::stringstream ss(instruction);
    std::string opcode, dest, src1, src2;
    ss >> opcode >> dest >> src1;

    dest = cleanRegister(dest);
    src1 = cleanRegister(src1);
    if (ss >> src2) {
        src2 = cleanRegister(src2);
    } else {
        src2 = "R0"; // Default register if src2 is not provided
    }

    return opcodes[opcode] + regToBin(dest) + regToBin(src1) + regToBin(src2);
}

std::string MainWindow::regToBin(const std::string &reg) {
    try {
        if (reg.empty() || reg.length() < 2 || reg[0] != 'R') {
            throw std::invalid_argument("Invalid register format: " + reg);
        }
        int num = std::stoi(reg.substr(1));
        return std::bitset<4>(num).to_string();
    } catch (const std::invalid_argument &e) {
        return "0000"; // Default value for invalid registers
    } catch (const std::out_of_range &e) {
        return "0000"; // Default value for out-of-range registers
    }
}

std::string MainWindow::cleanRegister(std::string reg) {
    reg.erase(std::remove_if(reg.begin(), reg.end(), [](char ch) {
                  return ch == ',' || ch == '[' || ch == ']';
              }), reg.end());
    return reg;
}
