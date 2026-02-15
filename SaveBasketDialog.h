//
// Created by Vanessza Tar on 19.05.2025.
//

#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "Service.h"

class SaveBasketDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit* formatInput;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QLabel* instructionLabel;
    Service& service;

    private slots:
        void onSaveClicked();

public:
    explicit SaveBasketDialog(Service& service, QWidget* parent = nullptr);
};
