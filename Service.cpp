//
// Created by Vanessza Tar on 25.03.2025.
//
#include "Service.h"

//Specification: This is the Service constructor
Service::Service(Repository* repo) {
    this->repository = repo;
}

//Specification: Adds a new trench coat to the database if possible, based on the exceptions thrown in the function "add_coat_repo".
void Service::add_coat_service(const TrenchCoat& coat) {
    repository->add_coat_repo(coat, false);
    std::unique_ptr<Action>coat_ptr = std::make_unique<ActionAdd>(*repository, coat);
    undo_stack.push(std::move(coat_ptr));
}


//Specification: Removes a sold trench coat from the database if possible, based on the exceptions thrown in the function "remove_coat_repo".
void Service::remove_coat_service(const TrenchCoat& coat) {
    repository->remove_coat_repo(coat, false);
    std::unique_ptr<Action>coat_ptr = std::make_unique<ActionRemove>(*repository, coat);
    undo_stack.push(std::move(coat_ptr));

}

//Specification: Updates a trench coat in the database if possible, based on the exceptions thrown in the function "update_coat_repo".
void Service::update_coat_service(const TrenchCoat& coat, const std::string& new_size, const std::string& new_colour, int new_price, int new_quantity, const std::string& new_photograph) {
    TrenchCoat newCoat(new_size, new_colour, new_price, new_quantity, new_photograph);
    TrenchCoat oldCoat = coat;
    repository->update_coat_repo(coat, new_size, new_colour, new_price, new_quantity, new_photograph, false);
    std::unique_ptr<Action>coat_ptr = std::make_unique<ActionUpdate>(*repository, oldCoat, newCoat);
    undo_stack.push(std::move(coat_ptr));
}
/*
//Specification: Adds 10 trench coats to the database, using the function "add10coats_repo" from repo.
void Service::add10coats_service() {
    repository->add10coats_repo();}
*/
//Specification: returns all existing coats
std::vector<TrenchCoat> Service::getAllCoatsService() const{
    return repository->getAllCoatsRepo();}

//Specification: returns all coats with a given size
std::vector<TrenchCoat> Service::getCoatsBySizeService(const std::string& size) const {
    return repository->getCoatsBySizeRepo(size);}

//Specification: adds a coat into the shopping basket
void Service::add_to_basket_service(const TrenchCoat& coat) {
    repository->added_to_basket(coat);}

//Specification: returns the price that needs to be paid after checkout
int Service::get_sum_service() const {
    return repository->sum_in_basket();}

//Specification: returns all coats that were put into the shopping basket
std::vector<TrenchCoat> Service::getCoatsFomBasketService() const {
    return repository->getAllCoatsFromBasketRepo();}

void Service::loadFromFileService() {
    repository->loadFromFile();
}

void Service::saveToFileService() const {
    repository->saveToFile();
}

void Service::exportBasketToFileService(BasketExporter *exporter, const std::string &filename) const {
    repository->exportBasketToFileRepo(exporter, filename);
}

void Service::undo() {
    if (undo_stack.empty()) {
        throw ValidationException("No more actions to undo!\n");
    }
    std::unique_ptr<Action> action = std::move(undo_stack.top());
    undo_stack.pop();
    try {
        action->execute_undo();
        redo_stack.push(std::move(action));
    } catch (const std::exception& e) {
        undo_stack.push(std::move(action));
        throw;
    }
}

void Service::redo() {
    if (redo_stack.empty()) {
        throw ValidationException("No more actions to redo!\n");
    }
    std::unique_ptr<Action> action = std::move(redo_stack.top());
    redo_stack.pop();
    try {
        action->execute_redo();
        undo_stack.push(std::move(action));
    } catch (const std::exception& e) {
        redo_stack.push(std::move(action));
        throw;
    }
}

bool Service::undoStackEmpty() const {
    return undo_stack.empty();
}

bool Service::redoStackEmpty() const {
    return redo_stack.empty();
}