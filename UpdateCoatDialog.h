//
// Created by Vanessza Tar on 19.05.2025.
//
#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "Service.h"

class UpdateCoatDialog : public QDialog {
  Q_OBJECT

  private:
    Service& service;
    QLineEdit* oldPriceEdit;
    QLineEdit* oldPhotographEdit;

    QLineEdit* newSizeEdit;
    QLineEdit* newColourEdit;
    QLineEdit* newPriceEdit;
    QLineEdit* newQuantityEdit;
    QLineEdit* newPhotographEdit;

    QPushButton* updateButton;
    QPushButton* cancelButton;

  private slots:
    void onUpdateButtonClicked();

  public:
    explicit UpdateCoatDialog(Service& service, QWidget* parent = nullptr);
};
