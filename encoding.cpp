#include <filesystem>
#include <vector>
#include <fstream>
#include "encoding.h"
#include "password.h"

auto encodeFile(std::string& password, std::string const& route, std::vector<Password> res, long long & time) -> void{
    auto result = std::string();
    auto file = std::fstream (route);
    time = std::chrono::system_clock::now().time_since_epoch().count()/1000000000;
    auto seconds = time%60;
    time-=seconds;
    time/=60;
    int minutes = time%60;
    time-=minutes;
    time/=60;
    int hours = time%24 + 2;

    for (int i = 0; i < res.size(); ++i) {
        result.append(encodeLine(password, res.at(i).getName()));
        result.append(encodeLine(password, res.at(i).getPassword()));
        result.append(encodeLine(password, res.at(i).getCategory()));
        result.append(encodeLine(password, res.at(i).getWebsite()));
        result.append(encodeLine(password, res.at(i).getLogin()));
    }

    file<<result<<"--";
    if(hours<10)
        file<<"0"<<hours;
    else
        file<<hours;
    if(minutes<10)
        file<<"0"<<minutes;
    else
        file<<minutes;
    if(seconds<10)
        file<<"0"<<seconds;
    else
        file<<seconds;
}
auto encodeLine(std::string& password, std::string line) -> std::string{
    auto count = 0;
    for (int i = 0; i < line.size(); i+=2) {
        line.at(i) += (int)password.at(count);
        count++;
        if(count>=password.size()){
            count = 0;
        }
    }
    if(line.size()>1){
        count = password.size()-1;
        for (int i = 1; i < line.size(); i+=2) {
            line.at(i) -= (int)password.at(count);
            count--;
            if(count<0){
                count = password.size()-1;
            }
        }
    }
    return line + "\n";
}
auto decodeFile(std::string& password, std::string const& route) -> std::vector<Password>{
    auto res = std::vector<Password>();
    auto file = std::fstream (route);
    auto str = std::string();
    std::cin.ignore();
    while(std::getline(file, str)){
        auto pass = Password();
        if(str.substr(0, 2) == "--"){
            std::cout<<"Last decoding attempt: "<<str.substr(2,2)<<" h, "<<str.substr(4, 2)<<" m, "<<str.substr(6,2)<<" s\n";
            break;
        }
        for (int i = 0; i < 5; i++) {
            switch(i){
                case 0:
                    pass.setName(decodeLine(password, str));
                    std::getline(file, str);
                    break;
                case 1:
                    pass.setPassword(decodeLine(password, str));
                    std::getline(file, str);
                    break;
                case 2:
                    pass.setCategory(decodeLine(password, str));
                    std::getline(file, str);
                    break;
                case 3:
                    pass.setWebsite(decodeLine(password, str));
                    std::getline(file, str);
                    break;
                case 4:
                    pass.setLogin(decodeLine(password, str));
                    break;
            }
        }
        res.push_back(pass);
    }
    return res;
}

auto decodeLine(std::string& password, std::string line) -> std::string{
    auto count = 0;
    for (int i = 0; i < line.size(); i+=2) {
        line.at(i) -= (int)password.at(count);
        count++;
        if(count>=password.size()){
            count = 0;
        }
    }
    if(line.size()>1){
        count = password.size()-1;
        for (int i = 1; i < line.size(); i+=2) {
            line.at(i) += (int)password.at(count);
            count--;
            if(count<0){
                count = password.size()-1;
            }
        }
    }
    return line;
}

auto checkIfFolder(std::string const& route) -> bool{
    return std::filesystem::is_directory(route);
}

auto checkIfEmpty(std::string const& route) -> bool{
    return std::filesystem::file_size(route) == 0;
}

auto checkIfExist(std::string const& route) -> bool{
    return std::filesystem::exists(route);
}