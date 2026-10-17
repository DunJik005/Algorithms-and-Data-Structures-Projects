#include "StringInput.h"

// u konstruktoru smesti argument u data i returnuje to sa readAll

StringInput::StringInput(std::string data) : data(std::move(data)) {}

std::string StringInput::readAll() {
    return data;
}