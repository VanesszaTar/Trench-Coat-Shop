//
// Created by Vanessza Tar on 19.05.2025.
//
#include "AddCoatDialog.h"
#include <QMessageBox>

AddCoatDialog::AddCoatDialog(Service& service, QWidget* parent) : QDialog(parent), service(service) {
  setWindowTitle("Add A New Trench Coat!");
  resize(400,300);

  auto* formLayout = new QFormLayout(this);

  sizeEdit = new QLineEdit(this);
  colourEdit = new QLineEdit(this);
  priceEdit = new QLineEdit(this);
  quantityEdit = new QLineEdit(this);
  photographEdit = new QLineEdit(this);

  formLayout->addRow("Size:", sizeEdit);
  formLayout->addRow("Colour:", colourEdit);
  formLayout->addRow("Price:", priceEdit);
  formLayout->addRow("Quantity:", quantityEdit);
  formLayout->addRow("Photo link:", photographEdit);

  addButton = new QPushButton("Add", this);
  cancelButton = new QPushButton("Cancel", this);

  auto* buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(addButton);
  buttonLayout->addWidget(cancelButton);
  formLayout->addRow(buttonLayout);

  connect(addButton, &QPushButton::clicked, this, &AddCoatDialog::onAddClicked);
  connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void AddCoatDialog::onAddClicked() {
  std::string size = sizeEdit->text().toStdString();
  std::string colour = colourEdit->text().toStdString();
  int price = priceEdit->text().toInt();
  int quantity = quantityEdit->text().toInt();
  std::string photolink = photographEdit->text().toStdString();

  try{
    TrenchCoat newCoat = TrenchCoat(size, colour, price, quantity, photolink);
    service.add_coat_service(newCoat);
    accept();
  } catch (const std::exception& e) {
    QMessageBox::warning(this, "Error", e.what());
    sizeEdit->clear();
    colourEdit->clear();
    priceEdit->clear();
    quantityEdit->clear();
    photographEdit->clear();
  }
}