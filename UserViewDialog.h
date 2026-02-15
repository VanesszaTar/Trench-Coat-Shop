//
// Created by Vanessza Tar on 19.05.2025.
//
#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include "Service.h"

class UserViewDialog : public QDialog {
  Q_OBJECT

  private:
    Service& service;
    QLineEdit* sizeEdit;
    QPushButton* enterButton;
    QLabel* infoLabel;
    QPushButton* nextButton;
    QPushButton* previousButton;
    QPushButton* cancelButton;

    std::vector <TrenchCoat> filteredCoats;
    int currentIndex;

    void showCoat(int index);
    void clearDisplay();

  private slots:
    void onEnterClicked();
    void onNextClicked();
    void onPreviousClicked();

  public:
    explicit UserViewDialog(Service& service, QWidget* parent = nullptr);
};
