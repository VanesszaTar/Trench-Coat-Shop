//
// Created by Vanessza Tar on 29.05.2025.
//
#pragma once
class Action{
  public:
    Action() {};
    virtual ~Action() {};
    virtual void execute_undo() = 0;
    virtual void execute_redo() = 0;
};