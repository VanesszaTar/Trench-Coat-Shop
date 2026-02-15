//
// Created by Vanessza Tar on 25.03.2025.
//
#pragma once
#include "Repository.h"
#include "Action.h"
#include "ActionAdd.h"
#include "ActionRemove.h"
#include "ActionUpdate.h"
#include <stack>
class Service {
private:
    Repository* repository;
    std::stack<std::unique_ptr<Action>> undo_stack;
    std::stack<std::unique_ptr<Action>> redo_stack;

public:
    Service(Repository* repo);
    void add_coat_service(const TrenchCoat& coat);
    void remove_coat_service(const TrenchCoat& coat);
    void update_coat_service(const TrenchCoat& coat, const std::string& new_size, const std::string& new_colour, int new_price, int new_quantity, const std::string& new_photograph);
    //void add10coats_service();
    void add_to_basket_service(const TrenchCoat& coat);
    int get_sum_service() const;
    std::vector<TrenchCoat> getAllCoatsService() const;
    std::vector<TrenchCoat> getCoatsBySizeService(const std::string& size) const;
    std::vector<TrenchCoat> getCoatsFomBasketService() const;

    void exportBasketToFileService(BasketExporter* exporter, const std::string& filename) const;

    void saveToFileService() const;
    void loadFromFileService();

    void undo();
    void redo();

    bool undoStackEmpty() const;
    bool redoStackEmpty() const;
};

