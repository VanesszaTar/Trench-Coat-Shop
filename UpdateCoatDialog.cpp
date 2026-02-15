//
// Created by Vanessza Tar on 19.05.2025.
//
#include "UpdateCoatDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

UpdateCoatDialog::UpdateCoatDialog(Service& service, QWidget* parent) : QDialog(parent), service(service) {
  setWindowTitle("Update A Trench Coat!");
  resize(400,300);
  auto* layout = new QVBoxLayout(this);

  layout->addWidget(new QLabel("Current price:", this));
  oldPriceEdit = new QLineEdit(this);
  layout->addWidget(oldPriceEdit);

  layout->addWidget(new QLabel("Current photo link:", this));
  oldPhotographEdit = new QLineEdit(this);
  layout->addWidget(oldPhotographEdit);

  layout->addSpacing(15);

  layout->addWidget(new QLabel("New size:", this));
  newSizeEdit = new QLineEdit(this);
  layout->addWidget(newSizeEdit);

  layout->addWidget(new QLabel("New colour:", this));
  newColourEdit = new QLineEdit(this);
  layout->addWidget(newColourEdit);

  layout->addWidget(new QLabel("New price:", this));
  newPriceEdit = new QLineEdit(this);
  layout->addWidget(newPriceEdit);

  layout->addWidget(new QLabel("New quantity:", this));
  newQuantityEdit = new QLineEdit(this);
  layout->addWidget(newQuantityEdit);

  layout->addWidget(new QLabel("New photo link:", this));
  newPhotographEdit = new QLineEdit(this);
  layout->addWidget(newPhotographEdit);

  auto* buttonLayout = new QHBoxLayout();
  updateButton = new QPushButton("Update", this);
  cancelButton = new QPushButton("Cancel", this);
  buttonLayout->addWidget(updateButton);
  buttonLayout->addWidget(cancelButton);
  layout->addLayout(buttonLayout);

  connect(updateButton, &QPushButton::clicked, this, &UpdateCoatDialog::onUpdateButtonClicked);
  connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void UpdateCoatDialog::onUpdateButtonClicked() {
  std::string newSize = newSizeEdit->text().toStdString();
  std::string newColour = newColourEdit->text().toStdString();
  int newPrice = newPriceEdit->text().toInt();
  int newQuantity = newQuantityEdit->text().toInt();
  int price = oldPriceEdit->text().toInt();
  std::string photolink = oldPhotographEdit->text().toStdString();
  std::string newPhotolink = newPhotographEdit->text().toStdString();
    try{
      std::vector<TrenchCoat> allCoats = service.getAllCoatsService();
      bool found = false;
      TrenchCoat coatToUpdate;
      for (const auto& coat : allCoats) {
        if (coat.getPrice() == price && coat.getPhotograph() == photolink) {
          coatToUpdate = coat;  // full coat info
          found = true;
          break;
        }
      }
      if (!found) {
        QMessageBox::warning(this, "Error", "No trench coat found with that price and photograph.");
        oldPriceEdit->clear();
        oldPhotographEdit->clear();
        return;
      }
      service.update_coat_service(coatToUpdate, newSize, newColour, newPrice, newQuantity, newPhotolink);
      accept();
  } catch (const std::exception& e) {
    QMessageBox::warning(this, "Error", e.what());
    oldPriceEdit->clear();
    oldPhotographEdit->clear();
    newSizeEdit->clear();
    newColourEdit->clear();
    newPriceEdit->clear();
    newQuantityEdit->clear();
    newPhotographEdit->clear();
  }
}