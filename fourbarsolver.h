#ifndef FOURBARSOLVER_H
#define FOURBARSOLVER_H

#include "imaginarynumbers.h"
#include <cmath>

/*These functions are exclusively for solving 3 precision point 4 bars with specified rotations of the coupler and
driver/follower link. They only provide one of the 2 legs of the 4 bar.
13r requires the angle change between PP1 & PP2 and PP1 & PP3 in radians for alpha and beta
12r requires the angle change between PP1 & PP2 and PP2 & PP3 in radians for alpha and beta
13d and 12d are the same as 13r and 12r except the angle specified is in degrees (if you're feeling lazy)
finally, Z and W are modified by the function, and constitute the values "returned" by the function
*/
void solveforZandW13r(Imag delta1, Imag delta3, Imag& Z, Imag& W, double alpha1rad, double alpha3rad, double beta1rad, double beta3rad){
	
	Imag a1(cos(alpha1rad)-1,sin(alpha1rad));
	Imag a3(cos(alpha3rad)-1,sin(alpha3rad));
	Imag b1(cos(beta1rad)-1, sin(beta1rad));
	Imag b3(cos(beta3rad)-1, sin(beta3rad));
	Z = ((delta1-(delta3*(b1/b3)))/(a1-a3*(b1/b3)));
	W = ((delta3-(Z)*a3)/b3);
}

void solveforZandW12r(Imag delta1, Imag delta3, Imag& Z, Imag& W, double alpha1rad, double alpha2rad, double beta1rad, double beta2rad){
	
	double alpha3rad = alpha1rad+alpha2rad;
	double beta3rad = beta1rad+beta2rad;
	Imag a1(cos(alpha1rad)-1,sin(alpha1rad));
	Imag a3(cos(alpha3rad)-1,sin(alpha3rad));
	Imag b1(cos(beta1rad)-1, sin(beta1rad));
	Imag b3(cos(beta3rad)-1, sin(beta3rad));
	Z = ((delta1-(delta3*(b1/b3)))/(a1-a3*(b1/b3)));
	W = ((delta3-(Z)*a3)/b3);
}

void solveforZandW13d(Imag delta1, Imag delta3, Imag& Z, Imag& W, double alpha1deg, double alpha3deg, double beta1deg, double beta3deg){
	
	Imag a1(cos(3.14159*alpha1deg/180)-1,sin(3.14159*alpha1deg/180));
	Imag a3(cos(3.14159*alpha3deg/180)-1,sin(3.14159*alpha3deg/180));
	Imag b1(cos(3.14159*beta1deg/180)-1, sin(3.14159*beta1deg/180));
	Imag b3(cos(3.14159*beta3deg/180)-1, sin(3.14159*beta3deg/180));
	Z = ((delta1-(delta3*(b1/b3)))/(a1-a3*(b1/b3)));
	W = ((delta3-(Z)*a3)/b3);
}

void solveforZandW12d(Imag delta1, Imag delta3, Imag& Z, Imag& W, double alpha1deg, double alpha2deg, double beta1deg, double beta2deg){
	
	double alpha3deg = alpha1deg+alpha2deg;
	double beta3deg = beta1deg+beta2deg;
	Imag a1(cos(3.14159*alpha1deg/180)-1,sin(3.14159*alpha1deg/180));
	Imag a3(cos(3.14159*alpha3deg/180)-1,sin(3.14159*alpha3deg/180));
	Imag b1(cos(3.14159*beta1deg/180)-1, sin(3.14159*beta1deg/180));
	Imag b3(cos(3.14159*beta3deg/180)-1, sin(3.14159*beta3deg/180));
	Z = ((delta1-(delta3*(b1/b3)))/(a1-a3*(b1/b3)));
	W = ((delta3-(Z)*a3)/b3);
}

