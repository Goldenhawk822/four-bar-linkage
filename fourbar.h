#ifndef FOURBAR_H
#define FOURBAR_H

#include "imaginarynumbers.h"

class FourBar {
private:
	Imag AoA1;
	Imag A1C;
	Imag BoB1;
	Imag B1C;
	Imag A1B1;
	Imag AoBo;
public:
	FourBar();
	FourBar(Imag, Imag, Imag, Imag);
	void setAoA1(Imag);
	void setA1C(Imag);
	void setBoB1(Imag);
	void setB1C(Imag);
	void setAoA1(double, double);
	void setA1C(double, double);
	void setBoB1(double, double);
	void setB1C(double, double);
	void randomize(double);
	//rotates the AoA1 vector by the amount theta in radians, then adjusts the position of all other vectors, will return false if an error occurs and the fourbar will revert to it's initial state
	bool rotatebyrad(double);
	//rotates the AoA1 vector by the amount theta in degrees, then adjusts the position of all other vectors, will return false if an error occurs and the fourbar will revert to it's initial state
	bool rotatebydeg(double);
	Imag getAoA1();
	Imag getA1C();
	Imag getBoB1();
	Imag getB1C();
};

FourBar::FourBar() {
	AoA1.setreal(1.0);
	AoA1.setimag(1.0);
	A1C.setreal(1.0);
	A1C.setimag(1.0);
	BoB1.setreal(-1.0);
	BoB1.setimag(1.0);
	B1C.setreal(-1.0);
	B1C.setimag(1.0);
	A1B1 = A1C - B1C;
	AoBo = AoA1 + A1B1 - BoB1;
}

FourBar::FourBar(Imag AoA1new, Imag A1Cnew, Imag BoB1new, Imag B1Cnew) {
	AoA1 = AoA1new;
	A1C = A1Cnew;
	BoB1 = BoB1new;
	B1C = B1Cnew;
	A1B1 = A1C - B1C;
	AoBo = AoA1 + A1B1 - BoB1;
}

void FourBar::setAoA1(Imag AoA1new) {
	AoA1 = AoA1new;
	AoBo = AoA1 + A1B1 - BoB1;
}

void FourBar::setBoB1(Imag BoB1new) {
	BoB1 = BoB1new;
	AoBo = AoA1 + A1B1 - BoB1;
}

void FourBar::setA1C(Imag A1Cnew) {
	A1C = A1Cnew;
	A1B1 = A1C - B1C;
	AoBo = AoA1 + A1B1 - BoB1;
}

void FourBar::setB1C(Imag B1Cnew) {
	B1C = B1Cnew;
	A1B1 = A1C - B1C;
	AoBo = AoA1 + A1B1 - BoB1;
}

void FourBar::setAoA1(double x, double y) {
	AoA1.setreal(x);
	AoA1.setimag(y);
	AoBo = AoA1 + A1B1 - BoB1;
}

void FourBar::setA1C(double x, double y) {
	A1C.setreal(x);
	A1C.setimag(y);
	A1B1 = A1C - B1C;
	AoBo = AoA1 + A1B1 - BoB1;
}

void FourBar::setBoB1(double x, double y) {
	BoB1.setreal(x);
	BoB1.setimag(x);
	AoBo = AoA1 + A1B1 - BoB1;
}

void FourBar::setB1C(double x, double y) {
	BoB1.setreal(x);
	BoB1.setimag(y);
	A1B1 = A1C - B1C;
	AoBo = AoA1 + A1B1 - BoB1;
}

