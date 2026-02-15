//
// Created by Vanessza Tar on 11.05.2025.
//

#pragma once
#include <fstream>
#include <vector>
#include "TrenchCoat.h"
#include "exceptions.h"
#include "validators.h"
#include "BasketExporter.h"
#include "CSVBasketExporter.h"
#include "HTMLBasketExporter.h"
class Repository {
private:
    std::vector<TrenchCoat> coats;
    std::vector<TrenchCoat> shopping_basket;
    std::string filename;

public:
    Repository(const std::string& file);
    //void add10coats_repo();
    void add_coat_repo(const TrenchCoat& coat, bool overrideCheck);
    void added_to_basket(const TrenchCoat& coat);
    int sum_in_basket() const;
    int check_uniqueness(const TrenchCoat& coat) const;
    std::vector<TrenchCoat> getAllCoatsFromBasketRepo() const;
    std::vector<TrenchCoat> getAllCoatsRepo() const;
    std::vector<TrenchCoat> getCoatsBySizeRepo(const std::string& size) const;
    void remove_coat_repo(const TrenchCoat& coat, bool overrideCheck);
    int existent_coat_repo(const TrenchCoat& coat) const;
    void update_coat_repo(const TrenchCoat& coat, const std::string& new_size, const std::string& new_colour, int new_price, int new_quantity, const std::string& new_photograph, bool overrideCheck);

    void exportBasketToFileRepo(BasketExporter* exporter, const std::string& filename) const;

    void saveToFile() const;
    void loadFromFile();
};
