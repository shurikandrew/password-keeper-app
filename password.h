#include <iostream>
#include <string>
#pragma once
/**
 *
 * Structure to store a password.
 * It has 5 string variables, each of them stores
 * some information about given password
 *
 */
struct Password{
public:
    std::string name;
    std::string password;
    std::string category;
    std::string website;
    std::string login;
    Password();

    Password(const std::string &name, const std::string &password, const std::string &category,
             const std::string &website, const std::string &login);
    /**
     * @return password's name
     */
    const std::string &getName() const;
    /**
     * @brief set password's name
     * @param1 password's name
     */
    void setName(const std::string &name);
    /**
     * @return password
     */
    const std::string &getPassword() const;
    /**
     * @brief set password
     * @param1 password
     */
    void setPassword(const std::string &password);
    /**
     * @return password's category
     */
    const std::string &getCategory() const;
    /**
     * @brief set password's category
     * @param1 password's category
     */
    void setCategory(const std::string &category);
    /**
     * @return password's website
     */
    const std::string &getWebsite() const;
    /**
     * @brief set password's website
     * @param1 password's website
     */
    void setWebsite(const std::string &website);
    /**
     * @return password's login
     */
    const std::string &getLogin() const;
    /**
     * @brief set password's login
     * @param1 password's login
     */
    void setLogin(const std::string &login);

    friend std::ostream &operator<<(std::ostream &os, const Password &password);

    virtual ~Password();
};
