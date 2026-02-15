//
// Created by Vanessza Tar on 26.03.2025.
//
#include <iostream>
#include "UI.h"

#include "exceptions.h"

void displayAdministratorMenu(){
    std::cout << "\nAdministrator Menu\n";
    std::cout << "1. Add a new trench coat.\n";
    std::cout << "2. Remove an existing trench coat.\n";
    std::cout << "3. Update an existing trench coat.\n";
    std::cout << "4. View all trench coats.\n";
    std::cout << "5. Exit.\n";
}

void displayUserMenu() {
    std::cout << "\nUser Menu\n";
    std::cout << "1. View the trench coats with a chosen size.\n";
    std::cout << "2. Go shopping.\n";
    std::cout << "3. See shopping basket and total price.\n";
    std::cout << "4. Save shopping basket to file.\n";
    std::cout << "5. View the saved shopping basket info.\n";
    std::cout << "6. Exit.\n";
}

void mainMenu(Service& service) {
    int choice;

    while (true) {
        std::cout << "\nWelcome to the Proper Trench Coats' Application!\n";
        std::cout << "1. Administrator Mode.\n";
        std::cout << "2. User Mode.\n";
        std::cout << "3. Exit.\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            int administratorsChoice;
            while (true){
                displayAdministratorMenu();
                std::cout << "Enter your choice as an administrator: ";
                std::cin >> administratorsChoice;

                if (administratorsChoice == 1){
                    std::string size, colour, photograph;
                    int price, quantity;
                    std::cout << "Enter the size (e.g., XXS | XS | S | M | L | XL | XXL): ";
                    std::cin >> size;
                    std::cout << "Enter the colour: ";
                    std::cin.ignore();
                    std::getline(std::cin, colour);
                    std::cout << "Enter the price: ";
                    std::cin >> price;
                    std::cout << "Enter the quantity: ";
                    std::cin >> quantity;
                    std::cout << "Enter the photograph's link: ";
                    std::cin.ignore();
                    std::getline(std::cin, photograph);
                    TrenchCoat newTrenchCoat(size, colour, price, quantity, photograph);
                    try {
                        service.add_coat_service(newTrenchCoat);
                        std::cout << "New trench coat added successfully!" << std::endl;
                    }catch (const RepositoryException& e) {
                        std::cout<<e.what()<<std::endl;
                    } catch (const ValidationException& e) {
                        std::cout<<e.what()<<std::endl;
                    } catch (const std::exception& e) {
                        std::cout<<e.what()<<std::endl;
                    }
                }
                else if (administratorsChoice == 2){
                    int price;
                    std::string photograph;
                    std::cout << "Enter the price of the trench coat you want to remove: ";
                    std::cin >> price;
                    std::cin.ignore();
                    std::cout << "Enter the photograph link of the trench coat you want to remove: ";
                    std::getline(std::cin, photograph);
                    TrenchCoat coatToRemove("", "", price, 0, photograph);
                    try {
                        service.remove_coat_service(coatToRemove);
                        std::cout << "Trench coat removed successfully!" << std::endl;
                    }catch (const RepositoryException& e) {
                        std::cout<<e.what()<<std::endl;
                    } catch (const ValidationException& e) {
                        std::cout<<e.what()<<std::endl;
                    } catch (const std::exception& e) {
                        std::cout<<e.what()<<std::endl;
                    }
                }
                else if (administratorsChoice == 3){
                    int old_price;
                    std::string old_photograph;
                    std::cout << "Enter the price of the trench coat you want to update: ";
                    std::cin >> old_price;
                    std::cin.ignore();
                    std::cout << "Enter the photograph link of the trench coat you want to update: ";
                    std::getline(std::cin, old_photograph);
                    TrenchCoat coatToUpdate("", "", old_price, 0, old_photograph);
                    std::string newSize, newColour, newPhotograph;
                    int newPrice, newQuantity;
                    std::cout << "Enter the new size (XXS | XS | S | M | L | XL | XXL): ";
                    std::cin >> newSize;
                    std::cout << "Enter the new colour: ";
                    std::cin.ignore();
                    std::getline(std::cin, newColour);
                    std::cout << "Enter the new price: ";
                    std::cin >> newPrice;
                    std::cout << "Enter the new quantity: ";
                    std::cin >> newQuantity;
                    std::cin.ignore();
                    std::cout << "Enter the new photograph link: ";
                    std::getline(std::cin, newPhotograph);
                    try {
                        service.update_coat_service(coatToUpdate, newSize, newColour, newPrice, newQuantity, newPhotograph);
                        std::cout << "Trench coat updated successfully!" << std::endl;
                    }catch (const RepositoryException& e) {
                        std::cout<<e.what()<<std::endl;
                    } catch (const ValidationException& e) {
                        std::cout<<e.what()<<std::endl;
                    } catch (const std::exception& e) {
                        std::cout<<e.what()<<std::endl;
                    }
                }
                else if (administratorsChoice == 4){
                    std::cout << "All coats: \n";
                    std::vector<TrenchCoat> coats = service.getAllCoatsService();
                    for (const auto& coat : coats) {
                        std::cout << coat.toString() << std::endl;
                    }
                }
                else if (administratorsChoice == 5){
                    std::cout << "Exiting administrator mode...\n";
                    break;
                }
                else{
                    std::cout << "Invalid choice! Please choose a number between 1 and 5!\n";
                }
            }
        }
        else if (choice == 2) {
            int usersChoice;
            while (true) {
                displayUserMenu();
                std::cout << "Enter your choice as an user: ";
                std::cin >> usersChoice;
                if (usersChoice == 1) {
                    try {
                        std::string size;
                        std::cout << "Enter the size of the trench coats you want to view: ";
                        std::cin.ignore();
                        std::getline(std::cin, size);
                        std::vector<TrenchCoat> filtered = service.getCoatsBySizeService(size);
                        if (size == "")
                            std::cout << "All coats available: \n";
                        else {
                            std::cout << "Coats having the size " << size << ":\n";
                        }
                        int i = 0;
                        while (i < filtered.size()) {
                            TrenchCoat currentCoat = filtered[i];
                            std::cout << currentCoat.toString() << std::endl;
                            std::string command;
                            std::cout << "Open photograph? (yes/no): ";
                            std::getline(std::cin, command);
                            if (command == "yes") {
                                system(("open " + currentCoat.getPhotograph()).c_str());
                            }
                            std::cout << "----------------------------------------------------------------------\n";
                            std::cout << "Press enter to see the next trench coat, or type anything else to exit.\n";
                            std::string userInput;
                            std::getline(std::cin, userInput);
                            if (!userInput.empty()) {
                                break;
                            }
                            i++;
                        }
                    } catch (const RepositoryException& e) {
                        std::cout<<e.what()<<std::endl;
                    } catch (const ValidationException& e) {
                        std::cout<<e.what()<<std::endl;
                    } catch (const std::exception& e) {
                        std::cout<<e.what()<<std::endl;
                    }
                }
                else if (usersChoice == 2) {
                    try{
                        std::string size;
                        std::cout << "Enter the size of the trench coats you want to view: ";
                        std::cin.ignore();
                        std::getline(std::cin, size);
                        std::vector<TrenchCoat> filtered = service.getCoatsBySizeService(size);
                        int coatCount = filtered.size();
                        if (size == "")
                            std::cout << "All coats available: \n";
                        else {
                            std::cout << "Coats having the size " << size << ":\n";
                        }
                        int i = 0;
                        bool browsing = true;
                        int sum = service.get_sum_service();

                        while (browsing) {
                            TrenchCoat currentCoat = filtered[i];
                            std::cout << currentCoat.toStringUser() << std::endl;

                            std::string command;
                            std::cout << "Open photograph? (yes/no): ";
                            std::getline(std::cin, command);
                            if (command == "yes") {
                                system(("open " + currentCoat.getPhotograph()).c_str());
                            }

                            std::cout << "----------------------------------------------------------------------\n";
                            std::cout << "Buy coat? (yes/next/exit): ";
                            std::getline(std::cin, command);

                            if (command == "yes") {
                                try {
                                    service.add_to_basket_service(currentCoat);
                                    sum = service.get_sum_service();
                                    std::cout << "The selected trench coat was successfully added to the shopping basket!\n";
                                    std::cout << "The total price is: " << sum << std::endl;
                                } catch (std::exception& e) {
                                    std::cout << e.what() << std::endl;
                                }
                                i = (i + 1) % coatCount;
                            } else if (command == "next") {
                                i = (i + 1) % coatCount;
                                continue;
                            } else if (command == "exit") {
                                std::cout << "Exiting browsing.\n";
                                browsing = false;
                                continue;
                            } else {
                                std::cout << "Invalid command. Please enter 'yes', 'next', or 'exit'.\n";
                                continue;
                            }
                            if (command != "next") {
                                std::cout << "Press enter to see the next trench coat, or type anything else to exit.\n";
                                std::string userInput;
                                std::getline(std::cin, userInput);
                                if (!userInput.empty()) {
                                    browsing = false;
                                }
                            }
                        }
                    } catch (const RepositoryException& e) {
                        std::cout << e.what() << std::endl;
                    } catch (const ValidationException& e) {
                        std::cout << e.what() << std::endl;
                    } catch (const std::exception& e) {
                        std::cout << e.what() << std::endl;
                    }
                }
                else if (usersChoice == 3) {
                    std::cout << "After the shopping spree, your basket contains: ";
                    std::vector<TrenchCoat> shopping_basket = service.getCoatsFomBasketService();
                    if (shopping_basket.empty()) {
                        std::cout << "-\n";
                    }
                    else {
                        std::cout << std::endl;
                        for (const auto& coat : shopping_basket) {
                            std::cout << coat.toStringUser() << std::endl;
                        }
                    }
                    int sum = service.get_sum_service();
                    std::cout << "The total price from the basket is: " << sum << std::endl;
                }
                else if (usersChoice == 4) {
                    try {
                        std::string format;
                        std::cout << "Choose file format (csv/html): ";
                        std::cin >> format;

                        if (format == "csv") {
                            CSVBasketExporter* exporter = new CSVBasketExporter();
                            service.exportBasketToFileService(exporter,"ShoppingBasket.csv");
                            exporter->openCSVInExcel("ShoppingBasket.csv");
                            delete exporter;
                        } else if (format == "html") {
                            HTMLBasketExporter* exporter = new HTMLBasketExporter();
                            service.exportBasketToFileService(exporter, "basket.html");
                            exporter->openHTMLInBrowser("basket.html");
                            delete exporter;
                        } else {
                            std::cout << "Invalid format. Please enter either 'csv' or 'html'.\n";
                            continue;
                        }
                    } catch (const FileException& e) {
                        std::cout << e.what() << std::endl;
                    } catch (const std::exception& e) {
                        std::cout << e.what() << std::endl;
                    }
                }
                else if (usersChoice == 5) {
                    try {
                        std::string filename;
                        std::cout << "Choose a filename: ";
                        std::cin >> filename;

                        std::ifstream fin(filename);
                        if (!fin.good()) {
                            std::cout << "The file \"" << filename << "\" does not exist!\n";
                            continue;
                        }
                        fin.close();

                        if (filename.find(".csv") != std::string::npos) {
                            CSVBasketExporter csvExporter;
                            service.exportBasketToFileService(&csvExporter, filename);
                            csvExporter.openCSVInExcel(filename);
                        }
                        else if (filename.find(".html") != std::string::npos) {
                            HTMLBasketExporter htmlExporter;
                            service.exportBasketToFileService(&htmlExporter, filename);
                            htmlExporter.openHTMLInBrowser(filename);
                        }
                        else {
                            std::cout << "Invalid filename. Please enter a .csv or .html file.\n";
                            continue;
                        }
                    } catch (const std::runtime_error& e) {
                        std::cout << e.what() << std::endl;
                    }
                }
                else if (usersChoice == 6) {
                    std::cout << "Exiting user mode...\n";
                    break;
                }
                else {
                    std::cout << "Invalid choice! Please choose a number between 1 and 6.\n";
                }
            }
        }
        else if (choice == 3){
            std::cout << "Exiting the program...\n";
            break;
        }
        else{
            std::cout << "Invalid choice! Please choose option 1, 2 or 3!\n";
        }
    }
}