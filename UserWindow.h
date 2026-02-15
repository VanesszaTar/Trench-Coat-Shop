//
// Created by Vanessza Tar on 13.05.2025.
//
#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "Service.h"
#include <QMessageBox>
class UserWindow : public QWidget {
  Q_OBJECT

  private:
  QPushButton *viewBySizeButton;
  QPushButton *goShoppingButton;
  QPushButton *checkOutButton;
  QPushButton *saveButton;
  QPushButton *viewSavedItemsButton;
  QPushButton *closeButton;
  QLabel *label;

  Service& service;
  std::vector<TrenchCoat> basket;
  double basketTotal = 0.0;

  void setupUser();

  private slots:
    void openViewBySizeDialog();
    void onGoShoppingButtonClicked();
    void onCheckOutButtonClicked();
    void onShoppingFinished(const std::vector<TrenchCoat>& basket, double TotalSum);
    void onSaveButtonClicked();
    void onViewSavedItemsButtonClicked();


  public:
    explicit UserWindow(Service& service, QWidget *parent = nullptr);
    ~UserWindow() override = default;
};
