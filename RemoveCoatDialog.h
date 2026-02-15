//
// Created by Vanessza Tar on 19.05.2025.
//
#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "Service.h"

class RemoveCoatDialog : public QDialog {
  Q_OBJECT

  private:
    Service& service;
    QLineEdit* priceEdit;
    QLineEdit* photographEdit;
    QPushButton* removeButton;
    QPushButton* cancelButton;

  private slots:
    void onRemoveClicked();
  public:
    explicit RemoveCoatDialog(Service& service, QWidget* parent = nullptr);
};
