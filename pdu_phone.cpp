#include <iostream>
#include <string>

std::string phone_2_pdu(std::string phone);

std::string phone_2_pdu(std::string phone)
{
    size_t index = phone.find('+');

    if (index != std::string::npos)
    {
        phone.erase(index, 1);
    }

    size_t l = phone.length();

    if(l / 2 != 0)
    {
        phone += 'F';
    }

    std::string pdu_phone;

    for (int i = 0; i < phone.length()-1; i = i + 2)
    {
        pdu_phone += phone[i + 1];
        pdu_phone += phone[i];
    }

    return pdu_phone;
}
