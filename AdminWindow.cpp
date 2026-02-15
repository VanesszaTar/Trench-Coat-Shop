//
// Created by Vanessza Tar on 13.05.2025.
//
#include "AdminWindow.h"
#include "ViewAllAdmin.h"
#include "AddCoatDialog.h"
#include "RemoveCoatDialog.h"
#include "UpdateCoatDialog.h"

AdminWindow::AdminWindow(Service& service, QWidget* parent) : QWidget(parent), service(service) {
    setWindowTitle("Administrator Window");
    this->resize(800, 600);
    setupAdmin();
    updateUndoRedoButtons();
    connect(this, &AdminWindow::dataUpdated, this, &AdminWindow::updateUndoRedoButtons);
}
void AdminWindow::setupAdmin() {
    auto* layout = new QVBoxLayout(this);

    label = new QLabel("Administrator options:",this);
    QFont font = label->font();
    font.setPointSize(24);
    font.setBold(true);
    font.setItalic(true);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    layout->addSpacing(50);
    layout->addWidget(label);
    layout->addSpacing(130);
    addButton = new QPushButton("Add",this);
    removeButton = new QPushButton("Remove",this);
    updateButton = new QPushButton("Update",this);
    viewAllButton = new QPushButton("View All",this);
    closeButton = new QPushButton("Close",this);

    QSize buttonSize(100, 100);
    addButton->setFixedSize(buttonSize);
    removeButton->setFixedSize(buttonSize);
    updateButton->setFixedSize(buttonSize);
    viewAllButton->setFixedSize(buttonSize);

    QFont buttonFont = addButton->font();
    buttonFont.setBold(true);
    buttonFont.setPointSize(12);
    addButton->setFont(buttonFont);
    removeButton->setFont(buttonFont);
    updateButton->setFont(buttonFont);
    viewAllButton->setFont(buttonFont);
    closeButton->setFont(buttonFont);

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(updateButton);
    buttonLayout->addWidget(viewAllButton);
    buttonLayout->setAlignment(Qt::AlignCenter);
    layout->addLayout(buttonLayout);
    layout->addSpacing(30);
    layout->addStretch();

    undoButton = new QPushButton("Undo", this);
    redoButton = new QPushButton("Redo", this);

    // Add to layout
    layout->addWidget(undoButton);
    layout->addWidget(redoButton);

    // Connect buttons
    connect(undoButton, &QPushButton::clicked, this, &AdminWindow::handleUndo);
    connect(redoButton, &QPushButton::clicked, this, &AdminWindow::handleRedo);

    // Add keyboard shortcuts
    undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);

    connect(undoShortcut, &QShortcut::activated, this, &AdminWindow::handleUndo);
    connect(redoShortcut, &QShortcut::activated, this, &AdminWindow::handleRedo);


    closeButton->setFixedSize(120, 40);
    layout->addWidget(closeButton, 0, Qt::AlignHCenter);

    connect(viewAllButton, &QPushButton::clicked, this, &AdminWindow::openViewAllWindow);
    connect(closeButton, &QPushButton::clicked,this,&QWidget::close);
    connect(addButton, &QPushButton::clicked, this, &AdminWindow::addButtonClicked);
    connect(removeButton, &QPushButton::clicked, this, &AdminWindow::removeButtonClicked);
    connect(updateButton, &QPushButton::clicked, this, &AdminWindow::updateButtonClicked);
    setLayout(layout);
}

void AdminWindow::openViewAllWindow() {
    auto* viewWindow = new ViewAllWindow(service);
    connect(this, &AdminWindow::dataUpdated, viewWindow, &ViewAllWindow::populateTable);
    viewWindow->show();
}

void AdminWindow::addButtonClicked() {
    AddCoatDialog dialog(service, this);
    if (dialog.exec() == QDialog::Accepted) {
        emit dataUpdated();
    }
}

void AdminWindow::removeButtonClicked() {
    RemoveCoatDialog dialog(service, this);
    if (dialog.exec() == QDialog::Accepted) {
        emit dataUpdated();
    }
}

void AdminWindow::updateButtonClicked() {
    UpdateCoatDialog dialog(service, this);
    if (dialog.exec() == QDialog::Accepted) {
        emit dataUpdated();
    }
}

void AdminWindow::handleUndo() {
    try {
        service.undo();
        emit dataUpdated();
        updateUndoRedoButtons();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Undo Error", e.what());
    }
}

void AdminWindow::handleRedo() {
    try {
        service.redo();
        emit dataUpdated();
        updateUndoRedoButtons();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Redo Error", e.what());
    }
}

void AdminWindow::updateUndoRedoButtons() {
    undoButton->setEnabled(!service.undoStackEmpty());
    redoButton->setEnabled(!service.redoStackEmpty());
}