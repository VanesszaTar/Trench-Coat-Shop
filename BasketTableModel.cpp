//
// Created by Vanessza Tar on 30.05.2025.
//
#include "BasketTableModel.h"

BasketTableModel::BasketTableModel(const std::vector<TrenchCoat> &coats, QObject *parent) : QAbstractTableModel(parent), coats(coats) {};
int BasketTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return coats.size();
}
int BasketTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 5;
}
QVariant BasketTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const TrenchCoat& coat = coats.at(index.row());

    switch (index.column()) {
        case 0: return QString::fromStdString(coat.getSize());
        case 1: return QString::fromStdString(coat.getColour());
        case 2: return QString::number(coat.getPrice());
        case 3: return QString::number(coat.getQuantity());
        case 4: return QString::fromStdString(coat.getPhotograph());
        default: return QVariant();
    }
}

QVariant BasketTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return QString("Size");
            case 1: return QString("Colour");
            case 2: return QString("Price");
            case 3: return QString("Quantity");
            case 4: return QString("Photograph");
            default: return QVariant();
        }
    }
    return QVariant();
}
void BasketTableModel::setCoats(const std::vector<TrenchCoat>& newCoats) {
    beginResetModel();
    coats = newCoats;
    endResetModel();
}
