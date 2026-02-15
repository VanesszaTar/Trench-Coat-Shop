//
// Created by Vanessza Tar on 29.04.2025.
//
#pragma once
#include "BasketExporter.h"
class HTMLBasketExporter : public BasketExporter {
public:
    void exportBasket(const std::vector<TrenchCoat>& basket, const std::string& filename) const override;
    void openHTMLInBrowser(const std::string& filename) const;
};