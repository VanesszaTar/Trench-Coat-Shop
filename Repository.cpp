//
// Created by Vanessza Tar on 25.03.2025.
//
#include "Repository.h"
#include <functional>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "validators.h"
//Specification: This is the Repository constructor.
Repository::Repository(const std::string& file): filename(file) {
    loadFromFile();
}

//Specification: Checks whether a coat is unique or not
int Repository::check_uniqueness(const TrenchCoat &coat) const {
    auto it = std::find_if(coats.begin(), coats.end(), [&coat](const TrenchCoat& current_coat) {
         return coat.getPrice() == current_coat.getPrice() && coat.getPhotograph() == current_coat.getPhotograph();
     });
    if (it != coats.end()) {
        return std::distance(coats.begin(), it);
    }
    return -1;
}

//Specification: Adds a new trench coat in the database only if it does not already exist. (unique price&photograph link)
void Repository::add_coat_repo(const TrenchCoat& coat, bool overrideCheck) {
    int existentIndex = check_uniqueness(coat);
    if (existentIndex != -1)
        throw RepositoryException("Error: The coat already exists in the database!");
    if (!overrideCheck)
        TrenchCoatValidator::validate(coat);
    coats.push_back(coat);
    saveToFile();
}

//Specification: Removes a trench coat from the database only if it exists and its quantity is equal to 0 (out of stock)
void Repository::remove_coat_repo(const TrenchCoat& coat, bool overrideCheck) {
    TrenchCoatValidator::validate_price(coat);
    TrenchCoatValidator::validate_photograph(coat);
    int existentIndex = check_uniqueness(coat);
    if (existentIndex == -1)
        throw RepositoryException("Error: The coat you are trying to remove does not exist in the database!");
    const TrenchCoat &repoCoat = coats[existentIndex];
    if (!overrideCheck && repoCoat.getQuantity() != 0)
        throw RepositoryException("Error: The coat you are trying to remove is not out of stock yet!");
    coats.erase(coats.begin() + existentIndex);
    saveToFile();
}

//Specification: Updates a trench coat from the database only if it exists and the provided price and photograph link are unique.
void Repository::update_coat_repo(const TrenchCoat& coat, const std::string& new_size, const std::string& new_colour, int new_price, int new_quantity, const std::string& new_photograph, bool overrideCheck) {
    TrenchCoatValidator::validate_price(coat);
    TrenchCoatValidator::validate_photograph(coat);
    int existentIndex = check_uniqueness(coat);
    if (existentIndex == -1)
        throw RepositoryException ("Error: The coat you are trying to update does not exist in the database!");
    TrenchCoat duplicate(new_size, new_colour, new_price, new_quantity, new_photograph);
    if (!overrideCheck) {
        TrenchCoat newCoat(new_size, new_colour, new_price, new_quantity, new_photograph);
        TrenchCoatValidator::validate(newCoat);
        int duplicateIndex = check_uniqueness(duplicate);
        if (duplicateIndex != -1 && duplicateIndex != existentIndex)
            throw RepositoryException("Error: A coat with the same price and photograph that you are trying to update already exists in the database!");
    }
    coats[existentIndex] = duplicate;
    saveToFile();
}
/*
//Specification: Adds 10 trench coats to the database.
void Repository::add10coats_repo() {
    coats.emplace_back("S", "Blue", 50, 10, "https://www.williamjacket.com/wp-content/uploads/2024/11/Leo-Stehr-Baby-Blue-Double-Breasted-Trench-Coat.webp");
    coats.emplace_back("M", "Red", 60, 15, "https://i.pinimg.com/736x/9e/b4/5f/9eb45face7e004db7adf91a574583829.jpg");
    coats.emplace_back("L", "Green", 70, 20, "https://alicebeckerinc.com/cdn/shop/files/80ee67bbfa70f35c8c40ea43208a0ec3e0c41d0874c6bb9d10271b4a3ad410eb.jpg?v=1706208571&width=1445");
    coats.emplace_back("S", "Black", 80, 5, "https://d1flfk77wl2xk4.cloudfront.net/Assets/41/820/XXL_p0201782041.jpg");
    coats.emplace_back("M", "Yellow", 90, 12, "https://m.media-amazon.com/images/I/71A5mW4XBhL._AC_SX425_.jpg");
    coats.emplace_back("L", "White", 100, 8, "https://cdn.dsmcdn.com/mnresize/600/-/ty1022/product/media/images/prod/SPM/PIM/20231024/18/df69624b-a129-3636-b3a8-787bb38c9e3b/1_org_zoom.jpg");
    coats.emplace_back("XL", "Gray", 110, 10, "https://colourfulrebel.com/cdn/shop/files/colourful-rebel-kaia-branded-trenchcoat-grey-8720867054030-104141_1080x.jpg?v=1742566051");
    coats.emplace_back("XXL", "Brown", 120, 25, "https://img4.dhresource.com/webp/m/0x0/f3/albu/jc/g/25/515e08ee-c99f-404f-aa20-b81d2698bd1f.png");
    coats.emplace_back("S", "Pink", 130, 5, "https://laviedupapillon.com/wp-content/uploads/2018/09/balenciaga-tweed-shoes-683x1024.jpg");
    coats.emplace_back("M", "Purple", 140, 7, "https://i.pinimg.com/474x/fa/d7/09/fad70902f8030ffe87b6eacb44f0c1f8.jpg");
    saveToFile();
}*/

