//
// Created by Vanessza Tar on 19.05.2025.
//
#pragma once
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "Service.h"

class ShoppingDialog : public QDialog {
    Q_OBJECT
  private:
    void showCoat(int index);
    void updateTotalLabel();

    Service& service;
    std::vector<TrenchCoat> filteredCoats;
    std::vector<TrenchCoat> boughtCoats;
    int currentIndex;
    double totalSum;

    QLineEdit* sizeEdit;
    QPushButton* enterButton;
    QPushButton* nextButton;
    QPushButton* cancelButton;
    QLabel* coatInfoLabel;
    QLabel* totalLabel;

  private slots:
    void onEnterClicked();
    void onNextClicked();

  public:
    explicit ShoppingDialog(Service& service, QWidget* parent = nullptr);
};
