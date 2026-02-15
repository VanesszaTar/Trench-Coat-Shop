//
// Created by Vanessza Tar on 13.05.2025.
//
#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include "Service.h"

class ViewAllWindow : public QWidget {
    Q_OBJECT

    private:
        Service& service;
        QTableWidget* coatTable;
        QPushButton* closeButton;
        QComboBox* viewModeComboBox;

    private slots:
        void onViewModeChanged(int index);

    public slots:
        void populateTable();
    public:
        explicit ViewAllWindow(Service& service, QWidget* parent = nullptr);
        ~ViewAllWindow() override = default;
};
