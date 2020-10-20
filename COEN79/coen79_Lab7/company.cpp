// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const std::string& company_name) {//constructor with string parameter
        assert(company_name.length() > 0);
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const company &src) {//copy constructor
        Debug("Company copy constructor..." << std::endl);
        this->company_name = src.company_name;
        list_copy(src.head_ptr, head_ptr, tail_ptr);
    }

    
    company& company::operator= (const company &src) {//overload assignment operator
        Debug("Company assignemnt operator..." << std::endl);
        list_clear(head_ptr);
        list_copy(src.head_ptr, head_ptr, tail_ptr);
        company_name = src.company_name;
        return *this;
    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    
    bool company::insert(const std::string& product_name, const float& price) {//insert a porduct(node) to the back of the list, return true if successul, return false if failed
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            head_ptr = new node(product_name, price);
            tail_ptr = head_ptr;
        }
        else {
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }

    
    bool company::erase(const std::string& product_name) {//erase the product with the parameter product_name, return true if successful, return false if unsuccessful
        assert(product_name.length() > 0);
        node* temp = head_ptr;
        if(list_contains_item(head_ptr, product_name) == false){
            return false;
        }
        node* target = list_search(head_ptr, product_name);
        target->setName(head_ptr->getName());
        target->setPrice(head_ptr->getPrice());
        list_head_remove(head_ptr);
        return true;
    }
    
    
}
