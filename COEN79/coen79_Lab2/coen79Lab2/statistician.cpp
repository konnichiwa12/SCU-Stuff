// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h" //include header file

using namespace std;
namespace coen79_lab2
{
    statistician::statistician(){//set default values since there are no parameters (min has to be max, can't be 0 since 0 is already the smallest number you can have)
                total = 0.0;
                max = -2147483647.0;
                min = 2147483647.0;
                avg = 0.0;
                n = 0;
            }
        void statistician::next(double r){//receive new value, process it and change private variables based on this new number
                if (r > max){
                    max = r;
                }
                if (r < min){
                    min = r;
                }
                total += r;
                n++;
                avg = total/n;
                return;
            }
            void statistician::reset(){//reset all values, set everything to 0 except min (needs to be set to max double)
                total = 0.0;
                max = -2147483647.0;
                min = 2147483647.0;
                avg = 0.0;
                n = 0;
                return;
            }
            int statistician::length() const{//return length of sequence, constant function
                return n;
            }
            double statistician::sum() const{//return sum, constant function
                return total;
            }
            double statistician::mean() const{//return average of sequence, constant function
                return avg;
            }
            double statistician::minimum() const{//return minimum value in sequence, constant function
                return min;
            }
            double statistician::maximum() const{//return maximum value in sequence, constant function
                return max;
            }
        statistician operator +(const statistician &s1, const statistician& s2){//define operation + (adding to objects together). Add the sum and length of each object together. Recalculate the average based on the new sum and length. Compare each object's min and max values and choose the new max and min. is a friend function
            statistician r;
            r.total = s1.total + s2.total;
            r.n = s1.n + s2.n;
            r.avg = r.total/r.n;
            if (s1.max >= s2.max){
            r.max = s1.max;
            }
            else{
                r.max = s2.max;
            }
            if (s1.min <= s2.min){
                r.min = s1.min;
            }
            else{
                r.min = s2.min;
            }
            return r;
        }
        statistician operator *(double scale, const statistician& s){//define operation *. Multiply each private variable by the scale variable passed as parameter. is a friend function
            statistician r;
            r.total = s.total * scale;
            r.max = s.max * scale;
            r.min = s.min * scale;
            r.n = s.n * scale;
            r.avg = s.avg * scale;
            if (r.max < r.min){
                double temp = r.max;
                r.max = r.min;
                r.min = temp;
            }
            return r;
        }
    bool operator ==(const statistician& s1, const statistician& s2){//check if the objects are equal, compare each private variable and see if each are equal. Return a boolean based off of these results
        if ((s1.length() == 0)&&(s2.length() == 0)){
            return true;
        }
        else if ((s1.length() == s2.length())&&(s1.maximum() == s2.maximum())&&(s1.minimum() == s2.minimum())&&(s1.sum() == s2.sum())&&(s1.mean() == s2.mean())){
            return true;
        }
            return false;
    }
}


