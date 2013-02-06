 fid = fopen('test.txt','w');
x=121:170;

fprintf(fid,'[');
for i=1:length(x)
fprintf(fid,'%04d    ',x(i));
end;
fprintf(fid,[']' 13 10]);


sigma=3;
mu=140;
y=1000*20*1/(sqrt(2*pi)*sigma)*exp(-0.5*(x-mu).^2/sigma^2);
plot(x,y,'.-');

fprintf(fid,'[');
for i=1:length(y)
fprintf(fid,'%07.2f ',y(i));
end;
fprintf(fid,']');
fclose(fid);