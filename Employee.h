//
//  Employee.hpp
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

#ifndef Employee_h
#define Employee_h

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>

class Employee{
private:
    std::string name;
    std::string country;
    std::string state;
    std::string city;
    std::string address;
    std::string phone;
    //double salary;
    int id;
    
    struct EmployeeRec {
        int id;
        char name[31];
        char address[26];
        char city[21];
        char state[21];
        char country[21];
        char phone[21];
        double salary;
    };
    
public:
    Employee();
    Employee(std::string name, std::string address, std::string phone, std::string city, std::string state, std::string country, double salary, int id);
    double salary;
    
    void display(std::ostream&) const;  // Write a readableEmployee representation to a stream
    void write(std::ostream&) const;    // Write a fixed-length record to current file position
    void store(std::iostream&) const;   // Overwrite (or append) record in (to) file
    void toXML(std::ostream&) const;  // Write XML record for Employee
 
    static Employee* read(std::istream& is ){ // Read record from current file position
        EmployeeRec employeeX;
        is.read(reinterpret_cast<char*>(&employeeX), sizeof(employeeX));
        Employee *emp = new Employee();
        if(is){
            emp->name = employeeX.name;
            emp->id = employeeX.id;
            emp->salary = employeeX.salary;
            emp->address = employeeX.address;
            emp->city = employeeX.city;
            emp->country = employeeX.country;
            emp->phone = employeeX.phone;
            emp->state = employeeX.state;
        }
        return emp;
    }
    
    static Employee* retrieve(std::istream& is ,int id_){ // Search file for record by id
        is.clear();
        is.seekg(0, is.beg);
        while (!is.eof()){
            std::unique_ptr<Employee> emp(Employee::read(is));
            if (emp->id == id_){
                return emp.release();
            }
        }
        return nullptr;
    }
    
