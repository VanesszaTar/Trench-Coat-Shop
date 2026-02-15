//
// Created by Vanessza Tar on 29.05.2025.
//
#pragma once
#include "Action.h"
#include "Repository.h"

class ActionRemove : public Action {
  private:
    Repository& repo;
    TrenchCoat removedCoat;
  public:
    ActionRemove(Repository& repo, const TrenchCoat& removedCoat) : repo(repo), removedCoat(removedCoat) {};
    void execute_undo() override { repo.add_coat_repo(removedCoat, true); };
    void execute_redo() override { repo.remove_coat_repo(removedCoat, true); };
};
