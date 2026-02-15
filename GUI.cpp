//
// Created by Vanessza Tar on 13.05.2025.
//
#include "GUI.h"
#include <QString>
#include "AdminWindow.h"
#include "UserWindow.h"
#include <QFont>

GUI::GUI(Service& service, QWidget* parent) : QWidget(parent), service(service) {
  setupUI();
}

GUI::~GUI() {
}

void GUI::setupUI() {
  auto* mainLayout = new QVBoxLayout(this);

  QLabel* welcomeLabel = new QLabel("Welcome to the TrenchCoat Application!\nPlease choose your role.", this);
  QFont labelFont;
  labelFont.setPointSize(24);
  labelFont.setBold(true);
  labelFont.setItalic(true);
  welcomeLabel->setFont(labelFont);
  welcomeLabel->setAlignment(Qt::AlignCenter);
  mainLayout->addWidget(welcomeLabel);

  auto* buttonLayout = new QHBoxLayout();
  buttonLayout->addStretch();

  adminButton = new QPushButton("Administrator",this);
  adminButton->setFixedSize(200, 60);
  connect(adminButton, &QPushButton::clicked, this, &GUI::adminMode);

  QFont buttonFont = adminButton->font();
  buttonFont.setBold(true);
  buttonFont.setPointSize(18);
  adminButton->setFont(buttonFont);
  buttonLayout->addWidget(adminButton);

  buttonLayout->addSpacing(40);

  userButton = new QPushButton("User",this);
  userButton->setFixedSize(200, 60);
  connect(userButton, &QPushButton::clicked, this, &GUI::userMode);
  userButton->setFont(buttonFont);
  buttonLayout->addWidget(userButton);

  buttonLayout->addStretch();

  mainLayout->addSpacing(170);
  mainLayout->addLayout(buttonLayout);
  mainLayout->addStretch();

  closeButton = new QPushButton("Close", this);
  closeButton->setFixedSize(100, 30);
  connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
  mainLayout->addWidget(closeButton, 0, Qt::AlignHCenter);
  setLayout(mainLayout);
}

void GUI::adminMode() {
  AdminWindow* adminWindow = new AdminWindow(service);
  adminWindow->show();
}

void GUI::userMode() {
  UserWindow* userWindow = new UserWindow(service);
  userWindow->show();
}