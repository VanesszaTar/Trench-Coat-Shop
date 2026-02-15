//
// Created by Vanessza Tar on 13.05.2025.
//
#include "UserWindow.h"
#include "UserViewDialog.h"
#include "ShoppingDialog.h"
#include "CheckoutDialog.h"
#include "SaveBasketDialog.h"
#include "ViewSavedBasketDialog.h"

UserWindow::UserWindow(Service& service, QWidget *parent) : QWidget(parent), service(service) {
  setWindowTitle("User Window");
  this->resize(800, 600);
  setupUser();
}
void UserWindow::setupUser() {
  auto* layout = new QVBoxLayout(this);

  label = new QLabel("User options:",this);
  QFont font = label->font();
  font.setPointSize(24);
  font.setBold(true);
  font.setItalic(true);
  label->setFont(font);
  label->setAlignment(Qt::AlignCenter);
  layout->addSpacing(50);
  layout->addWidget(label);
  layout->addSpacing(130);

  viewBySizeButton = new QPushButton("View trench coats by size",this);
  goShoppingButton = new QPushButton("Go shopping",this);
  checkOutButton = new QPushButton("Check out",this);
  saveButton = new QPushButton("Save",this);
  viewSavedItemsButton = new QPushButton("View saved items",this);
  closeButton = new QPushButton("Close",this);

  viewBySizeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  goShoppingButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  checkOutButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  saveButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  viewSavedItemsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  QFont buttonFont = viewBySizeButton->font();
  buttonFont.setBold(true);
  buttonFont.setPointSize(12);
  viewBySizeButton->setFont(buttonFont);
  goShoppingButton->setFont(buttonFont);
  checkOutButton->setFont(buttonFont);
  saveButton->setFont(buttonFont);
  viewSavedItemsButton->setFont(buttonFont);
  closeButton->setFont(buttonFont);


  QSize buttonSize(200, 100);
  viewBySizeButton->setFixedSize(buttonSize);
  viewSavedItemsButton->setFixedSize(buttonSize);

  QSize buttonSize1(100, 100);
  goShoppingButton->setFixedSize(buttonSize1);
  checkOutButton->setFixedSize(buttonSize1);
  saveButton->setFixedSize(buttonSize1);

  auto* buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(viewBySizeButton);
  buttonLayout->addWidget(goShoppingButton);
  buttonLayout->addWidget(checkOutButton);
  buttonLayout->addWidget(saveButton);
  buttonLayout->addWidget(viewSavedItemsButton);
  buttonLayout->setAlignment(Qt::AlignCenter);
  layout->addLayout(buttonLayout);
  layout->addSpacing(30);
  layout->addStretch();

  closeButton->setFixedSize(120, 40);
  layout->addWidget(closeButton, 0, Qt::AlignHCenter);

  connect(closeButton, &QPushButton::clicked,this,&QWidget::close);
  connect(viewBySizeButton, &QPushButton::clicked,this,&UserWindow::openViewBySizeDialog);
  connect(goShoppingButton, &QPushButton::clicked, this, &UserWindow::onGoShoppingButtonClicked);
  connect(checkOutButton, &QPushButton::clicked, this, &UserWindow::onCheckOutButtonClicked);
  connect(saveButton, &QPushButton::clicked, this, &UserWindow::onSaveButtonClicked);
  connect(viewSavedItemsButton, &QPushButton::clicked, this, &UserWindow::onViewSavedItemsButtonClicked);
  setLayout(layout);
}

void UserWindow::openViewBySizeDialog() {
  auto* dialog = new UserViewDialog(service, this);
  dialog->exec();
}

void UserWindow::onGoShoppingButtonClicked() {
  auto* dialog = new ShoppingDialog(service, this);
  dialog->exec();
  delete dialog;
}

void UserWindow::onCheckOutButtonClicked() {
  auto* dialog = new CheckoutDialog(service, this);
  dialog->exec();
}

void UserWindow::onShoppingFinished(const std::vector<TrenchCoat>& boughtCoats, double totalSum) {
  // Store this info for checkout
  basket = boughtCoats;
  basketTotal = totalSum;

  // Optionally, update UI elements or show a message:
  QMessageBox::information(this, "Shopping finished", QString("You bought %1 coats, total: $%2")
                           .arg(basket.size())
                           .arg(basketTotal, 0, 'f', 2));
}

void UserWindow::onSaveButtonClicked() {
  auto* dialog = new SaveBasketDialog(service, this);
  dialog->exec();
}

void UserWindow::onViewSavedItemsButtonClicked() {
  auto* dialog = new ViewSavedBasketDialog(this);
  dialog->exec();
}