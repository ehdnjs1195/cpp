#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/json/src.hpp> 
#include <iostream>
#include <string>

class JsonParser{
public:
    JsonParser();
    ~JsonParser();
private:
    boost::property_tree::ptree _pt, plan, level, phase;
};