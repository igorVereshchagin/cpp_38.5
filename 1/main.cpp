#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QMediaPlayer>

class ImageButton : public QPushButton
{
  Q_OBJECT
private:
  QPixmap buttonUpPix;
  QPixmap buttonDownPix;
  QPixmap buttonCurPix;
  QMediaPlayer clickSound;
  bool isDown = false;
public:
  ImageButton() = default;
  ImageButton(QWidget *parent);
  void paintEvent(QPaintEvent *e) override;
  QSize sizeHint() const override;
  QSize minimumSizeHint() const override;
  void keyPressEvent(QKeyEvent *e) override;
public slots:
  void setUp();
  void setDown();
};

ImageButton::ImageButton(QWidget *parent) : clickSound()
{
  setParent(parent);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  buttonUpPix = QPixmap("../butt_unpr.png");
  buttonDownPix = QPixmap ("../butt_pressed.png");
  buttonCurPix = buttonUpPix;
  setGeometry(buttonCurPix.rect());
  connect(this, &QPushButton::clicked, this, &ImageButton::setDown);
  clickSound.setMedia(QUrl::fromLocalFile("../TunePocket-Fast-Energetic-Whoosh-Pop-Preview.mp3"));
}

void ImageButton::paintEvent(QPaintEvent *e)
{
  QPainter p(this);
  p.drawPixmap(e->rect(), buttonCurPix);
}

QSize ImageButton::sizeHint() const
{
  return QSize (100, 100);
}

QSize ImageButton::minimumSizeHint() const
{
  return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e)
{
  setDown();
}

void ImageButton::setDown()
{
  buttonCurPix = buttonDownPix;
  update();
  QTimer::singleShot(100, this, &ImageButton::setUp);
  clickSound.play();
}

void ImageButton::setUp()
{
  buttonCurPix = buttonUpPix;
  update();
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ImageButton button(nullptr);
  button.setFixedSize(100, 100);
  button.move(1000, 400);
  button.show();
  return QApplication::exec();
}

#include <main.moc>