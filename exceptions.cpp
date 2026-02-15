//
// Created by Vanessza Tar on 29.04.2025.
//
#include "exceptions.h"

RepositoryException::RepositoryException(const std::string& message)
    : std::runtime_error(message) {}

ValidationException::ValidationException(const std::string& message)
    : std::runtime_error(message) {}

FileException::FileException(const std::string& message)
    : std::runtime_error(message) {}
