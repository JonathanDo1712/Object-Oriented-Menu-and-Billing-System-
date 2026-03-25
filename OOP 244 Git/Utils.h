/***********************************************************************
// OOP244 Project, Utils Module
//
// File	Utils.h
// Version 0.1
// Date 2024-9-11
// started by Fardad 
// Description
// utility function to be used in the project
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SENECA_UTILS_H
#define SENECA_UTILS_H
#include <iostream>

namespace seneca {
   class Utils {
   public:
       char* alocpy(const char* src)const;
       char* alocpy(char*& des, const char* src)const;
       char* strcpy(char* des, const char* src)const;
       char* strcpy(char* des, const char* src, int len)const;
       char* strncpy(char* des, const char* src, int len)const;

       char* makeBillFileName(char* des, size_t billNo)const;

       int strlen(const char* str)const;
       bool isspace(char ch)const;
       bool isspace(const char* cstring)const;

       char* read(char*& toRet, std::istream& istr, char delimiter = '\n')const;


      //self made
      int getInt();
      int getInt(int min, int max);

   };
   extern Utils ut;   // makes the ut object available where Utils.h is included
                     // to call a Utils function call it as follows
                     // ut.strcpy(des, src);
}

#endif // !SENECA_UTILS_H
