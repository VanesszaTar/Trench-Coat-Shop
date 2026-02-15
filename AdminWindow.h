//
// Created by Vanessza Tar on 13.05.2025.
//
#pragma once
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QShortcut>
#include <QMessageBox>
#include "Service.h"

class AdminWindow : public QWidget {
  Q_OBJECT

  private:
    Service& service;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *updateButton;
    QPushButton *viewAllButton;
    QPushButton *closeButton;
    QLabel *label;

    QPushButton *undoButton;
    QPushButton *redoButton;
    QTableWidget *coatTable;

    QShortcut *undoShortcut;
    QShortcut *redoShortcut;
    void setupAdmin();

  private slots:
    void openViewAllWindow();
    void addButtonClicked();
    void removeButtonClicked();
    void updateButtonClicked();
    void handleUndo();
    void handleRedo();
    void updateUndoRedoButtons();

  public:
    explicit AdminWindow(Service& service, QWidget* parent = nullptr);
    ~AdminWindow() override = default;

  signals:
    void dataUpdated();
};