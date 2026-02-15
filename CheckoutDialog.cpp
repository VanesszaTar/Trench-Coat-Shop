#include "CheckoutDialog.h"
#include "BasketTableModel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
CheckoutDialog::CheckoutDialog(Service& service, QWidget* parent) : service(service), QDialog(parent) {
    setWindowTitle("Checkout");
    resize(600, 400);

    auto* mainLayout = new QVBoxLayout(this);

    coatTable = new QTableView(this);
    coatTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(coatTable);

    totalPriceLabel = new QLabel(this);
    totalPriceLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(totalPriceLabel);

    cancelButton = new QPushButton("Cancel", this);
    cancelButton->setFixedWidth(100);
    auto* cancelLayout = new QHBoxLayout();
    cancelLayout->addStretch();
    cancelLayout->addWidget(cancelButton);
    cancelLayout->addStretch();
    mainLayout->addLayout(cancelLayout);

    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    populateTable();
}

void CheckoutDialog::populateTable() {
    std::vector<TrenchCoat> shopping_basket = service.getCoatsFomBasketService();
    auto* model = new BasketTableModel(shopping_basket, this);
    coatTable->setModel(model);

    coatTable->resizeColumnsToContents();
    coatTable->resizeRowsToContents();

    int totalSum = service.get_sum_service();
    totalPriceLabel->setText(QString("Total Price: %1").arg(totalSum));
}
