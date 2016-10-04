#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <ctime>
#include <QTimer>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (matrix_size_type row{}; row < rowCount; ++row)
        for (matrix_size_type col{}; col < colCount; ++col)
        {
            boxes(row, col) = new QLabel;
            boxes(row, col)->setFixedSize(imageSize, imageSize);
            ui->gridLayout->addWidget(boxes(row, col), row, col);
        }

    setFixedSize(imageSize * colCount, imageSize * rowCount);

    std::srand(std::time(0));
    QTimer *timer = new QTimer{this};
    connect(timer, &QTimer::timeout, this, &MainWindow::updateBoxes);

    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateBoxes()
{
    generateImage();

    for (matrix_size_type row{}; row < boxes.size1(); ++row)
        for (matrix_size_type col{}; col < boxes.size2(); ++col)
            boxes(row, col)->setPixmap(QPixmap::fromImage(image.mirrored(col % 2 != 0, row % 2 != 0)));
}

void MainWindow::generateImage()
{
    QPainter painter {&image};
    painter.setRenderHint(QPainter::Antialiasing, true);

    constexpr int maxColor{255};

    QBrush brush {QColor::fromRgb(std::rand() % maxColor, std::rand() % maxColor, std::rand() % maxColor)};
    QPen   pen   {QColor::fromRgb(std::rand() % maxColor, std::rand() % maxColor, std::rand() % maxColor)};

    painter.setPen   (pen);
    painter.setBrush (brush);

    painter.drawLine    (std::rand() % imageSize, std::rand() % imageSize, std::rand() % imageSize, std::rand() % imageSize);
    painter.drawEllipse (std::rand() % imageSize, std::rand() % imageSize, std::rand() % imageSize, std::rand() % imageSize);
}
