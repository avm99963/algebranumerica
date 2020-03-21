% Toni Susin (2018)
function [M,b,dim]=loadSparseMatrix(filename)
finput=fopen(filename);
d=fscanf(finput,'%d',[2,1]);
dim=d(1);
data=d(2);
values=fscanf(finput,'%d %d %e',[3,data]);
M=values';
db=fscanf(finput,'%d',[1,1]);
bc=fscanf(finput,'%d %e',[2,db]);
b=bc';
fclose(finput);
%  How to use it:
% [M,b,dim]=loadSparseMatrix('M00.dat') 
% It reads the matrix M 