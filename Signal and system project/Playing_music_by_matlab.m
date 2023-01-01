% program to play the song "3107-1" with pure tone
%
clc
clear all
%clf reset
% MUSICAL SCALE
s=2^(1/12);
R=0; % This is a rest
A0=110;
A0s=A0*s;
B0=A0s*s;
C0=B0*s;
C0s=C0*s;
D0=C0s*s;
D0s=D0*s;
E0=D0s*s;
F0=E0*s;
F0s=F0*s;
G0=F0s*s;
G0s=G0*s;

A=220;
As=A*s;
B=As*s;
C=B*s; % Middle C
Cs=C*s;
D=Cs*s;
Ds=D*s;
E=Ds*s;
F=E*s;
Fs=F*s;
G=Fs*s;
Gs=G*s;

A2=440;
A2s=A2*s;
B2=A2s*s;
C2=B2*s;
C2s=C2*s;
D2=C2s*s;
D2s=D2*s;
E2=D2s*s;
F2=E2*s;
F2s=F2*s;
G2=F2s*s;
G2s=G2*s;

A3=880;
A3s=A3*s;
B3=A3s*s;
C3=B3*s;
C3s=C3*s;
D3=C3s*s;
D3s=D3*s;
E3=D3s*s;
F3=E3*s;
F3s=F3*s;
G3=F3s*s;
G3s=G3*s;

Fs=8000;
t=0:1/Fs:0.3;
t2=0:1/Fs:0.52;
t3=0:1/Fs:0.95;
t4=0:1/Fs:1.25;
N=300;
A=2;

%Đô
nC=A*exp(-0.5*t).*cos(2*pi*C*t);
nC2=A*exp(-0.5*t2).*cos(2*pi*C*t2);
%Rê
nD=A*exp(-0.5*t).*cos(2*pi*D*t);
nD2=A*exp(-0.5*t2).*cos(2*pi*D*t2);
nD3=A*exp(-0.5*t3).*cos(2*pi*D*t3);
nD4=A*exp(-0.5*t4).*cos(2*pi*D*t4);
%Mi
nE=A*exp(-0.5*t).*cos(2*pi*E*t);
nE2=A*exp(-0.5*t2).*cos(2*pi*E*t2);
nE3=A*exp(-0.5*t3).*cos(2*pi*E*t3);
nE4=A*exp(-0.5*t4).*cos(2*pi*E*t4);
%Fa
nF=A*exp(-0.5*t).*cos(2*pi*F*t);
nF2=A*exp(-0.5*t2).*cos(2*pi*F*t2);
nF3=A*exp(-0.5*t3).*cos(2*pi*F*t3);
nF4=A*exp(-0.5*t4).*cos(2*pi*F*t4);
%Sol
nG=A*exp(-0.5*t).*cos(2*pi*G*t);
nG2=A*exp(-0.5*t2).*cos(2*pi*G*t2);
nG3=A*exp(-0.5*t3).*cos(2*pi*G*t3);
nG4=A*exp(-0.5*t4).*cos(2*pi*G*t4);
%La
nA=A*exp(-0.5*t).*cos(2*pi*A2*t);
nA2=A*exp(-0.5*t2).*cos(2*pi*A2*t2);
nA4=A*exp(-0.5*t4).*cos(2*pi*A2*t4);

%Si
nB=A*exp(-0.5*t).*cos(2*pi*B2*t);
nB2=A*exp(-0.5*t2).*cos(2*pi*B2*t2);
nB3=A*exp(-0.5*t3).*cos(2*pi*B2*t3);

%Đố
nC_H=A*exp(-0.5*t).*cos(2*pi*C2*t);
nC_H2=A*exp(-0.5*t2).*cos(2*pi*C2*t2);
nC_H4=A*exp(-0.5*t4).*cos(2*pi*C2*t4);

%Rế
nD_H=A*exp(-0.5*t).*cos(2*pi*D2*t);
nD_H2=A*exp(-0.5*t2).*cos(2*pi*D2*t2);
nD_H3=A*exp(-0.5*t3).*cos(2*pi*D2*t3);
nD_H4=A*exp(-0.5*t4).*cos(2*pi*D2*t4);

%Mí
nE_H=A*exp(-0.5*t).*cos(2*pi*E2*t);
nE_H2=A*exp(-0.5*t2).*cos(2*pi*E2*t2);
nE_H3=A*exp(-0.5*t3).*cos(2*pi*E2*t3);
nE_H4=A*exp(-0.5*t4).*cos(2*pi*E2*t4);

%Fá
nF_H=A*exp(-0.5*t).*cos(2*pi*F2*t);
nF_H2=A*exp(-0.5*t2).*cos(2*pi*F2*t2);
nF_H4=A*exp(-0.5*t4).*cos(2*pi*F2*t4);


x=[nG2,nE,nG3,nC_H,nC_H,nB,nB2,nC_H,nB2,nA,nE3,...
nG,nG,nG2,nF,nF3,nE,nE2,nF,nF4,nC,nE4,nG,nD4,...
nG2,nE,nG3,nC_H,nC_H,nB,nB2,nC_H,nB2,nA,nE3,...
nG,nG,nG2,nF,nF3,nG,nG2,nF,nF3,nE,nD,nE2,nE,nE2,nG2,nG4,...
nG,nC_H2,nD_H,nD_H2,nD_H,nD_H2,nC_H,nE_H4,...
nB,nC_H2,nA,nB2,nB,nC_H2,nC_H2,nA4,...
nA,nB2,nC_H,nE_H2,nE_H,nE_H2,nD_H2,nF_H4,...
nA,nB2,nC_H,nE_H2,nE_H,nF_H2,nE_H2,nD_H4,...
nG,nC_H2,nD_H,nD_H2,nD_H,nD_H2,nC_H,nE_H4,...
nB,nC_H2,nA,nB2,nB,nC_H2,nB2,nA4,...
nA,nB2,nC_H,nE_H2,nE_H,nE_H2,nD_H2,nF_H4,...
nC_H,nC_H2,nG,nG2,nC_H2,nD_H4,...
nG,nC_H2,nD_H,nD_H2,nD_H,nD_H2,nC_H,nE_H4,...
nB,nC_H2,nA,nB2,nB,nC_H2,nB2,nA4,...
nA,nB2,nC_H,nE_H2,nE_H,nE_H2,nD_H2,nF_H4,...
nA,nB2,nC_H,nE_H2,nE_H,nF_H2,nE_H2,nD_H4,...
nC_H,nB2,nA,nB2,nB,nC_H2,nB2,nA4,...
nA,nB2,nC_H,nE_H2,nE_H,nE_H2,nF_H2,nA4,...
nA,nB2,nC_H,nE_H2,nE_H,nF_H2,nE_H2,nD_H4,...
nB3,nC_H4] 
  
sound(x,Fs);
