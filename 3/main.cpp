#include <QApplication>

#include "./ui_blur.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <cassert>

class BlurMainWindow : public QMainWindow
{
  Q_OBJECT
  QWidget* pictureView = nullptr;
  QSlider* blurSlider = nullptr;
  QImage sourceImage;
  QImage bluredImage;
public:
  BlurMainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {}
  void paintEvent(QPaintEvent* e) override {
    assert(pictureView != nullptr);
    QPainter p(this);
    p.drawPixmap(pictureView->rect(), QPixmap::fromImage(bluredImage));
  }
  void setPictureView(QWidget* widget) {pictureView = widget;}
  void setBlurSlider(QSlider* slider) {blurSlider = slider;}
public slots:
  void openFileSlot() {
    assert(pictureView != nullptr);
    assert(blurSlider != nullptr);
    sourceImage = QImage(QFileDialog::getOpenFileName(nullptr, "Open picture", "./../" ));
    this->setFixedSize(sourceImage.rect().width(), sourceImage.rect().height() + 200);
    pictureView->setGeometry(sourceImage.rect());
    bluredImage = sourceImage;
    blurSlider->setValue(0);
  };
  void blurImageSlot(int val)
  {
    bluredImage = blurImage(sourceImage, val);
    update();
  }
  static QImage blurImage(const QImage &source, int radius)
  {
    if (source.isNull())
      return QImage();
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(source));
    auto *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(radius);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);
    QImage result(source.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    scene.render(&painter, QRectF(), QRectF(0, 0, source.width(), source.height()));
    delete blur;
    return result;
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
  QObject::connect(blur.pushButton, &QPushButton::clicked, &window, &BlurMainWindow::openFileSlot);
  QObject::connect(blur.horizontalSlider, &QSlider::valueChanged, &window, &BlurMainWindow::blurImageSlot);
  window.resize(800, 600);
  window.show();
  return QApplication::exec();
}

#include "main.moc"