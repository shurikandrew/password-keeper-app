#include <iostream>
#include "password.h"
#pragma once
/**
 *
 * Takes all passwords, encodes them with a give algorithm,
 * defines current time, writes everything to a file
 *
 * @param password password to encode file with
 * @param route path to a file
 * @param res vector of passwords
 * @param time timestamp
 */
auto encodeFile(std::string& password, std::string const& route, std::vector<Password> res, long long& time) -> void;
/**
 *
 * Prints timestamp, decodes all the file,
 * writes its content to a vector
 *
 * @param password password to decode file with
 * @param route path to a file
 * @return vector of passwords from the file
 */
auto decodeFile(std::string& password, std::string const& route) -> std::vector<Password>;
/**
 *
 * checks if given file is empty or not
 *
 * @param route file path
 * @return boolean ( true if file is empty and false otherwise)
 */
auto checkIfEmpty(std::string const& route) -> bool;
/**
 *
 * checks if given object is folder or not
 *
 * @param route path to an object
 * @return boolean (true if file is a folder and false otherwise)
 */
auto checkIfFolder(std::string const& route) -> bool;
/**
 *
 * It takes a string, and decodes it with an algorithm
 *
 * @param password password to decode a line with
 * @param line line from the file
 * @return decoded line
 */
auto decodeLine(std::string& password, std::string line) -> std::string;
/**
 *
 * It takes a string, and encodes it with an algorithm
 *
 * @param password password to encode a line with
 * @param line line from the file
 * @return encoded line
 */
auto encodeLine(std::string& password, std::string line) -> std::string;
/**
 *
 * Checks if an object exists
 *
 * @param route path to an object
 * @return boolean (true if file exists and false otherwise)
 */
auto checkIfExist(std::string const& route) -> bool;

