//
// Created by Vanessza Tar on 29.04.2025.
//
#pragma once
#include <stdexcept>
#include <string>

class RepositoryException : public std::runtime_error {
public:
    explicit RepositoryException(const std::string& message);
};

class ValidationException : public std::runtime_error {
public:
    explicit ValidationException(const std::string& message);
};

class FileException : public std::runtime_error {
public:
    explicit FileException(const std::string& message);
};