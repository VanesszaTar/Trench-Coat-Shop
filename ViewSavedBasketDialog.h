//
// Created by Vanessza Tar on 19.05.2025.
//
#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ViewSavedBasketDialog : public QDialog {
    Q_OBJECT

    private:
        QLabel* instructionLabel;
        QLineEdit* formatInput;
        QPushButton* enterButton;
        QPushButton* cancelButton;

    private slots:
        void onEnterClicked();
        void clearHtmlAndCsvFiles();

    public:
        explicit ViewSavedBasketDialog(QWidget* parent = nullptr);
};
