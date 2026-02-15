//
// Created by Vanessza Tar on 19.05.2025.
//
#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include "Service.h"

class AddCoatDialog : public QDialog {
  Q_OBJECT

  private:
    QLineEdit* sizeEdit;
    QLineEdit* colourEdit;
    QLineEdit* priceEdit;
    QLineEdit* quantityEdit;
    QLineEdit* photographEdit;
    QPushButton* addButton;
    QPushButton* cancelButton;

    Service& service;

  private slots:
    void onAddClicked();

  public:
    explicit AddCoatDialog(Service& service, QWidget* parent = nullptr);
};