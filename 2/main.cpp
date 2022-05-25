#include <QApplication>
#include <QPushButton>

#include "./ui_webEdit.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QMainWindow window(nullptr);
  Ui::MainWindow editor;
  editor.setupUi(&window);
  editor.plainTextEdit->setPlainText(QString("<H1>Hello world!!!</H1>"));
  editor.webEngineView->setHtml(editor.plainTextEdit->toPlainText());
  QObject::connect(editor.plainTextEdit, &QPlainTextEdit::textChanged, [editor] () {
    editor.webEngineView->setHtml(editor.plainTextEdit->toPlainText());
  });
  window.resize(800, 600);
  window.show();
  return QApplication::exec();
}
