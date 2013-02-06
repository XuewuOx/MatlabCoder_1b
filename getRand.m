function [y] = getRand(seed) %#codegen
% main()  hello world
%              _
%  \/\ /\ /   /  * _  '
% _/\ \/\/ __/__.'(_|_|_

% Generate values from a normal distribution 
% with mean 1 and standard deviation 2.f
% y = 10 + 2.*randn;
rng(seed);
x=1:100;
sigma=15; mu=40; A=3;
y=A*exp(-(x-mu).^2/(2*sigma^2))+rand(size(x))*0.3;
% B=importdata('iruvdatafile.txt',' ');
% disp(y);
end

