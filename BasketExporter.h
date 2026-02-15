//
// Created by Vanessza Tar on 29.04.2025.
//
#pragma once
#include "TrenchCoat.h"
#include <vector>
#include <string>

class BasketExporter {
public:
    virtual void exportBasket(const std::vector<TrenchCoat>& basket, const std::string& filename) const = 0;
    virtual ~BasketExporter() = default;
};