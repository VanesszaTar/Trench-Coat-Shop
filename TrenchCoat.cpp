//
// Created by Vanessza Tar on 25.03.2025.
//
#include "TrenchCoat.h"
#include <iostream>
#include <sstream>
#include <string>
//Specification: This is the TrenchCoat constructor.
TrenchCoat::TrenchCoat(const std::string& size, const std::string& colour, int price, int quantity, const std::string& photograph){
    this->size = size;
    this->colour = colour;
    this->price = price;
    this->quantity = quantity;
    this->photograph = photograph;}

//Specification: This is the TrenchCoat default constructor.
TrenchCoat::TrenchCoat(){
    this->size = "";
    this->colour = "";
    this->price = 0;
    this->quantity = 0;
    this->photograph = "";}

//Specification: Returns the size of the trench coat.
std::string TrenchCoat::getSize() const{
    return this->size;}

//Specification: Returns the colour of the trench coat.
std::string TrenchCoat::getColour() const{
    return this->colour;}

//Specification: Returns the price of the trench coat.
int TrenchCoat::getPrice() const{
    return this->price;}

//Specification: Returns the quantity of the trench coat.
int TrenchCoat::getQuantity() const{
    return this->quantity;}

//Specification: Returns the photograph of the trench coat.
std::string TrenchCoat::getPhotograph() const{
    return this->photograph;}

//Specification: It sets the current size of the trench coat to a new one.
void TrenchCoat::setSize(const std::string &new_size) {
    this->size = new_size;}

//Specification: It sets the current colour of the trench coat to a new one.
void TrenchCoat::setColour(const std::string &new_colour) {
    this->colour = new_colour;}

//Specification: It sets the current price of the trench coat to a new one.
void TrenchCoat::setPrice(int new_price) {
    this->price = new_price;}

//Specification: It sets the current quantity of the trench coat to a new one.
void TrenchCoat::setQuantity(int new_quantity) {
    this->quantity = new_quantity;}

//Specification: It sets the current photograph of the trench coat to a new one.
void TrenchCoat::setPhotograph(const std::string &new_photograph) {
    this->photograph = new_photograph;}

//Specification: returns each coat in a specific string format for admin
std::string TrenchCoat::toString() const {
    return "size: " + this->size + " colour: " + this->colour + " price: " + std::to_string(this->price) + " quantity: " + std::to_string(this->quantity) + " photograph: " + this->photograph;}

//Specification: returns each coat in a specific string format for user
std::string TrenchCoat::toStringUser() const {
    return "size: " + this->size + " colour: " + this->colour + " price: " + std::to_string(this->price) + " photograph: " + this->photograph;}

std::ostream& operator<<(std::ostream& out, const TrenchCoat& coat) {
    out << coat.size << '\n'
        << coat.colour << '\n'
        << coat.price << '\n'
        << coat.quantity << '\n'
        << coat.photograph << '\n';
    return out;
}

std::istream& operator>>(std::istream& in, TrenchCoat& coat) {
    std::getline(in, coat.size);
    std::getline(in, coat.colour);
    in >> coat.price;
    in.ignore();
    in >> coat.quantity;
    in.ignore();
    std::getline(in, coat.photograph);
    return in;
}


