//
//  Employee.cpp
//  xml2
//
//  Created by Mariana on 2/15/19.
//  Copyright © 2019 Mariana. All rights reserved.
//

// Project:  XML Parser
// Name: Mariana Acosta
// Submitted: 02/21/19
// I declare that the following source code was written by me, or provided
// by the instructor for this project. I understand that copying source
// code from any other source, providing source code to another student,
// or leaving my code on a public web site constitutes cheating.
// I acknowledge that  If I am found in violation of this policy this may result
// in a zero grade, a permanent record on file and possibly immediate failure of the class.
/* Reflection:
 This project was honestly a pain. I should've started way before than I did. I thought it wasn't going to be this hard
 It wasn't hard to understand the logic but it was hard to implement it in the correct form. I had a bunch of little errors
 I did fix most of them but I still think this project needs a little bit more work for it to be perfect.
 I did learn a ton, this project was complex but I think overall I learned a ton of things that will help in the future.
 */
#include "Employee.h"
#include <iostream>
#include <limits>

using namespace std;

Employee::Employee(){
    id = -1;
    salary = 0.0;
}

std::ostream& operator<<(std::ostream& os, const Employee& emp){
    return os << "Name: "<< emp.name << std::endl << std::endl << "Address: " << emp.address << std::endl << "City: " << emp.city << std::endl << "State: " << emp.state << std::endl << "Country: " << emp.country << std::endl << "Phone: " << emp.phone  << "ID: " << emp.id << std::endl << "Salary: " <<emp.salary << std::endl;
}

void Employee::setName(std::string name_){
    name = name_;
}

void Employee::setAdress(std::string address_){
    address = address_;
}
void Employee::setCity(std::string city_){
    city = city_;
}
void Employee::setState(std::string state_){
    state = state_;
}
void Employee::setCountry(std::string country_){
    country = country_;
}
void Employee::setPhone(std::string phone_){
    phone = phone_;
}
void Employee::setSalary(double salary_){
    salary = salary_;
}
void Employee::setID(int id_){
    id = id_;
}

void Employee::display(std::ostream& os) const{ // Write a readable Employee representation to a stream
    
    os << "\nName: " << this->name << "\n";
    os << "ID: " << this->id << "\n";
    os << "Salary: " << this->salary << "\n";
    os << "Address: "<< this->address << "\n";
    os << "City: " << this->city << "\n";
    os <<"State: " << this->state << "\n";
    os << "Country: " << this->country << "\n";
    os << "Phone: "<< this->phone << "\n";
    
}

void Employee::write(std::ostream& os) const{ // Write a fixed-length record to current file position
    EmployeeRec tempEmp;
    tempEmp.id = id;
    tempEmp.salary = salary;
    strncpy(tempEmp.name, name.c_str(), 30)[30] = '\0';
    strncpy(tempEmp.address, address.c_str(), 25)[25] = '\0' ;
    strncpy(tempEmp.city, city.c_str(), 20)[20] = '\0';
    strncpy(tempEmp.state, state.c_str(), 20)[20] = '\0';
    strncpy(tempEmp.country, country.c_str (), 20)[20] = '\0' ;
    strncpy(tempEmp.phone, phone.c_str (), 20)[20] = '\0' ;
    os.write(reinterpret_cast<const char*>(&tempEmp), sizeof tempEmp);
}

void Employee::store(std::iostream& is) const{  // Overwrite (or append) record in (to) file
    EmployeeRec tempEmp;
    tempEmp.id = id;
    tempEmp.salary = salary;
    strncpy(tempEmp.name, name.c_str(), 30)[30] = '\0';
    strncpy(tempEmp.address, address.c_str(), 25)[25] = '\0' ;
    strncpy(tempEmp.city, city.c_str(), 20)[20] = '\0';
    strncpy(tempEmp.state, state.c_str(), 20)[20] = '\0';
    strncpy(tempEmp.country, country.c_str (), 20)[20] = '\0' ;
    strncpy(tempEmp.phone, phone.c_str (), 20)[20] = '\0' ;
    is.write(reinterpret_cast<const char*>(&tempEmp), sizeof tempEmp);
}

void Employee::toXML(std::ostream& os) const{ //// Write XML record for Employee
    os << std::endl;
    os << "<Employee>" << std::endl;
    os << "<name>" << name << "</name>" << std::endl;
    os << "<address>" << address<< "</address>" << std::endl;
    os << "<city>" << city << "</city>" << std::endl;
    os << "<state>" << state << "</state>" << std::endl;
    os << "<country>" << country << "</country>" << std::endl;
    os << "<phone>" << phone << "</phone>" << std::endl;
    os << "<salary>" << salary << "</salary>" << std::endl;
    os << "<id>" << id << "</id>" << std::endl;
    os << "</Employee>" << std::endl;
    os << std::endl;
    
}

