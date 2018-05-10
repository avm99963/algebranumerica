% example cometa Tentax
clear;
% original table
r=[2.70,2.00,1.61,1.20,1.02];
phi=[48,67,83,108,126];
% change of variables passing to a linear system
y=1./r; % divides each component by r
x=cosd(phi); % calculates cos of each component of phi
m=1; % degree of least squares polynomial
[coeff,norm2_res]=polminquad(x,y,m); % routine computing the latter polynomial - THIS IS WHAT WE HAVE TO DO
p=1/coeff(1); % coeff(1) = a, coeff(2) = b, where y = a + bx <=> 1/r = 1/p + (e/p)*cos \phi
exc=coeff(2)/coeff(1);
disp(sprintf("Aproximaci´o de p: %f ",p)); % disp: print
disp(sprintf("Aproximaci´o de exc: %f ",exc));
% we compute the aproximated orbit
rr=p./(1+exc*cosd(phi));
phi_min=min(phi);
phi_max=max(phi);
phiC=phi_min:0.1:phi_max;
xrr=r.*cosd(phi);
yrr=r.*sind(phi);
scatter(xrr,yrr,'r','filled'); hold on % scatter points
xC=p./(1+exc*cosd(phiC)).*cosd(phiC);
yC=p./(1+exc*cosd(phiC)).*sind(phiC);
plot(xC,yC,'b');
hold off;
