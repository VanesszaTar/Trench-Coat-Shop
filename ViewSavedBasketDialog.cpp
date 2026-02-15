//
// Created by Vanessza Tar on 19.05.2025.
//
#include "ViewSavedBasketDialog.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>

ViewSavedBasketDialog::ViewSavedBasketDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("View Saved Basket");
    resize(300, 150);

    auto* mainLayout = new QVBoxLayout(this);

    instructionLabel = new QLabel("Enter format (csv or html):", this);
    formatInput = new QLineEdit(this);

    enterButton = new QPushButton("Enter", this);
    cancelButton = new QPushButton("Cancel", this);

    mainLayout->addWidget(instructionLabel);
    mainLayout->addWidget(formatInput);

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(enterButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    connect(enterButton, &QPushButton::clicked, this, &ViewSavedBasketDialog::onEnterClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void ViewSavedBasketDialog::onEnterClicked() {
    QString format = formatInput->text().trimmed().toLower();
    QString filename;

    if (format == "csv") {
        filename = "basket.csv";
    } else if (format == "html") {
        filename = "basket.html";
    } else {
        QMessageBox::warning(this, "Invalid Format", "Please enter either 'csv' or 'html'.");
        return;
    }

    QFileInfo fileInfo(filename);
    if (!fileInfo.exists()) {
        QMessageBox::warning(this, "File Not Found", QString("The file %1 does not exist.").arg(filename));
        return;
    }

    QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
    accept();
    clearHtmlAndCsvFiles();
}
void ViewSavedBasketDialog::clearHtmlAndCsvFiles() {
    QFile htmlFile("basket.html");
    if (htmlFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        htmlFile.close();
    }

    QFile csvFile("basket.csv");
    if (csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        csvFile.close();
    }
}
