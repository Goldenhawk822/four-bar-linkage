#ifndef IMAGINARYNUMBERS_H
#define IMAGINARYNUMBERS_H

#include <iostream>
#include <cmath>

class Imag{
private:
	double real;
	double imaginary;
public:
	Imag();               //done
	Imag(double, double); //done
	Imag(char, double);	  //done (use 'd' for degrees, anything else for radians)
	Imag(Imag&);          //done
	double getreal();     //done
	double getimag();     //done
	double magnitude();   //done
	double magsquared();  //done
	double directrad();   //done
	double directdeg();   //done
	double posrad();
	double posdeg();
	Imag directImag();	  //done
	void changedirectdeg(double);		  //done
	void changedirectrad(double);		  //done
	void changedirectimag(Imag);		  //done
	void setmagnitude(double);			  
	void setreal(double); //done		  
	void setimag(double); //done
	friend Imag operator +(Imag, Imag);   //done
	friend Imag operator +(Imag, double); //done
	friend Imag operator +(double, Imag); //done
	friend Imag operator -(Imag, Imag);   //done
	friend Imag operator -(Imag, double); //done
	friend Imag operator -(double, Imag); //done
	friend Imag operator *(Imag, Imag);   //done
	friend Imag operator *(Imag, double); //done
	friend Imag operator *(double, Imag); //done
	friend Imag operator /(Imag, Imag);   //done
	friend Imag operator /(Imag, double); //done
	friend Imag operator /(double, Imag); //done
	//Imag& operator =(const Imag&);
	friend std::ostream& operator <<(std::ostream&, Imag); //done
	friend std::istream& operator >>(std::istream&, Imag); //may be fixed, will need to test to make sure
	//add additional functions here as necessary, but only for the complex number class


};

Imag::Imag(){
	real = 0;
	imaginary = 0;
}

Imag::Imag(double a, double b){
	real = a;
	imaginary = b;
}

Imag::Imag(char a, double b){
	if(a == 'd'){
		real = cos(3.14159*b/180);
		imaginary = sin(3.14159*b/180);
	}else{
		real = cos(b);
		imaginary = sin(b);
	}
}

Imag::Imag(Imag& a){
	real = a.getreal();
	imaginary = a.getimag();
}

double Imag::getreal(){
	return real;
}

double Imag::getimag(){
	return imaginary;
}

Imag operator +(Imag a, Imag b){
	Imag c(a.getreal()+b.getreal(), a.getimag()+b.getimag());
	return c;
}

Imag operator +(Imag a, double b){
	Imag c(a.getreal()+b, a.getimag());
	return c;
}

Imag operator +(double a, Imag b){
	Imag c(a+b.getreal(), b.getimag());
	return c;
}

Imag operator -(Imag a, Imag b){
	Imag c(a.getreal()-b.getreal(), a.getimag()-b.getimag());
	return c;
}

Imag operator -(Imag a, double b){
	Imag c(a.getreal() - b, a.getimag());
	return c;
}

Imag operator -(double a, Imag b){
	Imag c(a-b.getreal(), -b.getimag());
	return c;
}

Imag operator *(Imag a, Imag b){
	Imag c(a.getreal()*b.getreal()-a.getimag()*b.getimag(), a.getreal()*b.getimag() + a.getimag()*b.getreal());
	return c;
}

Imag operator *(Imag a, double b){
	Imag c(a.getreal()*b, a.getimag()*b);
	return c;
}

Imag operator *(double b, Imag a){
	Imag c(a.getreal()*b, a.getimag()*b);
	return c;
}

Imag operator /(Imag a, double b){
	a.setreal(a.getreal()/b);
	a.setimag(a.getimag()/b);
	return a;
}

Imag operator /(Imag a, Imag b){
	double d = b.getreal()*b.getreal()+b.getimag()*b.getimag();
	b.setimag(-1*b.getimag());
	Imag c = a*b;
	c = c/d;
	return c;
}

Imag operator /(double a, Imag b){
	double d = (b.getreal()*b.getreal()+b.getimag()*b.getimag());
	Imag c(a*b.getreal()/d, -a*b.getimag()/d);
	return c;
}

double Imag::magnitude(){
	return sqrt(real*real + imaginary*imaginary);
}

double Imag::magsquared() {
	return real*real + imaginary*imaginary;
}

double Imag::directrad(){
	return atan2(imaginary, real);
}

double Imag::directdeg(){
	return 180.0*atan2(imaginary, real)/3.14159;
}

Imag Imag::directImag(){
	double temp = magnitude();
	Imag direction(real/temp, imaginary/temp);
	return direction;
}

void Imag::changedirectdeg(double degrees){
	double temp = magnitude();
	real = temp*cos(3.14159*degrees/180);
	imaginary = temp*sin(3.14159*degrees/180);
}

void Imag::changedirectrad(double radians){
	double temp = magnitude();
	real = temp*cos(radians);
	imaginary = temp*sin(radians);
}

void Imag::changedirectimag(Imag a){
	double temp = magnitude();
	a = a/(a.magnitude());
	real = a.getreal()*temp;
	imaginary = a.getimag()*temp;
}

void Imag::setmagnitude(double a){
	double temp = a/magnitude();
	real = real*temp;
	imaginary = imaginary*temp;
}

std::ostream& operator <<(std::ostream& sout, Imag a){
	sout << a.getreal() << ", " << a.getimag() << " i";
	return sout;
}

std::istream& operator >>(std::istream& input, Imag a){
	double temp=0;
	input >> temp;
	a.setreal(temp);
	input >> temp;
	a.setimag(temp);
	return input;
}

void Imag::setreal(double a){
	real = a;
}

void Imag::setimag(double a){
	imaginary = a;
}

double Imag::posdeg() {
	double val = 180.0*atan2(imaginary, real) / 3.14159;
	if (val < 0) {
		return val + 360;
	}
	return val;
}

double Imag::posrad() {
	double val = atan2(imaginary, real);
	if (val < 0) {
		return val + 2 * 3.14159;
	}
	return val;
}
#endif