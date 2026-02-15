//
// Created by Vanessza Tar on 29.05.2025.
//
#pragma once
#include "Action.h"
#include "Service.h"

class ActionAdd : public Action {
  private:
    Repository& repo;
    TrenchCoat addedCoat;
  public:
    ActionAdd(Repository& repo, const TrenchCoat& addedCoat) : repo(repo), addedCoat(addedCoat) {};
    void execute_undo() override { repo.remove_coat_repo(addedCoat, true); };
    void execute_redo() override { repo.add_coat_repo(addedCoat, true); };
};