//
// Created by Vanessza Tar on 29.04.2025.
//
#pragma once
#include "TrenchCoat.h"
#include "exceptions.h"

class TrenchCoatValidator {
public:
    static void validate(const TrenchCoat& coat);
    static void validate_size(const TrenchCoat& coat);
    static void validate_colour(const TrenchCoat& coat);
    static void validate_price (const TrenchCoat& coat);
    static void validate_quantity(const TrenchCoat& coat);
    static void validate_photograph(const TrenchCoat& coat);
};