#pragma once
#include <QDialog>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <vector>
#include "Service.h"

class CheckoutDialog : public QDialog {
    Q_OBJECT
    private:
        Service& service;
        QTableView* coatTable;
        QLabel* totalPriceLabel;
        QPushButton* cancelButton;
        void populateTable();
public:
    explicit CheckoutDialog(Service& service, QWidget* parent = nullptr);
};
