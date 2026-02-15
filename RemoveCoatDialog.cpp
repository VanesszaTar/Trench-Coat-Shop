//
// Created by Vanessza Tar on 19.05.2025.
//
#include "RemoveCoatDialog.h"
#include <QLabel>
#include <QMessageBox>

RemoveCoatDialog::RemoveCoatDialog(Service& service, QWidget* parent) : QDialog(parent), service(service) {
  setWindowTitle("Remove A Trench Coat!");
  resize(400,200);
  auto* layout = new QVBoxLayout(this);

  auto* priceLabel = new QLabel("Price:", this);
  priceEdit = new QLineEdit(this);

  auto* photoLabel = new QLabel("Photo link:", this);
  photographEdit = new QLineEdit(this);

  layout->addWidget(priceLabel);
  layout->addWidget(priceEdit);
  layout->addWidget(photoLabel);
  layout->addWidget(photographEdit);

  auto* buttonLayout = new QHBoxLayout();
  removeButton = new QPushButton("Remove", this);
  cancelButton = new QPushButton("Cancel", this);

  buttonLayout->addWidget(removeButton);
  buttonLayout->addWidget(cancelButton);
  layout->addLayout(buttonLayout);

  connect(removeButton, &QPushButton::clicked, this, &RemoveCoatDialog::onRemoveClicked);
  connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void RemoveCoatDialog::onRemoveClicked() {
  int price = priceEdit->text().toInt();
  std::string photolink = photographEdit->text().toStdString();
  try{
    std::vector<TrenchCoat> allCoats = service.getAllCoatsService();
    bool found = false;
    TrenchCoat coatToRemove;
    for (const auto& coat : allCoats) {
      if (coat.getPrice() == price && coat.getPhotograph() == photolink) {
        coatToRemove = coat;  // full coat info
        found = true;
        break;
      }
    }
    if (!found) {
      QMessageBox::warning(this, "Error", "No trench coat found with that price and photograph.");
      priceEdit->clear();
      photographEdit->clear();
      return;
    }
    service.remove_coat_service(coatToRemove);
    accept();
  } catch (const std::exception& e) {
    QMessageBox::warning(this, "Error", e.what());
    priceEdit->clear();
    photographEdit->clear();
    }
}