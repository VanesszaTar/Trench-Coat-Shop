//
// Created by Vanessza Tar on 29.05.2025.
//
#pragma once
#include "Action.h"
#include "Repository.h"
class ActionUpdate : public Action {
  private:
    Repository& repo;
    TrenchCoat newCoat;
    TrenchCoat oldCoat;

  public:
  ActionUpdate(Repository& repo, const TrenchCoat& oldCoat, const TrenchCoat& newCoat)
  : repo(repo), oldCoat(oldCoat), newCoat(newCoat) {}

  void execute_undo() override {
    repo.update_coat_repo(newCoat, oldCoat.getSize(), oldCoat.getColour(), oldCoat.getPrice(), oldCoat.getQuantity(), oldCoat.getPhotograph(), true);
  }

  void execute_redo() override {
    repo.update_coat_repo(oldCoat, newCoat.getSize(), newCoat.getColour(), newCoat.getPrice(), newCoat.getQuantity(), newCoat.getPhotograph(),true);
  }
};