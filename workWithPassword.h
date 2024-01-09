#include <iostream>
#include <string>
#include <vector>
#include "password.h"
#pragma once
/**
 *
 * Sorts a vector of passwords by two parameter(Name and Category)
 *
 * @param a first password
 * @param b second password
 * @return boolean variable for std::sort() parameter
 */
auto compare(Password const& a, Password const& b) -> bool;
/**
 *
 * Checks if the passwords is weak and prints one of the possible reasons
 *
 * @param str password (that is stored in a Password struct)
 * @param res vector of passwords itself
 * @return if the password is weak
 */
auto isPasswordWeak(std::string const& str, std::vector<Password> res) -> bool;
/**
 * Creates a random password with given parameters
 *
 * @param input number of symbols in password
 * @param isUpper can it contain uppercase chars
 * @param isSpecial can it contain special chars
 * @return generated password
 */
auto createNewPassword(int const& input,bool const& isUpper,bool const& isSpecial) -> std::string;
/**
 *
 * Inputs a password, based on user's choices and prints information on the screen
 *
 * @param res vector of passwords
 * @param pass password where we will insert this info
 */
auto inputPassword(std::vector<Password> const& res, Password& pass) -> void;
/**
 *
 * Inputs a category, based on user's choices and prints information on the screen
 *
 * @param res vector of passwords
 * @param pass password where we will insert this info
 */
auto inputCategory(Password& pass, std::vector<std::string> categories) -> void;
/**
 *
 * Inputs a website, based on user's choices and prints information on the screen
 *
 * @param res vector of passwords
 * @param pass password where we will insert this info
 */
auto inputWebsite(Password& pass) -> void;
/**
 *
 * Inputs a login, based on user's choices and prints information on the screen
 *
 * @param res vector of passwords
 * @param pass password where we will insert this info
 */
auto inputLogin(Password& pass) -> void;