//
// Created by Vanessza Tar on 11.05.2025.
//

#include "validators.h"
#include <vector>

void TrenchCoatValidator::validate(const TrenchCoat& coat) {
  std::string errors;
  std::vector<std::string> validSizes = {"XXS", "XS", "S", "M", "L", "XL", "XXL"};
  if (coat.getSize().empty())
    errors+="Size must not be empty!\n";

  bool valid = false;
  for (const auto& size : validSizes) {
    if (coat.getSize() == size)
      valid = true;
  }
  if (!valid)
    errors+="Invalid size! It must be one of: XXS | XS | S | M | L | XL | XXL\n";

  if (coat.getColour().empty())
    errors+="Colour must not be empty!\n";
  if (coat.getPrice() <= 0)
    errors+="Price must be greater than zero!\n";
  if (coat.getQuantity() < 0)
    errors+="Quantity must be positive!\n";
  if (coat.getPhotograph().empty())
    errors+="Photograph link must not be empty!\n";

  if (!errors.empty())
    throw ValidationException(errors);
}

void TrenchCoatValidator::validate_size(const TrenchCoat& coat) {
  std::string errors;
  std::vector<std::string> validSizes = {"XXS", "XS", "S", "M", "L", "XL", "XXL"};
  if (coat.getSize().empty())
    errors+="Size must not be empty!\n";

  bool valid = false;
  for (const auto& size : validSizes) {
    if (coat.getSize() == size)
      valid = true;
  }
  if (!valid)
    errors+="Invalid size! It must be one of: XXS | XS | S | M | L | XL | XXL\n";
 if (!errors.empty())
   throw ValidationException(errors);
}

void TrenchCoatValidator::validate_colour(const TrenchCoat& coat) {
  std::string errors;
  if (coat.getColour().empty())
    errors+="Colour must not be empty!\n";
  if (!errors.empty())
    throw ValidationException(errors);
}

void TrenchCoatValidator::validate_price(const TrenchCoat& coat) {
  std::string errors;
  if (coat.getPrice() <= 0)
    errors+="Price must be greater than zero!\n";
  if (!errors.empty())
    throw ValidationException(errors);
}

void TrenchCoatValidator::validate_quantity(const TrenchCoat& coat) {
  std::string errors;
  if (coat.getQuantity() < 0)
    errors+="Quantity must be positive!\n";
  if (!errors.empty())
    throw ValidationException(errors);
}

void TrenchCoatValidator::validate_photograph(const TrenchCoat& coat) {
  std::string errors;
  if (coat.getPhotograph().empty())
    errors+="Photograph link must not be empty!\n";
  if (!errors.empty())
    throw ValidationException(errors);
}