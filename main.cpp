#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include "encoding.h"
#include "password.h"
#include "workWithPassword.h"

auto main() -> int{
    std::string password;
    int input;
    auto categories = std::vector<std::string>();
    long long time;
    categories.push_back("Work");
    categories.push_back("Study");
    std::cout<<"Please, input path to the file or a folder:\n";
    std::string path;
    bool flagInput = false;
    while(!flagInput){
        std::cin>>path;
        if(checkIfFolder(path)){
            std::vector<std::string> str;
            for (const auto & entry : std::filesystem::directory_iterator(path)){
                str.push_back(entry.path());
            }
            if(!str.empty()){
                std::cout<<"Choose a file:\n";
                for (int i = 0; i < str.size(); ++i) {
                    std::cout << i+1 << ". " << str.at(i)<< std::endl;
                }
                int pathInput;
                while(!flagInput){
                    std::cin>>pathInput;
                    if(pathInput<0 || pathInput>str.size()){
                        std::cout<<"Incorrect input!\n";
                    }
                    else{
                        path = str.at(pathInput-1);
                        flagInput = true;
                    }
                }
            }
            else{
                std::cout<<"Sorry, this folder is empty\n"
                           "Please, try again! \n";
            }
        }
        else if(!checkIfFolder(path)){
            if(!checkIfExist(path)){
                std::cout<<"Sorry, there is no such file :(\n"
                           "Please, try again! \n";
            }
            else  if(checkIfExist(path)){
                flagInput = true;
            }
        }
        else{
            std::cout<<"Incorrect input\n"
                       "Please, try again!\n";
        }
    }
    std::string strInput;
    bool createPassword;
    auto categoryFlag = false;
    if(checkIfEmpty(path)){
        std::cout<<"Hmm, this file seems to be empty. Do you want to create a password for it? [y/n]\n";
        bool flag = false;
        while(!flag){
            std::cin>>strInput;
            if(strInput == "y" || strInput == "yes" || strInput == "Y" || strInput == "Yes"){
                flag = true;
                createPassword = true;
            }
            else if(strInput == "n" || strInput == "no" || strInput == "N" || strInput == "No"){
                flag = true;
                createPassword = false;
            }
            else{
                std::cout<<"Incorrect input!\nPlease, try again.\n";
            }
        }
    }
    auto res = std::vector<Password>();
    if(createPassword){
        std::cout<<"Input new password for this file:\n";
        std::cin>>password;
    }
    else{
        std::cout<<"Input your password:\n";
        std::cin>>password;
        res = decodeFile(password, path);
    }
    auto work = true;
    while(work){
        std::cout<<"What do you want to do? :\n"
                   "(1) - Search passwords\n"
                   "(2) - Sort passwords\n"
                   "(3) - Add password\n"
                   "(4) - Edit password\n"
                   "(5) - Delete password(s)\n"
                   "(6) - Add category\n"
                   "(7) - Delete category\n"
                   "(8) - Exit\n";
        std::cin>>input;
        switch(input){
            case 1 :{
                std::cout<<"Input search parameters:\n";
                std::cin>>strInput;
                auto arr = std::vector<Password>();
                auto isCount = false;
                for (int i = 0; i < res.size(); i++) {
                    isCount = false;
                    if(std::search(res.at(i).getName().begin(), res.at(i).getName().end(), strInput.begin(), strInput.end()) != res.at(i).getName().end())
                        isCount = true;
                    if(std::search(res.at(i).getPassword().begin(), res.at(i).getPassword().end(), strInput.begin(), strInput.end()) != res.at(i).getPassword().end())
                        isCount = true;
                    if(std::search(res.at(i).getCategory().begin(), res.at(i).getCategory().end(), strInput.begin(), strInput.end()) != res.at(i).getCategory().end())
                        isCount = true;
                    if(std::search(res.at(i).getWebsite().begin(), res.at(i).getWebsite().end(), strInput.begin(), strInput.end()) != res.at(i).getWebsite().end())
                        isCount = true;
                    if(std::search(res.at(i).getLogin().begin(), res.at(i).getLogin().end(), strInput.begin(), strInput.end()) != res.at(i).getLogin().end())
                        isCount = true;

                    if(isCount)
                        arr.push_back(res.at(i));
                }
                std::cout<<"Result:\n";
                for (int i = 0; i < arr.size(); ++i) {
                    std::cout<<i+1<<":\n";
                    std::cout<<arr.at(i)<<std::endl<<std::endl;
                }
                break;
            }
            case 2 :{
                std::cout<<"Sorted:\n";
                std::sort(res.begin(), res.end(), compare);
                for (int i = 0; i < res.size(); ++i) {
                    std::cout<<i+1<<": \n";
                    std::cout<<res.at(i)<<std::endl<<std::endl;
                }
                break;
            }
            case 3 :{
                auto pass = Password();
                std::cout<<"Input name:\n";
                std::cin>>strInput;
                pass.setName(strInput);

                inputPassword(res, pass);

                inputCategory(pass, categories);

                inputWebsite(pass);

                inputLogin(pass);

                res.push_back(pass);
                break;
            }
            case 4 :{
                std::cout<<"Input the number of a password that you want to edit:\n";
                for (int i = 0; i < res.size(); ++i) {
                    std::cout<<i+1<<":\n";
                    std::cout<<res.at(i)<<std::endl<<std::endl;
                }

                flagInput = false;
                while(!flagInput){
                    std::cin>>input;
                    if(input>res.size() || input<=0)
                    {
                        std::cout<<"There is no such password!\n"
                                   "Try again!\n";
                    }
                    else{
                        flagInput = true;
                    }
                }
                std::cout<<"What part do you want to edit?\n"
                           "1.Name\n"
                           "2.Password\n"
                           "3.Category\n"
                           "4.Website\n"
                           "5.Login\n";
                auto num = int();
                flagInput = false;
                while(!flagInput){
                    std::cin>>num;
                    if(num>5 || num<=0)
                    {
                        std::cout<<"Incorrect input!\n"
                                   "Try again!\n";
                    }
                    else{
                        flagInput = true;
                    }
                }
                switch(num){
                    case 1:{
                        std::cout<<"Input name:\n";
                        std::cin>>strInput;
                        res.at(input-1).setName(strInput);
                        break;
                    }
                    case 2:{
                        inputPassword(res, res.at(input-1));
                        break;
                    }
                    case 3:{
                        inputCategory(res.at(input-1), categories);
                        break;
                    }
                    case 4:{
                        inputWebsite(res.at(input-1));
                        break;
                    }
                    case 5:{
                        inputLogin(res.at(input-1));
                        break;
                    }
                }
                break;
            }
            case 5 :{
                std::cout<<"Input numbers of all passwords you want to delete:(When finished type \'0\')\n";
                for (int i = 0; i < res.size(); ++i) {
                    std::cout<<i+1<<":\n";
                    std::cout<<res.at(i)<<std::endl;
                }
                std::cin>>input;
                auto toDelete = std::vector<int>();
                while(input!=0){
                    if(input<0 || input>res.size()){
                        std::cout<<"There is no such password!\n";
                    }
                    else{
                        toDelete.push_back(input);
                    }
                    std::cin>>input;
                }
                std::cout<<"Are you sure you want to delete "<<toDelete.size()<<" password(s)?[y/n]\n";
                flagInput = false;
                while(!flagInput){
                    std::cin>>strInput;
                    if(strInput == "y" || strInput == "yes" || strInput == "Y" || strInput == "Yes")
                    {
                        for (int i = 0; i < toDelete.size(); i++) {
                            res.erase(res.begin() + toDelete.at(i)-1);
                        }
                        flagInput = true;
                    }
                    else if(strInput == "n" || strInput == "no" || strInput == "N" || strInput == "No"){
                        flagInput = true;
                    }
                    else{
                        std::cout<<"Incorrect input!\n"
                                   "Try again!\n";
                    }
                }
                break;
            }
            case 6 :{
                std::cout<<"Input new category:\n";
                auto category = std::string();
                std::cin>>category;
                categoryFlag = true;
                for (int i = 0; i < categories.size(); ++i) {
                    if(category == categories.at(i)){
                        std::cout<<"This category already exists!\n";
                        categoryFlag = false;
                    }
                }
                if(categoryFlag){
                    categories.push_back(category);
                }
                break;
            }
            case 7 :{
                std::cout<<"Select category you want to delete:\n";
                for (int i = 0; i < categories.size(); ++i) {
                    std::cout<<i+1<<". "<<categories.at(i)<<std::endl;
                }
                flagInput = false;
                while(!flagInput){
                    std::cin>>input;
                    if(input<=0 || input>categories.size())
                    {
                        std::cout<<"Incorrect input!\n"
                                   "Try again!\n";
                    }
                    else{
                        std::cout<<"Are you sure you want to delete this category?[y/n]\n";
                        flagInput = false;
                        while(!flagInput){
                            std::cin>>strInput;
                            if(strInput == "y" || strInput == "yes" || strInput == "Y" || strInput == "Yes")
                            {
                                for (int i = 0; i < res.size(); ++i) {
                                    if(res.at(i).getCategory() == categories.at(input-1)){
                                        res.erase(res.begin() + i);
                                    }
                                }
                                categories.erase(categories.begin()+input-1);
                                flagInput = true;
                            }
                            else if(strInput == "n" || strInput == "no" || strInput == "N" || strInput == "No"){
                                flagInput = true;
                            }
                            else{
                                std::cout<<"Incorrect input!\n"
                                           "Try again!\n";
                            }
                        }
                    }
                }
                break;
            }
            case 8:{
                work = false;
                break;
            }
        }
    }
    encodeFile(password, path, res, time);
}