//These two functions are for using ground pivot specification to create a solution for motion generation,
//It will overwrite any Z, W, beta2 and beta 3 inputs with those of the new solution.
//r is for radians, d is for degrees (input and output, no mixed types)
/*
alpha2 & alpha2deg are the rotation of PP2 with respect to PP1
alpha3 & alpha3deg are the rotation of PP3 with respect to PP1
*/
void groundspecZandWr(Imag ground, Imag PP1, Imag PP2, Imag PP3, Imag& Z, Imag& W, double alpha2, double alpha3, double& beta2, double& beta3){
	Imag R1(0,0);
	Imag R2(0,0);
	Imag R3(0,0);
	Imag a2('r', alpha2);
	Imag a3('r', alpha3);
	R1 = PP1-ground;
	R2 = PP2-ground;
	R3 = PP3-ground;
	Imag D1(0,0);
	Imag D2(0,0);
	Imag D3(0,0);
	D1 = R3*a2-R2*a3;
	D2 = R1*a3-R3;
	D3 = R2-R1*a2;
	D1 = 0-D1;
	beta2 = 2*D1.directrad()-D2.directrad()-(D2*a2).directrad();
	beta3 = 2*D1.directrad()-D3.directrad()-(D3*a3).directrad();
	Imag b2('r', beta2);
	W = (R1-R2/a2)/(1+b2/a2);
	Z = R1-W;
}

void groundspecZandWd(Imag ground, Imag PP1, Imag PP2, Imag PP3, Imag& Z, Imag& W, double alpha2deg, double alpha3deg, double& beta2deg, double& beta3deg){
	Imag R1(0,0);
	Imag R2(0,0);
	Imag R3(0,0);
	Imag a2('d', alpha2deg);
	Imag a3('d', alpha3deg);
	R1 = PP1-ground;
	R2 = PP2-ground;
	R3 = PP3-ground;
	Imag D1(0,0);
	Imag D2(0,0);
	Imag D3(0,0);
	D1 = R3*a2-R2*a3;
	D2 = R1*a3-R3;
	D3 = R2-R1*a2;
	D1 = 0-D1;
	beta2deg = 2*D1.directdeg()-D2.directdeg()-(D2*a2).directdeg();
	beta3deg = 2*D1.directdeg()-D3.directdeg()-(D3*a3).directdeg();
	Imag b2('d', beta2deg);
	W = (R1-R2/a2)/(1+b2/a2);
	Z = R1-W;
}

/*These functions are exclusively for finding the angular velocities of the coupler and follower links given the x and y
of the Imag complex class for each component, AoA is from the ground on the driver link to the coupler, BoB is from the
ground of the follower to the coupler, and AB is from the coupler-driver joint to the coupler-follower joint. 
It modifies w3 and w4 and those are the apparent return values even though it is a void function. 
The output is in radians per second.
The function can be used if the known velocity is that of the follower link, but not if it is that of the coupler. 
In order to use the function with the follower link, simply rewrite the values as if the follower link was the driver.
It represents counterclockwise as being positive
*/
/*
In case you happen to be confused on the 4 bar terminology:
Ao = ground pivot for side A
A = moving pivot for side A
Bo = ground pivot for side B
B = moving pivot for side B
C = coupler point of interest
ABC is the coupler, consisting of sides AB, AC and BC
AoA is the driving link, going from Ao to A
BoB is the following link, going from Bo to B
etc...
*/


void findw3w4(Imag AoA, Imag AB, Imag BoB, Imag w2, Imag& w3, Imag& w4){

	w3.setreal(0);
	w4.setreal(0);
	Imag q1(w2*AoA/AB);
	Imag q2(BoB/AB);
	w4.setimag(q1.getreal()/q2.getimag());
	w3.setimag(w4.getimag()*q2.getreal() - q1.getimag());
}

//These two functions solve for the velocity of the coupler's point of interest (aka point C) remember to use the same units
//for AoA and AC, and wDriver and wCoupler, otherwise the answer will be wrong

//If you can't tell, wDriver is the angular velocity of the driving link, wCoupler is the angular velocity of the coupler
Imag findVofCouplerPOI(Imag AoA, Imag AC, double wDriver, double wCoupler){
	Imag w2(0, wDriver);
	Imag w3(0, wCoupler);
	return AoA*w2+AC*w3;
}


Imag findVofCouplerPOI(Imag AoA, Imag AB, Imag BoB, Imag AC, double wDriver){
	Imag w2(0, wDriver);
	Imag w3(0,0);
	Imag w4(0,0);
	Imag q1(w2*AoA/AB);
	Imag q2(BoB/AB);
	w4.setimag(q1.getreal()/q2.getimag());
	w3.setimag(w4.getimag()*q2.getreal() - q1.getimag());
	return AoA*w2+AC*w3;
}

