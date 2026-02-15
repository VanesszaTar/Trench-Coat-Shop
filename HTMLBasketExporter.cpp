//
// Created by Vanessza Tar on 29.04.2025.
//
#include "HTMLBasketExporter.h"
#include <fstream>
#include "exceptions.h"
#include <cstdlib>
void HTMLBasketExporter::exportBasket(const std::vector<TrenchCoat>& basket, const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        throw FileException("Could not open file");
    }
    fout << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<title>Shopping basket</title>\n</head>\n<body>\n";
    fout << "<table border=\"1\">\n<tr><th>Size</th><th>Colour</th><th>Price</th><th>Photograph</th></tr>\n";
    for (const auto& coat : basket) {
        fout << "<tr><td>" << coat.getSize() << "</td><td>"
             << coat.getColour() << "</td><td>"
             << coat.getPrice() << "</td><td>"
        << "<a href=\"" << coat.getPhotograph() << "\">" << coat.getPhotograph() << "</a></td></tr>\n";
    }
    fout << "</table>\n";
    fout << "</body></html>";
    fout.close();
}

void HTMLBasketExporter::openHTMLInBrowser(const std::string& filename) const {
    std::string command = "open " + filename;
    system(command.c_str());
}