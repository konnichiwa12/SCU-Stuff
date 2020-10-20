//
//  poly.cpp
//  coen79_lab4
//
//  Created by dkanai on 2/3/20.
//  Copyright © 2020 SCU. All rights reserved.
//

#include "poly.h"
#include <iomanip>
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;
namespace coen79_lab4{
    polynomial::polynomial(double c, unsigned int exponent){//constructor for class polynomial, replace poly[exponent] with c after initializing everything to 0
        assert(exponent <= polynomial::MAXIMUM_DEGREE);
        for (int i = 0; i < MAXIMUM_DEGREE + 1; i++){
            poly[i] = 0;
        }
        poly[exponent] = c;
        current = exponent;
    }
    void polynomial::assign_coef(double amount, unsigned int exponent){//assign a coefficient to poly[exponent]
        assert(exponent <= polynomial::MAXIMUM_DEGREE);
        poly[exponent] = amount;
        return;
    }
    void polynomial::add_to_coef(double coefficient, unsigned int exponent){//add coefficient to poly[exponent];
        assert(exponent <= polynomial::MAXIMUM_DEGREE);
        poly[exponent] += coefficient;
        return;
    }
    void polynomial::clear(){//set all elements of poly to 0
        for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++){
            poly[i] = 0.0;
        }
    }
    polynomial polynomial::antiderivative() const{//return the antiderivative of poly
	assert(degree() < polynomial::MAXIMUM_DEGREE);
	polynomial returnthis;
	double temp;
        for (int i = 0; i < polynomial::MAXIMUM_DEGREE; i++){
            temp = (poly[i])/(i+1);
            returnthis.assign_coef(temp, i + 1);
        }
        returnthis.assign_coef(0, 0);
        return returnthis;
    }
    double polynomial::coefficient(unsigned int exponent) const{//return the coefficient at poly[exponent]
        if (exponent > polynomial::MAXIMUM_DEGREE){
            return 0.0;
        }
        return poly[exponent];
    }
    double polynomial::definite_integral(double x0, double x1){//return the definite integral from x0 to x1
	double uno;
	double dos;
	polynomial temp;
	temp = antiderivative();
	uno = temp.eval(x0);
	dos = temp.eval(x1);
	return dos - uno;

    }
    unsigned int polynomial::degree() const{//return the degree of the largest exponent whose coefficient is non zero
        int i = 0;
        for (int j = 0; j < polynomial::MAXIMUM_DEGREE + 1; j++){
            if (poly[j] != 0){
                i = j;
            }
        }
        return i;
    }
    polynomial polynomial::derivative() const{//return the derivative of poly
        polynomial returnthis;
        double temp;
        for (int i = 1; i < polynomial::MAXIMUM_DEGREE; i++){
            temp = poly[i]*i;
            returnthis.assign_coef(temp, i - 1);
        }
        return returnthis;
    }
    double polynomial::eval(double x) const{//return the value of poly given the value for x (evaluate f(x))
        double sum;
        for (int i = 0; i <= degree(); i++){
            sum += poly[i]*(pow(x,i));
        }
        return sum;
    }
    bool polynomial::is_zero() const{//return true if poly has 0s for all indexes
        for (int i = 0; i < polynomial::MAXIMUM_DEGREE; i++){
            if (poly[i] != 0){
                return false;
            }
        }
        return true;
    }
    unsigned int polynomial::next_term(unsigned int e) const{//return the value of the next exponent larger than e whos coefficient is non zero
    	int i = e;
    	for (i = e; i < polynomial::MAXIMUM_DEGREE; i++){
    		if (coefficient(i) != 0){
			return i;
            }
    	}
	return 0;
    }
    unsigned int polynomial::previous_term(unsigned int e) const{//return the value of the exponent smaller than e whos coefficient is non zero
        int i = e;
        for( i = e - 1; i >= 0; i--){
            if (poly[i] != 0){
                return i;
            }
        }        return UINT_MAX;
    }
    double polynomial::operator() (double x) const{//does the same as eval function
	double sum;
        for(int i = 0; i < polynomial::MAXIMUM_DEGREE; i++){
            sum += poly[i]*pow(x,i);
        }
        return sum;
    }
    

    polynomial operator +(const polynomial& p1, const polynomial& p2){//return a polynomial with coefficients equal to the sum of the coefficients of p1 and p2
        polynomial temp;
        double value = 0;
        for (int i = 0; i < polynomial::MAXIMUM_DEGREE; i++){
            value = p1.coefficient(i) + p2.coefficient(i);
            temp.add_to_coef(value, i);
        }
        return temp;
    }
    polynomial operator -(const polynomial& p1, const polynomial& p2){//return a polynomial with the coefficients equal to the difference of the coefficients in p1 and p2
        polynomial temp;
        double value = 0;
        for (int i = 0; i < polynomial::MAXIMUM_DEGREE; i++){
            value = p1.coefficient(i) - p2.coefficient(i);
            temp.add_to_coef(value, i);
        }
        return temp;
    }
    polynomial operator *(const polynomial& p1, const polynomial& p2){//return a polynomial where the FOIL method has been used on p1 and p2 (mulitplying two polynomials)
        assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
        polynomial temp;
        int a = p1.degree();
        int b = p2.degree();
        double addin = 0;
        for (int i = 0; i < b + 1 ; i++){
            for (int j = 0; j < a + 1; j++){
                temp.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
            }
        }
        return temp;
    }
    ostream& operator << (ostream& out, const polynomial& p){//overload the << operator and specifically tell the computer how to print out info from polynomials
        int fixnum = out.precision();
        out << std::fixed;
        out << std::setprecision(1);
        int num = p.degree();
        if(num == 0){
            if (p.coefficient(0) == 0){
                out << "0.0";
            }
            else{
                out << p.coefficient(0);
            }
        }
        else{
            out << (p.coefficient(num)) << "x^" << num;
                for (int i = num - 1; i >= 0; i--){
                    if (p.coefficient(i) > 0.0){
                        out << " + " << p.coefficient(i);
                    }
                    else if (p.coefficient(i) < 0.0){
                        out << " - " << p.coefficient(i)*-1;
                    }
                    if ((i > 1)&&(p.coefficient(i) != 0.0)){
                        out << "x^" << i;
                    }
                    else if ((i == 1)&&(p.coefficient(i) != 0.0)){
                        out << "x";
                    }
                }
        }
        out << std::setprecision(fixnum);
        return out;
    }
        
}

