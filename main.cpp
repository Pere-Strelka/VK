#include <iostream>
#include "src/api.h"

using namespace std;


string fa2_callback(){
    string res;
    cout << "Enter 2fa code: ";
    cin >> res;
    return res;
}

string captcha_callback(const string &captcha_sid){
    string res;
    cout << "Open image https://api.vk.com/captcha.php?sid=" << captcha_sid;\
    cout << " and enter text: " << endl;
    cin >> res;
    return res;
}

int main(int argc, char *argv[])
{
    if(argc < 2 || argc > 4){
        cout << "[access_token] login pass" << endl;
        return 1;
    }

    string access_token, login, pass;

    if(argc == 2){
        access_token = argv[1];
    }
    else if(argc == 3){
        login = argv[1];
        pass = argv[2];
    }
    else if(argc == 4){
        access_token = argv[1];
        login = argv[2];
        pass = argv[3];
    }


    VK::Client api;
    api.set_fa2_callback(fa2_callback);
    api.set_cap_callback(captcha_callback);
    if(api.auth(login, pass, access_token)){
        cout << "Auth ok" << endl;
        cout << "Access token: " << api.access_token() << endl;
        api.call("wall.post", "owner_id=-123123123&message=Hello from API");
    }
    else{
        cout << "Auth fail: " << api.last_error() << endl;
    }

    return 0;
}
