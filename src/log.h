#pragma once

#include <iostream>
#include <sstream>
#include <string>

#define VALUE_NAME_(x) #x
#define QuickLogHelper(x) QuickLog(__PRETTY_FUNCTION__, x)

// #define QUICK_DEBUG_LOG

#ifdef QUICK_DEBUG_LOG
#define QI_LOG(str) QuickLogHelper(str)
#define QI_LOG_VALUE(value) QuickLogValues(VALUE_NAME_(value), value)
#else
#define QI_LOG(str)
#define QI_LOG_VALUE(value)
#endif

void QuickLog(std::string header, std::string log);

template <class T>
void QuickLogValues(std::string value_name, T value) {
    std::stringstream ss;
    ss << value;
    std::string buffer = "";
    ss >> buffer;
    QI_LOG(value_name + " =  " + buffer);
    return;
}