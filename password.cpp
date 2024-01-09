#include "password.h"


Password::Password(const std::string &name, const std::string &password, const std::string &category,
                   const std::string &website, const std::string &login){
    Password::name = name;
    Password::password = password;
    Password::category = category;
    Password::website = website;
    Password::login = login;
}

const std::string &Password::getName() const {
    return name;
}

void Password::setName(const std::string &name) {
    Password::name = name;
}

const std::string &Password::getPassword() const {
    return password;
}

void Password::setPassword(const std::string &password) {
    Password::password = password;
}

const std::string &Password::getCategory() const {
    return category;
}

void Password::setCategory(const std::string &category) {
    Password::category = category;
}

const std::string &Password::getWebsite() const {
    return website;
}

void Password::setWebsite(const std::string &website) {
    Password::website = website;
}

const std::string &Password::getLogin() const {
    return login;
}

void Password::setLogin(const std::string &login) {
    Password::login = login;
}

Password::~Password() {
    name = "";
    password = "";
    category = "";
    website = "";
    login = "";
}

Password::Password() {

}

std::ostream &operator<<(std::ostream &os, const Password &password) {
    os << "Name: " << password.name << "\nPassword: " << password.password << "\nCategory: " << password.category
       << "\nWebsite: " << password.website << "\nLogin: " << password.login;
    return os;
}
