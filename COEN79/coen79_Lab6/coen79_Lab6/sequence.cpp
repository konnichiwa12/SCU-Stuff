//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }
    
    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence::sequence ()
    {
        init();
    }
    
    //Copy Constructor
    sequence::sequence(const sequence& source)
    {
        init();
        *this = source;
    }
    sequence::~sequence(){//destructor
        list_clear(head_ptr);
        head_ptr = tail_ptr = cursor = precursor = NULL;
        many_nodes = 0;
    }
    void sequence::start(){//set the cursor to the beginning of the list, precursor = NULL
        cursor = head_ptr;
        precursor = NULL;
    }
    void sequence::end(){//set cursor at the end of the list and precursor to 1 before cursor
        cursor = tail_ptr;
        precursor = head_ptr;
        while(precursor->link() != cursor){
            precursor = precursor->link();
        }
    }
    void sequence::advance(){//move cursor and precursor forwards one, they equal NULL if cursor->link() is NULL
        if(cursor->link() == NULL){
            cursor = NULL;
            precursor = NULL;
        }
        else{
            precursor = cursor;
            cursor = cursor->link();
        }
    }
    void sequence::insert(const value_type& entry){//insert a node into the list before cursor, if cursor = NULL, attach it at the beginning
        if(cursor == NULL || precursor == NULL){
            list_head_insert(head_ptr, entry);
            if(tail_ptr == NULL){
                tail_ptr = head_ptr;
            }
            cursor = head_ptr;
            precursor = NULL;
        }
        else{
            list_insert(precursor, entry);
            cursor = precursor->link();
        }
        many_nodes++;
    }
    void sequence::attach(const value_type &entry){//insert a node into the list after cursor, if cursor = NULL, attach it to the end
        if(head_ptr == NULL){
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
        }
        else if(cursor == NULL){
            list_insert(tail_ptr, entry);
            cursor = tail_ptr->link();
            precursor = tail_ptr;
            tail_ptr = tail_ptr->link();
        }
        else{
            list_insert(cursor, entry);
            precursor = cursor;
            cursor = cursor->link();
            if (cursor->link() == NULL){
                tail_ptr = tail_ptr->link();
            }
        }
        many_nodes++;
    }
    void sequence::operator =(const sequence& source){//overload assignment operator
        if(this == &source){
            return;
        }
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        many_nodes = source.size();
        node* temp = source.head_ptr;
        cursor = head_ptr;
        while(temp != source.cursor){
            advance();
            temp = temp->link();
        }
    }
    void sequence::remove_current( ){//remove the node cursor points to
        assert(is_item() == true);
        if(cursor == head_ptr){
            if(head_ptr == tail_ptr){
                list_head_remove(cursor);
                cursor = precursor = head_ptr = tail_ptr = NULL;
            }
            else{
                list_head_remove(head_ptr);
                cursor = head_ptr;
                precursor = NULL;
            }
        }
        else if(cursor == tail_ptr){
            list_remove(precursor);
            tail_ptr = cursor;
            cursor = precursor = NULL;
        }
        else{
            list_remove(precursor);
            cursor = precursor->link();
        }
        many_nodes--;
    }
    
    // CONSTANT MEMBER FUNCTIONS
    sequence::size_type sequence::size( ) const{//return many_nodes
        return many_nodes;
    }
    bool sequence::is_item( ) const{//return is cursor points to a valid node
        if (cursor != NULL){
            return true;
        }
        return false;
    }
    sequence::value_type sequence::current( ) const{//return the data of the node cursor points to
        assert(is_item() == true);
        return cursor->data();
    }
    
    
}
