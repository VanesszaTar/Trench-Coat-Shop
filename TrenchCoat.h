//
// Created by Vanessza Tar on 25.03.2025.
//
#pragma once
#include <string>

class TrenchCoat {
private:
    std::string size;
    std::string colour;
    int price;
    int quantity;
    std::string photograph;

public:
    TrenchCoat(const std::string& size,
               const std::string& colour,
               int price,
               int quantity,
               const std::string& photograph);

    TrenchCoat();

    std::string getSize() const;
    std::string getColour() const;
    int getPrice() const;
    int getQuantity() const;
    std::string getPhotograph() const;
    std::string toString() const;
    std::string toStringUser() const;

    void setSize(const std::string& new_size);
    void setColour(const std::string& new_colour);
    void setPrice(int new_price);
    void setQuantity(int new_quantity);
    void setPhotograph(const std::string& new_photograph);

    friend std::ostream& operator<<(std::ostream& out, const TrenchCoat& coat);
    friend std::istream& operator>>(std::istream& in, TrenchCoat& coat);
};