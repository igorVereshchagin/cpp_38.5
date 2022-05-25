#include <QApplication>

#include "./ui_blur.h"

#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QFileDialog>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <cassert>

class BlurMainWindow : public QMainWindow
{
  Q_OBJECT
  QWidget* pictureView = nullptr;
  QSlider* blurSlider = nullptr;
  QPixmap inputPicture;
  QPixmap bluredPicture;
public:
  BlurMainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {}
  void paintEvent(QPaintEvent* e) override {
    assert(pictureView != nullptr);
    QPainter p(this);
    p.drawPixmap(pictureView->rect(), bluredPicture);
  }
  void setPictureView(QWidget* widget) {pictureView = widget;}
  void setBlurSlider(QSlider* slider) {blurSlider = slider;}
public slots:
  void openFile() {
    assert(pictureView != nullptr);
    assert(blurSlider != nullptr);
    inputPicture = QPixmap(QFileDialog::getOpenFileName(nullptr, "Open picture", "./../" ));
    this->setFixedSize(inputPicture.rect().width(), inputPicture.rect().height() + 200);
    pictureView->setGeometry(inputPicture.rect());
    bluredPicture = inputPicture;
    blurSlider->setValue(0);
  };
  void blurPicture(int val)
  {
    
  }
};

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  BlurMainWindow window(nullptr);
  Ui::MainWindow blur;
  blur.setupUi(&window);
  window.setPictureView(blur.widget);
  window.setBlurSlider(blur.horizontalSlider);
  QObject::connect(blur.pushButton, &QPushButton::clicked, &window, &BlurMainWindow::openFile);
  QObject::connect(blur.horizontalSlider, &QSlider::valueChanged, &window, &BlurMainWindow::blurPicture);
  window.resize(800, 600);
  window.show();
  return QApplication::exec();
}

#include "main.moc"