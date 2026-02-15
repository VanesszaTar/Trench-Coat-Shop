//
// Created by Vanessza Tar on 30.05.2025.
//
#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "TrenchCoat.h"

class BasketTableModel : public QAbstractTableModel {
  Q_OBJECT

  private:
    std::vector<TrenchCoat> coats;

  public:
    explicit BasketTableModel(const std::vector<TrenchCoat> &coats, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setCoats(const std::vector<TrenchCoat>& newCoats);
};