    static Employee* fromXML(std::istream& is){ // Read the XML record from a stream
        std::string line;
        int nameC = 0;
        int idC = 0;
        int salaryC = 0;
        int addressC = 0;
        int cityC = 0;
        int stateC = 0;
        int countryC = 0;
        int phoneC = 0;

       /* I have some error where it doesn't detect if there is no opening tag or the opening tag isn't correct.
         It will create an employee but it won't do the right thing where it throws an error. I tried doing an if statement
         where if line isnt the correct opening tag then throw the error but if I do than then when the file is correct and
         there is an opening tag it will always throw that error. Which makes sense because it is pointing to the next line
         instead of the first. I tried doing the seekg(0, std::ios::beg) but that doesn't work either.
         If you could show me the correct way of doing it I would really appreciate it.
         I commented what I tried so you can see at least the effort haha.
         Thank you*/
         
        /*std::getline(is, line);
        if(line != "<Employee>"){
        //if(line != "<Employee>" && !is.eof()){
            throw std::runtime_error("Missing <Employee> tag ");
        }
        is.clear();
        is.seekg(0, std::ios::beg); ////////
        
        */
        std::getline(is, line, '<');
        std::getline(is, line, '>');
        if(line == "Employee"){
            //move to next line
            Employee* emp = new Employee();
            std::getline(is, line, '<');
            std::getline(is, line, '>');
        
            
            while(line != "/Employee"){
                //check to see if there are unvalid tags
                if(line != "name" && line != "address" && line != "city" && line != "state" && line != "country" && line != "phone" && line != "salary" && line != "id"){
                    throw std::runtime_error("NOT A VALID TAG");
                }
                else if(line == "salary"){
                    std::getline(is, line, '<');
                    emp->salary =  std::stod(line);
                    std::getline(is, line, '>');
                    //look for the next opening tag
                    if (line == "/salary"){
                        std::getline(is, line,'<');
                        std::getline(is, line, '>');
                        salaryC++;
                        //
                    }
                    else {
                        throw std::runtime_error("Missing </salary> tag");
                    }
                }
                
                else if(line == "name"){
                    std::getline(is, line, '<');
                    emp->name = line;
                    std::getline(is, line, '>');
                    //look for the next opening tag
                    if (line == "/name"){
                        std::getline(is, line,'<');
                        std::getline(is, line, '>');
                        nameC++;
                        //
                    }
                    else {
                        throw std::runtime_error("Missing </name> tag");
                    }
                }
                
                else if(line == "id"){
                    std::getline(is, line, '<');
                    emp->id =  std::stoi(line);
                    std::getline(is, line, '>');
                    //look for the next opening tag
                    if (line == "/id"){
                        std::getline(is, line,'<');
                        std::getline(is, line, '>');
                        idC++;
                        //
                    }
                    else {
                        throw std::runtime_error("Missing </id> tag");
                    }
                }
                
                else if(line == "address"){
                    std::getline(is, line, '<');
                    emp->address = line;
                    std::getline(is, line, '>');
                    //look for the next opening tag
                    if (line == "/address"){
                        std::getline(is, line,'<');
                        std::getline(is, line, '>');
                        addressC++;
                        //
                    }
                    else {
                        throw std::runtime_error("Missing </address> tag");
                    }
                }
                
                else if(line == "city"){
                    std::getline(is, line, '<');
                    emp->city = line;
                    std::getline(is, line, '>');
                    //look for the next opening tag
                    if (line == "/city"){
                        std::getline(is, line,'<');
                        std::getline(is, line, '>');
                        cityC++;
                        //
                    }
                    else {
                        throw std::runtime_error("Missing </city> tag");
                    }
                }
                
                else if(line == "state"){
                    std::getline(is, line, '<');
                    emp->state = line;
                    std::getline(is, line, '>');
                    //look for the next opening tag
                    if (line == "/state"){
                        std::getline(is, line,'<');
                        std::getline(is, line, '>');
                        stateC++;
                        //
                    }
                    else {
                        throw std::runtime_error("Missing </state> tag");
                    }
                }
                
                else if(line == "country"){
                    std::getline(is, line, '<');
                    emp->country = line;
                    std::getline(is, line, '>');
                    //look for the next opening tag
                    if (line == "/country"){
                        std::getline(is, line,'<');
                        std::getline(is, line, '>');
                        countryC++;
                        //
                    }
                    else {
                        throw std::runtime_error("Missing </country> tag");
                    }
                }
                
                else if(line == "phone"){
                    std::getline(is, line, '<');
                    emp->phone = line;
                    std::getline(is, line, '>');
                    //look for the next opening tag
                    if (line == "/phone"){
                        std::getline(is, line,'<');
                        std::getline(is, line, '>');
                        phoneC++;
                    }
                    else {
                        throw std::runtime_error("Missing </phone> tag");
                    }
                }
                
                else if(line == ""){
                    std::getline(is, line, '<');
                    //emp->phone = line;
                    std::cout << "endof line" << std::endl;

                }
                
                else{
                    throw std::runtime_error("Missing closing tag");
                }


                //KEEP TRACK OF HOW MANY TAGS THERE ARE
                
                if(nameC > 1){
                    throw std::runtime_error("More than one <name> tag");
                }
                else if(idC> 1){
                    throw std::runtime_error("More than one <id> tag");
                }
                else if(salaryC > 1){
                    throw std::runtime_error("More than one <salary> tag");
                }
                else if(addressC > 1){
                    throw std::runtime_error("More than one <address> tag");
                }
                else if(cityC > 1){
                    throw std::runtime_error("More than one <city> tag");
                }
                else if(stateC > 1){
                    throw std::runtime_error("More than one <state> tag");
                }
                else if(countryC > 1){
                    throw std::runtime_error("More than one <country> tag");
                }
                else if(phoneC > 1){
                    throw std::runtime_error("More than one <phone> tag");
                }
            }
            if(emp->isValid() == false || emp->isNameValid() == false){
                std::cout << "Possible error with name " << emp->name << std::endl;
                std::cout << "Possible error with id: " << emp->id << std::endl;
            }
            return emp;
        }
        else{
            return nullptr;
        }
    }
    
    friend std::ostream& operator<<(std::ostream&, const Employee& emp);
    
    bool isValid() const{
        return id != -1;
    };
    
    bool isNameValid() const{
        return name != "";
    };
    
    void setName(std::string);
    void setAdress(std::string);
    void setCity(std::string);
    void setState(std::string);
    void setCountry(std::string);
    void setPhone(std::string);
    void setSalary(double);
    void setID(int);

};

#endif
