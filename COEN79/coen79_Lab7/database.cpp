// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    
    database::database(const database &src) {//copy constructor
        Debug("Copy constructor..." << std::endl);
        company_array = new company[src.aloc_slots];
        company* temp1 = src.company_array;
        company* temp2 = company_array;
        for(int i = 0; i < src.used_slots; i++){
            company_array[i] = src.company_array[i];
        }
        aloc_slots = src.aloc_slots;
        used_slots = src.used_slots;
    }
    
    
    database& database::operator= (const database &rhs) {//overload assignment operator
        Debug("Assignment operator..." << std::endl);
        if (this == &rhs){
            return *this;
        }
        if(aloc_slots != rhs.aloc_slots){
            reserve(rhs.aloc_slots);
        }
        used_slots = rhs.used_slots;
        for(int i = 0; i < used_slots; i++){
            company_array[i] = rhs.company_array[i];
        }
        return *this;
    }
    
    
    database::~database() {//destructor
        delete[] company_array;
        aloc_slots = 0;
        used_slots = 0;
    }
    
    
    void database::reserve(size_type new_capacity) {//increase memory space to new_capacity (only if necessary)
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        
        company* temp = new company[new_capacity];
        std::copy(company_array, company_array + used_slots, temp);
        delete[] company_array;
        company_array = temp;
        aloc_slots = new_capacity;
        return;
    }
    
    
    bool database::insert_company(const std::string &entry) {//insert a new company into the end of the array
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }
        if(used_slots == aloc_slots){
            reserve(used_slots + 1);
        }
        company temp(entry);
        company_array[used_slots] = temp;
        used_slots++;
        return true;
    }
    
    
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {//insert a product under a company indicated by parameter
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);
        size_type mark = -1;
        if(search_company(company) != COMPANY_NOT_FOUND){
            mark = search_company(company);
            company_array[mark].insert(product_name, price);
            return true;
        }
        return false;
    }
    
    
    bool database::erase_company(const std::string &company) {//erase a company indicated by the string parameter
        
        size_type company_index = search_company(company);
        for(int i = company_index; i < used_slots; i++){
            company_array[i] = company_array[i + 1];
        }
        used_slots--;
        return true;
    }
    
    
    bool database::erase_item(const std::string& cName, const std::string& pName) {//erase an item of a company, cName, indicated by pName
        
        assert(cName.length() > 0 && pName.length() > 0);
        size_type num = search_company(cName);
        if(num == COMPANY_NOT_FOUND){
            return false;
        }
        node* temp = list_search(company_array[num].get_head(), pName);
        if(temp == NULL){
            return false;
        }
        node* tempprev = company_array[num].get_head();
        while (tempprev->getLink() != temp){
            tempprev = tempprev->getLink();
        }
        tempprev->setLink(temp->getLink());
        delete temp;
        return true;
    }
    
    
    
    database::size_type database::search_company(const std::string& company) {//search for a company whose name is provided by parameter
        assert(company.length() > 0);
        for(int i = 0; i < used_slots; i++){
            if (company_array[i].get_name() == company){
                return i;
            }
        }
        return COMPANY_NOT_FOUND;
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