//Randomizes the fourbar to be within the maximum size specified, uses the rand() function
void FourBar::randomize(double maxsize) {
	AoA1.setreal((rand() % 201 - 100)*maxsize / 800);
	AoA1.setimag((rand() % 201 - 100)*maxsize / 800);
	A1C.setreal((rand() % 201 - 100)*maxsize / 800);
	A1C.setimag((rand() % 201 - 100)*maxsize / 800);
	BoB1.setreal((rand() % 201 - 100)*maxsize / 800);
	BoB1.setimag((rand() % 201 - 100)*maxsize / 800);
	B1C.setreal((rand() % 201 - 100)*maxsize / 800);
	B1C.setimag((rand() % 201 - 100)*maxsize / 800);
	A1B1 = A1C - B1C;
	AoBo = AoA1 + A1B1 - BoB1;
}

Imag FourBar::getAoA1() {
	return AoA1;
}

Imag FourBar::getA1C() {
	return A1C;
}

Imag FourBar::getBoB1() {
	return BoB1;
}

Imag FourBar::getB1C() {
	return B1C;
}

int min4(double a, double b, double c, double d) {
	if (a < b) {
		if (a < c) {
			if (a < d) {
				return 1;
			}
			else {
				return 4;
			}
		}
		else {
			if (c < d) {
				return 3;
			}
			else {
				return 4;
			}
		}
	}
	else {
		if (b < c) {
			if (b < d) {
				return 2;
			}
			else {
				return 4;
			}
		}
		else {
			if (c < d) {
				return 3;
			}
			else {
				return 4;
			}
		}
	}
}

bool FourBar::rotatebyrad(double theta) {
	double offset = A1C.posrad() - A1B1.posrad();
	Imag A = AoA1;
	Imag B = A1B1;
	Imag C = BoB1;
	A.changedirectrad(A.directrad() + theta);
	A = A - AoBo;
	double N = C.magsquared() - B.magsquared() - A.magsquared();
	N = N / (2 * B.magnitude());
	double u1, u2, v1;
	double q = 0;
	double mag1 = 0;
	double mag2 = 0;
	double mag3 = 0;
	double mag4 = 0;
	u1 = 4 * (A.getreal()*A.getreal()*N*N - A.magsquared()*(N*N - A.getimag()*A.getimag()));
	if (u1 > 0) {
		u2 = sqrt(u1) + 2 * N * A.getreal();
		u2 = u2 / (2 * A.magsquared());
		u1 = -sqrt(u1) + 2 * N * A.getreal();
		u1 = u1 / (2 * A.magsquared());
		if (u1 > 1 || u1 < -1) {
			u1 = u2;
		}
		if (u1 < 1 && u1 > -1) {
			q = cos(B.directrad());
			if (abs(q - u1) > abs(q - u2)) {
				u1 = u2;
			}
			v1 = A.getreal() + B.magnitude()*u1;
			v1 = v1 / C.magnitude();
			B.changedirectrad(acos(u1));
			C.changedirectrad(acos(v1));
			mag1 = (A + B - C).magsquared();
			B.changedirectrad(-acos(u1));
			mag2 = (A + B - C).magsquared();
			C.changedirectrad(-acos(v1));
			mag3 = (A + B - C).magsquared();
			B.changedirectrad(acos(u1));
			mag4 = (A + B - C).magsquared();
			AoA1.changedirectrad(AoA1.directrad() + theta);
			switch (min4(mag1, mag2, mag3, mag4)) {
			case 1:
				A1B1.changedirectrad(acos(u1));
				BoB1.changedirectrad(acos(v1));
				break;
			case 2:
				A1B1.changedirectrad(-acos(u1));
				BoB1.changedirectrad(acos(v1));
				break;
			case 3:
				A1B1.changedirectrad(-acos(u1));
				BoB1.changedirectrad(-acos(v1));
				break;
			case 4:
				A1B1.changedirectrad(acos(u1));
				BoB1.changedirectrad(-acos(v1));
				break;
			}
			A1C.changedirectrad(A1B1.directrad() + offset);
			B1C = A1C - A1B1;
			return true;
		}
	}
	return false;
}

bool FourBar::rotatebydeg(double theta) {
	return this->rotatebyrad(theta*3.14159 / 180);
}
#endif