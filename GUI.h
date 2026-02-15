//
// Created by Vanessza Tar on 13.05.2025.
//
#pragma once
#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "Service.h"

class GUI : public QWidget {
  Q_OBJECT

  private:
    Service& service;
    QTableWidget* coatTable;
    QPushButton* closeButton;
    QPushButton* adminButton;
    QPushButton* userButton;
    QSpacerItem* spacer;

    void setupUI();

  private slots:
    void adminMode();
    void userMode();

  public:
    explicit GUI(Service& service, QWidget* parent = nullptr);
    ~GUI();
};