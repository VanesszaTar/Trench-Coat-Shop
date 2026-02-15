//
// Created by Vanessza Tar on 26.03.2025.
//
#include <QApplication>
#include "Service.h"
#include "Repository.h"
#include "TrenchCoat.h"
#include "GUI.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Repository repo("CoatsFile.txt");
    Service service(&repo);

    GUI gui(service);
    gui.setWindowTitle("Trench Coat Application");
    gui.resize(800, 600);
    gui.show();

    return app.exec();
}
