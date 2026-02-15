//
// Created by Vanessza Tar on 19.05.2025.
//
#include "UserViewDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

UserViewDialog::UserViewDialog(Service& service, QWidget* parent) : QDialog(parent), service(service), currentIndex(0) {
  setWindowTitle("View Trench Coats By Size!");
  resize(450,350);
  auto* mainLayout = new QVBoxLayout(this);
  sizeEdit = new QLineEdit(this);
  sizeEdit->setPlaceholderText("Enter desired size");

  enterButton = new QPushButton("Enter",this);
  infoLabel = new QLabel(this);
  infoLabel->setWordWrap(true);
  infoLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  auto* navLayout = new QHBoxLayout();
  previousButton = new QPushButton("< Previous",this);
  nextButton = new QPushButton("Next >",this);
  navLayout->addWidget(previousButton);
  navLayout->addWidget(nextButton);

  mainLayout->addWidget(sizeEdit);
  mainLayout->addWidget(enterButton);
  mainLayout->addWidget(infoLabel);
  mainLayout->addLayout(navLayout);

  cancelButton = new QPushButton("Cancel",this);
  cancelButton->setFixedWidth(100);
  auto* cancelLayout = new QHBoxLayout();
  cancelLayout->addStretch();
  cancelLayout->addWidget(cancelButton);
  cancelLayout->addStretch();

  mainLayout->addLayout(cancelLayout);
  connect(enterButton, &QPushButton::clicked, this, &UserViewDialog::onEnterClicked);
  connect(nextButton, &QPushButton::clicked, this, &UserViewDialog::onNextClicked);
  connect(previousButton, &QPushButton::clicked, this, &UserViewDialog::onPreviousClicked);
  connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void UserViewDialog::onEnterClicked() {
  try{
    std::string size = sizeEdit->text().toStdString();
    filteredCoats.clear();
    currentIndex = 0;
    for (const auto& coat : service.getCoatsBySizeService(size)) {
      filteredCoats.push_back(coat);
    }
    showCoat(currentIndex);
  } catch (const std::exception& e) {
      QMessageBox::critical(this, "Error", e.what());
  }
}

void UserViewDialog::showCoat(int index) {
  if (index >= 0 && index < filteredCoats.size()) {
    const auto& coat = filteredCoats[index];
    QString info = QString("Size: %1\nColour: %2\nPrice: %3\nQuantity: %4\nPhotograph: %5")
            .arg(QString::fromStdString(coat.getSize()))
            .arg(QString::fromStdString(coat.getColour()))
            .arg(coat.getPrice())
            .arg(coat.getQuantity())
            .arg(QString::fromStdString(coat.getPhotograph()));
    infoLabel->setText(info);
  }
}

void UserViewDialog::clearDisplay() {
  infoLabel->clear();
}

void UserViewDialog::onNextClicked() {
  if (!filteredCoats.empty() && currentIndex < filteredCoats.size() - 1) {
    currentIndex++;
    showCoat(currentIndex);
  }
}

void UserViewDialog::onPreviousClicked() {
  if (!filteredCoats.empty() && currentIndex > 0) {
    currentIndex--;
    showCoat(currentIndex);
  }
}