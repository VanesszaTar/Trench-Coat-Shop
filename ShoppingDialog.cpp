#include "ShoppingDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include <QDesktopServices>
#include <QUrl>

ShoppingDialog::ShoppingDialog(Service& service, QWidget* parent) : QDialog(parent), service(service), currentIndex(0), totalSum(0.0) {
  setWindowTitle("Go Shopping!");
  resize(400, 350);
  auto* mainLayout = new QVBoxLayout(this);

  sizeEdit = new QLineEdit(this);
  sizeEdit->setPlaceholderText("Enter desired size");

  enterButton = new QPushButton("Enter", this);
  coatInfoLabel = new QLabel(this);
  coatInfoLabel->setWordWrap(true);
  coatInfoLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  nextButton = new QPushButton("Next >", this);
  nextButton->setEnabled(false);

  totalLabel = new QLabel("Total: $0.00", this);
  totalLabel->setAlignment(Qt::AlignCenter);

  mainLayout->addWidget(sizeEdit);
  mainLayout->addWidget(enterButton);
  mainLayout->addWidget(coatInfoLabel);
  mainLayout->addWidget(nextButton);
  mainLayout->addWidget(totalLabel);

  cancelButton = new QPushButton("Cancel", this);
  cancelButton->setFixedWidth(100);

  auto* cancelLayout = new QHBoxLayout();
  cancelLayout->addStretch();
  cancelLayout->addWidget(cancelButton);
  cancelLayout->addStretch();
  mainLayout->addLayout(cancelLayout);

  connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
  connect(enterButton, &QPushButton::clicked, this, &ShoppingDialog::onEnterClicked);
  connect(nextButton, &QPushButton::clicked, this, &ShoppingDialog::onNextClicked);
}

void ShoppingDialog::onEnterClicked() {
  try {
    std::string size = sizeEdit->text().toStdString();
    filteredCoats = service.getCoatsBySizeService(size);
    currentIndex = 0;
    totalSum = 0;
    updateTotalLabel();

    if (filteredCoats.empty()) {
      QMessageBox::information(this, "No coats", "No coats found for the given size.");
      coatInfoLabel->clear();
      nextButton->setEnabled(false);
      return;
    }

    nextButton->setEnabled(true);
    showCoat(currentIndex);
  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error", e.what());
    sizeEdit->clear();
  }
}

void ShoppingDialog::showCoat(int index) {
  if (index < 0 || index >= filteredCoats.size()) {
    coatInfoLabel->setText("No more coats to show.");
    nextButton->setEnabled(false);
    return;
  }

  const auto& coat = filteredCoats[index];
  QString info = QString("Size: %1\nColour: %2\nPrice: $%3\nQuantity: %4\nPhotograph: %5")
                    .arg(QString::fromStdString(coat.getSize()))
                    .arg(QString::fromStdString(coat.getColour()))
                    .arg(coat.getPrice())
                    .arg(coat.getQuantity())
                    .arg(QString::fromStdString(coat.getPhotograph()));

  coatInfoLabel->setText(info);
  auto viewPhoto = QMessageBox::question(this, "View Photo", "Would you like to view the photo of this coat?", QMessageBox::Yes | QMessageBox::No);
  if (viewPhoto == QMessageBox::Yes) {
    QDesktopServices::openUrl(QUrl(QString::fromStdString(coat.getPhotograph())));
  }

  auto buy = QMessageBox::question(this, "Buy Coat", "Would you like to buy this coat?", QMessageBox::Yes | QMessageBox::No);
  if (buy == QMessageBox::Yes) {
    try{
      if (coat.getQuantity() > 0) {
        service.add_to_basket_service(coat);
        service.update_coat_service(coat, coat.getSize(), coat.getColour(), coat.getPrice(), coat.getQuantity() - 1, coat.getPhotograph());
        totalSum += coat.getPrice();
        boughtCoats.push_back(coat);
        updateTotalLabel();
      }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
      }
  }
}

void ShoppingDialog::onNextClicked() {
  if (currentIndex + 1 < filteredCoats.size()) {
    currentIndex++;
    showCoat(currentIndex);
  } else {
    QMessageBox::information(this, "End", "You have reached the last coat.");
    nextButton->setEnabled(false);
    accept();
  }
}

void ShoppingDialog::updateTotalLabel() {
  totalLabel->setText(QString("Total: $%1").arg(totalSum, 0, 'f', 2));
}