/*
Rotates link AoA by the given angle, and returns AoA2, BoB2, AC2, and BC2
Ao = ground pivot for side A
A = moving pivot for side A
Bo = ground pivot for side B
B = moving pivot for side B
C = coupler point of interest
ABC is the coupler, consisting of sides AB, AC and BC
AoA is the driving link, going from Ao to A
BoB is the following link, going from Bo to B
etc...
*/
void rotate4BarRad(double angle, Imag AoA, Imag BoB, Imag AC, Imag BC, Imag& AoA2, Imag& BoB2, Imag& AC2, Imag& BC2){
	//Initializing additional variables
	Imag AB(0,0);
	Imag AoBo(0,0);
	Imag ABo2(0,0);
	Imag AB2(0,0);
	double angle2 = 0;
	AB = AC-BC;
	AB2 = AB;
	AoBo = AoA+AB-BoB;
	//Preparing outputs
	AoA2 = AoA;
	BoB2 = BoB;
	AC2 = AC;
	BC2 = BC;
	AoA2.changedirectrad(angle+AoA.directrad());
	ABo2 = AoBo - AoA2;
	//calculating coupler's rotation...
	angle2 = acos((AB.magnitude()*AB.magnitude()+ABo2.magnitude()*ABo2.magnitude()-(BoB.magnitude()*BoB.magnitude()))/(2*AB.magnitude()*ABo2.magnitude()));
	AB2.changedirectrad(angle2+ABo2.directrad());
	BoB2=AB2-ABo2;
	AC2.changedirectrad(AB2.directrad()+AB2.directrad()-AB.directrad());
	BC2.changedirectrad(AB2.directrad()+AB2.directrad()-AB.directrad());
}

void rotate4BarDeg(double angle, Imag AoA, Imag BoB, Imag AC, Imag BC, Imag& AoA2, Imag& BoB2, Imag& AC2, Imag& BC2){
	//Initializing additional variables
	Imag AB(0,0);
	Imag AoBo(0,0);
	Imag ABo2(0,0);
	Imag AB2(0,0);
	double angle2 = 0;
	AB = AC-BC;
	AB2 = AB;
	AoBo = AoA+AB-BoB;
	//Preparing outputs
	AoA2 = AoA;
	BoB2 = BoB;
	AC2 = AC;
	BC2 = BC;
	AoA2.changedirectdeg(angle+AoA.directdeg());
	ABo2 = AoBo - AoA2;
	//calculating coupler's rotation...
	angle2 = acos((AB.magnitude()*AB.magnitude()+ABo2.magnitude()*ABo2.magnitude()-(BoB.magnitude()*BoB.magnitude()))/(2*AB.magnitude()*ABo2.magnitude()));
	AB2.changedirectrad(angle2+ABo2.directrad());
	BoB2=AB2-ABo2;
	AC2.changedirectrad(AB2.directrad()+AB2.directrad()-AB.directrad());
	BC2.changedirectrad(AB2.directrad()+AB2.directrad()-AB.directrad());
}

//Returns the beta angle of the driving link (WA) that will result in a toggle position,
//relative to the current angle of the driving link.

//These two functions have not been tested yet, and should be considered experimental
double TogglePositionAngleRad(Imag AC, Imag AoA, Imag BC, Imag BoB){
	Imag AB(0,0);
	AB = AC-BC;
	Imag AoBo(0,0);
	AoBo = AoA+AB-BoB;
	double angle = acos((AoBo.magnitude()*AoBo.magnitude()+AoA.magnitude()*AoA.magnitude()-(AB.magnitude()+BoB.magnitude())*(AB.magnitude()+BoB.magnitude()))/(2*AoBo.magnitude()*AoA.magnitude()));
	angle = angle+AoBo.directrad()-AoA.directrad();
	return angle;
}

double TogglePositionAngleDeg(Imag AC, Imag AoA, Imag BC, Imag BoB){
	double angle = TogglePositionAngleRad(AC, AoA, BC, BoB);
	angle = 180*angle/3.14159;
	return angle;
}

#endif
