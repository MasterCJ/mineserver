#ifndef _CONFIG_H
#define _CONFIG_H

#include <vector>

class Conf
{
  private:
    Conf() {};
    std::map<std::string, std::string> confSet;
  public:
    bool load(std::string configFile);
    int iValue(std::string name);
    std::string sValue(std::string name);
    std::vector<int> vValue(std::string name);
    static Conf &get();
};

#endif
