#include "workWithPassword.h"
#include "password.h"

auto compare(Password const& a, Password const& b) -> bool{
    if(a.getName() != b.getName())
        return a.getName() > b.getName();

    if(a.getCategory() != b.getCategory())
        return a.getCategory() > b.getCategory();

    return true;
}

auto isPasswordWeak(std::string const& str, std::vector<Password> res) -> bool{
    if(str.size()<8){
        std::cout<<"Password seems to be too short.\n";
        return true;
    }

    for (int i = 0; i < res.size(); i++) {
        if(res.at(i).getPassword() == str){
            std::cout<<"You have already used this password.\n";
            return true;
        }
    }
    auto isOk = false;
    for (int i = 0; i < str.size(); i++) {
        if(isupper(str.at(i))){
            isOk = true;
        }
    }
    if(!isOk){
        std::cout<<"Your password does not contain uppercase characters\n";
        return true;
    }

    return false;
}

auto createNewPassword(int const& input,bool const& isUpper,bool const& isSpecial) -> std::string{
    auto res = std::string();
    auto str = std::string();
    for (int i = 0; i < input; i++) {
        if(isSpecial){
            if(isUpper){
                str = (char)(33 + std::rand()%94);
            }
            else{
                auto inter = 1 + std::rand()%64;
                if(inter <= 32){
                    str = (char)(32 + inter);
                }
                else if(inter>32){
                    str = (char)(inter + 90 - 32);
                }
            }
        }
        else{
            str = (char)(97 + std::rand()%26);
        }
        res.append(str);
    }
    return res;
}

auto inputPassword(std::vector<Password> const& res, Password& pass) -> void{
    auto password = std::string();
    auto flagInput = false;
    auto strInput = std::string();
    auto input = int();
    std::cout<<"Input password:\n";
    std::cin>>password;
    if(isPasswordWeak(password, res))
    {
        std::cout<<"Do you want to use automatically generated password?[y/n]\n";
        flagInput = false;
        while(!flagInput){
            std::cin>>strInput;
            if(strInput == "y" || strInput == "yes" || strInput == "Y" || strInput == "Yes")
            {
                std::cout<<"Input number of characters:\n";
                std::cin>>input;
                auto isUpper = false;
                auto isSpecial = false;
                std::cout<<"Do you want to include uppercase and lowercase letters?[y/n]\n";
                flagInput = false;
                while(!flagInput){
                    std::cin>>strInput;
                    if(strInput == "y" || strInput == "yes" || strInput == "Y" || strInput == "Yes")
                    {
                        isUpper = true;
                        flagInput = true;
                    }
                    else if(strInput == "n" || strInput == "no" || strInput == "N" || strInput == "No"){
                        isUpper = false;
                        flagInput = true;
                    }
                    else{
                        std::cout<<"Incorrect input!\n"
                                   "Try again!\n";
                    }
                }

                std::cout<<"Do you want to include special characters?[y/n]\n";
                flagInput = false;
                while(!flagInput){
                    std::cin>>strInput;
                    if(strInput == "y" || strInput == "yes" || strInput == "Y" || strInput == "Yes")
                    {
                        isSpecial= true;
                        flagInput = true;
                    }
                    else if(strInput == "n" || strInput == "no" || strInput == "N" || strInput == "No"){
                        isSpecial = false;
                        flagInput = true;
                    }
                    else{
                        std::cout<<"Incorrect input!\n"
                                   "Try again!\n";
                    }
                }
                pass.setPassword(createNewPassword(input, isUpper, isSpecial));
                flagInput = true;
            }
            else if(strInput == "n" || strInput == "no" || strInput == "N" || strInput == "No"){
                std::cout<<"Your password will be written.\n";
                pass.setPassword(password);
                flagInput = true;
            }
            else{
                std::cout<<"Incorrect input!\n"
                           "Try again!\n";
            }
        }
    }
}

auto inputCategory(Password& pass, std::vector<std::string> categories) -> void{
    std::cout<<"Choose category:\n";
    auto flagInput = false;
    auto input = 0;
    for (int i = 0; i < categories.size(); ++i) {
        std::cout<<i+1<<". "<<categories.at(i)<<"\n";
    }
    flagInput = false;
    while(!flagInput){
        std::cin>>input;
        if(input>=1 && input<=categories.size())
            flagInput = true;
        else{
            std::cout<<"Incorrect input!\n"
                       "Try again!\n";
        }
    }
    pass.setCategory(categories.at(input-1));

}

auto inputWebsite(Password& pass) -> void{
    std::cout<<"Do you want to add a website?[y/n]\n";
    auto flagInput = false;
    auto strInput = std::string();
    auto website = std::string();
    while(!flagInput){
        std::cin>>strInput;
        if(strInput == "y" || strInput == "yes" || strInput == "Y" || strInput == "Yes")
        {
            std::cout<<"Input website:\n";
            std::cin>>website;
            pass.setWebsite(website);
            flagInput = true;
        }
        else if(strInput == "n" || strInput == "no" || strInput == "N" || strInput == "No"){
            pass.setWebsite("");
            flagInput = true;
        }
        else{
            std::cout<<"Incorrect input!\n"
                       "Try again!\n";
        }
    }
}

auto inputLogin(Password& pass) -> void{
    std::cout<<"Do you want to add a login?[y/n]\n";
    auto flagInput = false;
    auto login = std::string();
    auto strInput = std::string();
    auto website = std::string();
    while(!flagInput){
        std::cin>>strInput;
        if(strInput == "y" || strInput == "yes" || strInput == "Y" || strInput == "Yes")
        {
            std::cout<<"Input login:\n";
            std::cin>>login;
            pass.setLogin(login);
            flagInput = true;
        }
        else if(strInput == "n" || strInput == "no" || strInput == "N" || strInput == "No"){
            pass.setLogin("");
            flagInput = true;
        }
        else{
            std::cout<<"Incorrect input!\n"
                       "Try again!\n";
        }
    }
}