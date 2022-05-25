#include "Mainwindow.h"
#include "Controller.h"
#include "Model.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    Model model;
    Controller controller(&window, &model);

    window.show();
    return a.exec();
}
