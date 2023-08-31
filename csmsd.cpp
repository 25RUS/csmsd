#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "ucs2.cpp"
#include "com.cpp"
#include "pdu_phone.cpp"


void send_2_com(std::vector<std::string> atv, std::string com);
void sms(std::string msg, std::string phone, std::string port, std::string flash);


void sms(std::string msg, std::string phone, std::string port, std::string flash)
{
    std::string pdu_phone = phone_2_pdu(phone);
    std::string text2 = convertToUCS2LE(msg);
    text2.erase(std::remove(text2.begin(), text2.end(), '-'), text2.end());

    int textlong = text2.length();
    std::stringstream ss;
    ss << std::hex << textlong;
    std::string textlongHEX = ss.str();
    
    int l = 26 + textlong;
    int l1 = l / 2;

    std::string MSG = "0001000B91" + pdu_phone + "00" + flash + "8" + textlongHEX + text2  + char(26) + "\r\n";
    std::string argument_3 = "AT+CMGS=" + std::to_string(l1) + "\r\n";

    std::vector<std::string> at_cmds = {"AT\r\n", "AT+CMGF=0\r\n", argument_3, MSG};
    write(at_cmds, port);
}


int main(int argc, char* argv[])
{
    std::string port = argv[1]; // /dev/ttyUSBx || COMx
    std::string phone = argv[2]; //+79991234566
    std::string flash = argv[3]; //0 - SMS || 1 - flash
    std::stringstream mss;

    for (int i = 4; i < argc; ++i)
    {
        mss << argv[i];
        if(i < argc)
        {
            mss << " ";
        }
    }

    std::string text = mss.str();

    sms(text, phone, port, flash);
    return 0;
}
