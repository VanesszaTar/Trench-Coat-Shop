//
// Created by Vanessza Tar on 13.05.2025.
//
#include "ViewAllAdmin.h"
#include <QHeaderView>
ViewAllWindow::ViewAllWindow(Service& service, QWidget* parent) : QWidget(parent), service(service) {
    this->resize(1500, 400);
    setWindowTitle("All Trench Coats");

    auto* layout = new QVBoxLayout(this);

    viewModeComboBox = new QComboBox(this);
    viewModeComboBox->addItem("Detailed");
    viewModeComboBox->addItem("Short");
    connect(viewModeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ViewAllWindow::onViewModeChanged);

    layout->addWidget(viewModeComboBox, 0, Qt::AlignLeft);

    coatTable = new QTableWidget(this);
    coatTable->setColumnCount(5);
    coatTable->setHorizontalHeaderLabels({"Size", "Colour", "Price", "Quantity", "Photograph"});
    layout->addWidget(coatTable);

    closeButton = new QPushButton("Close", this);
    closeButton->setFixedSize(100, 30);
    layout->addWidget(closeButton, 0, Qt::AlignHCenter);

    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    setLayout(layout);
    populateTable();
}

void ViewAllWindow::onViewModeChanged(int index) {
    bool detailed = (index == 0); // "Detailed" = 0, "Short" = 1
    populateTable();
}

void ViewAllWindow::populateTable() {
    bool isDetailed = viewModeComboBox->currentIndex() == 0;
    coatTable->setColumnWidth(4, 300);
    coatTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    coatTable->clearContents();
    auto coats = service.getAllCoatsService();
    coatTable->setRowCount(coats.size());

    if (isDetailed) {
        coatTable->setColumnCount(5);
        coatTable->setHorizontalHeaderLabels({"Size", "Colour", "Price", "Quantity", "Photograph"});
    } else {
        coatTable->setColumnCount(2);
        coatTable->setHorizontalHeaderLabels({"Size", "Colour"});
    }

    for (int row = 0; row < coats.size(); row++) {
        const auto& coat = coats[row];
        coatTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(coat.getSize())));
        coatTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(coat.getColour())));
        if (isDetailed){
            coatTable->setItem(row, 2, new QTableWidgetItem(QString::number(coat.getPrice())));
            coatTable->setItem(row, 3, new QTableWidgetItem(QString::number(coat.getQuantity())));
            coatTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(coat.getPhotograph())));
        }
    }
    coatTable->resizeColumnsToContents();
    coatTable->resizeRowsToContents();
}
