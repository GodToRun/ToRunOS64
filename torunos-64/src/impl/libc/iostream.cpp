#include "stdio.h"
#include "iostream"
using namespace std;
int atoi(const char* str);

iostream &iostream::operator<<(char value)
    {
        printf("%c",value);
        return (*this);
    }
    iostream &iostream::operator<<(int value)
    {
        printf("%d",value);
        return (*this);
    }
    iostream &iostream::operator<<(const void *value)
    {
        printf("%x",value);
        return (*this);
    }
    iostream &iostream::operator<<(const char *value)
    {
        printf("%s",value);
        return (*this);
    }

    iostream &iostream::operator>>(char &value)
    {
        char strbuf[15];
        gets(strbuf);
        value = strbuf[0];
        return (*this);
    }
    iostream &iostream::operator>>(int &value)
    {
        char strbuf[30];
        gets(strbuf);
        value = atoi(strbuf);
        return (*this);
    }
    iostream &iostream::operator>>(char *value)
    {
        gets(value);
        return (*this);
    }

    iostream std::cout;
    iostream std::cin;
    const char std::endl = '\n';