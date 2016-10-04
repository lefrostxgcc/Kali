#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <boost/numeric/ublas/matrix.hpp>

using boost::numeric::ublas::matrix;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateBoxes();

private:
    using matrix_size_type = matrix<QLabel*>::size_type;

    static constexpr matrix_size_type rowCount{8};
    static constexpr matrix_size_type colCount{16};
    static constexpr int              imageSize {50};

    void generateImage();

    Ui::MainWindow  *ui;
    QImage          image {imageSize, imageSize, QImage::Format_ARGB32_Premultiplied};
    matrix<QLabel*> boxes {rowCount, colCount, nullptr};
};

#endif // MAINWINDOW_H
