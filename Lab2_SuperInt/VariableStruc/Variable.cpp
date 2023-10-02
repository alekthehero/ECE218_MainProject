#include "Variable.h"

variable::variable()
{
    name_ = "";
    value_ = NULL;
}

variable::variable(const std::string& name, const SuperInt value)
{
    this->name_ = name;
    this->value_ = value;
}

void variable::set_name(const std::string& new_name)
{
    this->name_ = new_name;
}

void variable::set_value(const SuperInt new_value)
{
    this->value_ = new_value;
}
