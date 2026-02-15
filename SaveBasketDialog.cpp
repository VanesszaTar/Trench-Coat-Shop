//
// Created by Vanessza Tar on 19.05.2025.
//
#include "SaveBasketDialog.h"
#include "CSVBasketExporter.h"
#include "HTMLBasketExporter.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

SaveBasketDialog::SaveBasketDialog(Service& service, QWidget* parent) : QDialog(parent), service(service) {
    setWindowTitle("Save Shopping Basket");
    resize(300, 150);

    auto* mainLayout = new QVBoxLayout(this);

    instructionLabel = new QLabel("Enter format (csv or html):", this);
    formatInput = new QLineEdit(this);

    saveButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel", this);

    mainLayout->addWidget(instructionLabel);
    mainLayout->addWidget(formatInput);

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &SaveBasketDialog::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void SaveBasketDialog::onSaveClicked() {
    QString format = formatInput->text().trimmed().toLower();
    std::string filename;

    BasketExporter* exporter = nullptr;
    if (format == "csv") {
        filename = "basket.csv";
        exporter = new CSVBasketExporter();
    } else if (format == "html") {
        filename = "basket.html";
        exporter = new HTMLBasketExporter();
    } else {
        QMessageBox::warning(this, "Invalid Format", "Please enter either 'csv' or 'html'.");
        return;
    }
    try {
        service.exportBasketToFileService(exporter, filename);
        QMessageBox::information(this, "Success", QString("Basket saved to %1.").arg(QString::fromStdString(filename)));
        accept();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
        formatInput->clear();
    }
    delete exporter;
}