//Specification: gets all coats
std::vector<TrenchCoat>Repository::getAllCoatsRepo() const{
    return this->coats;}


//Specification: gets all coats with a given size
std::vector<TrenchCoat> Repository::getCoatsBySizeRepo(const std::string& size) const {
    if (size.empty())
        return coats;
    TrenchCoat prototype = TrenchCoat(size, "", 0, 0, "");;
    if (!size.empty()){
        TrenchCoatValidator::validate_size(prototype);
    }
    std::vector<TrenchCoat> filteredCoats;
    std::copy_if(coats.begin(), coats.end(), std::back_inserter(filteredCoats),[&size](const TrenchCoat& current_coat) {
        return current_coat.getSize() == size;
    });
    return filteredCoats;
}

//Specification: adds a coat into the shopping basket
void Repository::added_to_basket(const TrenchCoat& coat){
    if (coat.getQuantity() == 0)
        throw RepositoryException("Error: The trench coat you want to add to the shopping basket is out of stock!");
    shopping_basket.push_back(coat);
    int index = existent_coat_repo(coat);
    if (index != -1) {
        coats[index].setQuantity(coats[index].getQuantity() - 1);
    }
    saveToFile();
}

//Specification: returns the sum that needs to be paid after checkout
int Repository::sum_in_basket() const {
    int sum = 0;
    for (const auto& current_item : shopping_basket) {
        sum += current_item.getPrice();
    }
    return sum;
}

//Specification: checks whether a given coat is identical with another one
int Repository::existent_coat_repo(const TrenchCoat &coat) const {
    int index = 0;
    for (const auto& current_item: coats) {
        if (current_item.getPrice() == coat.getPrice() &&
            current_item.getQuantity() == coat.getQuantity() &&
            current_item.getSize() == coat.getSize() &&
            current_item.getColour() == coat.getColour() &&
            current_item.getPhotograph() == coat.getPhotograph()) {
            return index;
            }
        index++;
    }
    return -1;}

//Specification: gets all coats that were added into the shopping basket
std::vector<TrenchCoat> Repository::getAllCoatsFromBasketRepo() const{
    return shopping_basket;
}

void Repository::loadFromFile() {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        throw FileException("Error opening file.");
    }
    coats.clear();
    TrenchCoat coat;

    while (fin >> coat) {
        coats.push_back(coat);
    }
    fin.close();
    std::cout << "File loading finished." << std::endl;
}


void Repository::saveToFile() const{
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        throw FileException("Error opening file for writing.");
    }
    for (const auto& coat : coats) {
        fout << coat;
    }
    fout.close();
}

void Repository::exportBasketToFileRepo(BasketExporter* exporter, const std::string& filename) const {
    exporter->exportBasket(shopping_basket, filename);
}
