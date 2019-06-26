//
//  main.cpp
//  xml
//
//  Created by Mariana on 2/15/19.
//  Copyright © 2019 Mariana. All rights reserved.

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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

#include "Employee.h"

using namespace std;

int main(int argc, const char * argv[]) {

    ifstream is;
    is.open(argv[1]);
    
    vector<unique_ptr<Employee>>v;
   
    //open files
    if(is.good()){
        while(!is.eof()){
        Employee *p = Employee::fromXML(is);
        if(p != nullptr){
            v.push_back(unique_ptr<Employee>(p)); //push data from files to data
            }
        }
    }
    else{
        cout << "Failed open file" << endl;
        return 0;
    }
    
    
    is.close();
   
    for(int i=0; i<v.size(); i++){
        v.at(i) -> display(cout);
       
    }
    std::fstream employeeFile;
    employeeFile.open("employee.bin", std::fstream::in | std::fstream::out | std::ios::binary| std::ios::trunc);
    
    for (int i=0; i<v.size(); i++){ //(auto i = v.begin(); i != (v.end()-1);
        v.at(i)->write(employeeFile); //i->get()
    }
    v.clear();
    
   employeeFile.seekg(0, employeeFile.beg);
    
    while(!employeeFile.eof() && employeeFile.peek() != EOF){
        Employee *p = Employee::read(employeeFile);
            if(p -> isNameValid()){
                v.push_back(unique_ptr<Employee>(p));
            }
    }

    for (int i = 0; i < v.size(); i++){ //loop through your vector and print to coutan XML representation of each Employee using Employee::toXML.
        v.at(i)->toXML(std::cout);
    }
    
    std::unique_ptr<Employee>x(Employee::retrieve(employeeFile, 12345)); //Search the file for the Employee with id 12345 using Employee::retrieve.
    std::cout << "Found:" << std::endl;
    x->display(std::cout);
    x->setSalary(150000);//Change the salary for the retrieved object to 150000.00
    x ->  Employee::store(employeeFile); //Write the modified Employee object back to file using Employee::store
    std::cout << x->salary << std::endl;
    std::unique_ptr<Employee>(Employee::retrieve(employeeFile, 12345));//Retrieve the object again by id (12345) and print its salary to verify that the file now has the updated salary.
    
    
    std::unique_ptr<Employee> newEmployee(new Employee);//Create a new Employee object of your own with a new, unique id, along with other information.
    newEmployee->setName("Mariana Acosta");
    newEmployee->setID(10720013);
    newEmployee->setSalary(700);
    newEmployee->setAdress("1073 N 100 W");
    newEmployee->setCity("Orem");
    newEmployee->setState("Utah");
    newEmployee->setCountry("USA");
    newEmployee->setPhone("801-836-1049");
    
    newEmployee -> Employee::store(employeeFile);//Store it in the file using Employee::store
    std::unique_ptr<Employee>myemp(Employee::retrieve(employeeFile, 10720013));
    
    //Retrieve the record with Employee::retrieve and display it to cout.
    myemp->display(std::cout);
    

    return 0;
}
