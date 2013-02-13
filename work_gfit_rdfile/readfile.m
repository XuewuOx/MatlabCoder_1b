function [gfir gfuv] = readfile(filename) %#codegen
% version: .\work_readfile\readfile_v5.m

% The 'fprintf' function will not be compiled and instead passed
% to the MATLAB runtime. If we choose to generate code for this example,
% all calls to extrinsic functions are automatically eliminated.
coder.extrinsic('fprintf');
coder.extrinsic('sprintf');
coder.extrinsic('num2str');
coder.extrinsic('plot');
coder.extrinsic('hold');
coder.extrinsic('save');
coder.extrinsic('title');
coder.extrinsic('xlabel');
coder.extrinsic('ylabel');
coder.extrinsic('stem');
coder.extrinsic('figure');
coder.extrinsic('grid');

% Put class and size constraints on function input.
assert(isa(filename, 'char'));
assert(size(filename, 1) == 1);
assert(size(filename, 2) <= 1024);

tempvar=int32(-1);

% Define a new opaque variable 'f' which will be of type 'FILE *'
% in the generated C code initially with the value NULL.
f = coder.opaque('FILE *', 'NULL');

% Call fopen(filename 'r'), but we need to convert the MATLAB
% string into a C type string (which is the same string with the
% NUL (\0) string terminator).
f = coder.ceval('fopen', c_string(filename), c_string('r'));
tempvar=coder.ceval('(int)',f);
if (tempvar==0)
    fprintf('Open file %s failed.\n', filename);
    gfir=[-1 -1 -1]; gfuv=[-1 -1 -1];
    return;
end;

% Call fseek(f, 0, SEEK_END) to set file position to the end of
% the file.
coder.ceval('fseek', f, int32(0), coder.opaque('int', 'SEEK_END'));

% We need to initialize the variable 'filelen' to the proper type
% as custom C functions are not analyzed.
filelen = int32(0);

% Call ftell(f) which will return the length of the file in bytes
% (as current file position is at the end of the file).
filelen = coder.ceval('ftell', f);
fprintf('filelen=%d\n',filelen);
% Reset current file position
coder.ceval('fseek', f, int32(0), coder.opaque('int', 'SEEK_SET'));

% Initialize a buffer
bufSIZE=65536*1024;
% buffer = zeros(1,bufSIZE,'uint8');
bufline=zeros(1,65536,'uint8'); 
   % NOTE: bufline will be define as uint8_T type in generated C code
   % manually change its type to char_T in the generated c codes, 
   % like char_T bufline[65536];
% strline=zeros(1,1024,'uint8');
nStep=zeros(1,1,'int32');

% Remaining is the number of bytes to read (from the file)
remaining = filelen;

% Index is the current position to read into the buffer
index = int32(1);
nline=int32(0);

nVar=int32(0);
nChar=int32(0);

char100=uint8(0);
posA=int32(0);
posB=int32(0);
nSam=int32(0);
nStep=int32(0);
nFs=int32(0);
k4step=int32(0); % a temp variable to keep the value of current steps

for nline=1:1
    fprintf('line %d, ',nline);
   coder.ceval('fgets',coder.ref(bufline(1)), int32(1024),f);  
   nChar=coder.ceval('strlen',coder.ref(bufline(1)));
  fprintf('(%d)="%s',nChar,bufline(1:nChar)); 
end;

nline=nline+1; fprintf('line %d, ',nline);
nVar=coder.ceval('fscanf',f, ...
    ['%cSWN posA=%d, posB=%d, nSteps=%d, nSam=%d, Fs=%d' 13 10], ...
        coder.ref(char100), coder.ref(posA), coder.ref(posB), ...
        coder.ref(nStep), coder.ref(nSam),coder.ref(nFs));
 if (nVar~=6)
      fprintf('ERROR: fscanf cannot read formatted line %d. Inncorrect format\n', nline);
      coder.ceval('fclose', f);
      gfir=[-2 -2 -2]; gfuv=[-2 -2 -2];
      return;
 end;
 fprintf('nVar=%d, posA=%d, posB=%d, nStep=%d, nSam=%d, Fs=%d\n', ...
            nVar,posA, posB, nStep, nSam, nFs);

for nline=3:5
   fprintf('line %d, ',nline);
   coder.ceval('fgets',coder.ref(bufline(1)), int32(8192),f);  
   nChar=coder.ceval('strlen',coder.ref(bufline(1)));
   fprintf('(%d)="%s',nChar,bufline(1:nChar)); 
end;

% read data from 7-th line now
dataMS=zeros(nStep,1);
% k=nStep;
dataIR=zeros(nStep,nSam);
dataUV=zeros(nStep,nSam);
xir=int32(0);
xuv=int32(0);
k=1;

lenChar=int32(0);
lenChar=7+nSam*10+2;
% read data line-by-line
for k=1:nStep
    nline=nline+1; 
    % fprintf('line %d, ',nline);
    coder.ceval('fgets',coder.ref(bufline(1)), int32(lenChar),f);  
    nChar=coder.ceval('strlen',coder.ref(bufline(1)));
    % fprintf('(%d)="%s',nChar,bufline(1:nChar));  % to debug if fgets ok
  
   %  % read motor step data
     nVar=coder.ceval('sscanf', coder.ref(bufline(1)), ['%d '],coder.ref(k4step));
     % fprintf(' nStep=%d \n', k4step);
     dataMS(k)=coder.ceval('(double)',k4step);
   %  % read IR UV data
     for i=1:nSam
         nVar=coder.ceval('sscanf',coder.ref(bufline(7+10*(i-1))), ['%d %d'],coder.ref(xir), coder.ref(xuv));
         if (nVar~=2)
             fprintf('ERROR: sscanf cannot read formatted item %d, line %d. [xir=%d, xuv=%d]Inncorrect format\n', i, nline, xir, xuv);
             coder.ceval('fclose', f);
             gfir=[-2 -2 -2]; gfuv=[-2 -2 -2];
             return;
         end;
         % fprintf (' %04d %04d', xir, xuv);
         dataIR(k,i)=coder.ceval('(double)',xir);
         dataUV(k,i)=coder.ceval('(double)',xuv);
     end;
     % fprintf ('\n');
     
%      % display the dataIR and dataUV
%      fprintf('  dataIR(%d,:)=%s\n',k,num2str(dataIR(k,1:nSam)));
%      fprintf('  dataUV(%d,:)=%s\n',k,num2str(dataUV(k,1:nSam)));

 
%     % move to the end of line for next reading 
%     % coder.ceval('fgets',coder.ref(bufline(1)), int32(1024),f); 
%     coder.ceval('fgets',coder.ref(bufline(1)), int32(1024),f);  
%     nChar=coder.ceval('strlen',coder.ref(bufline(1)));
%     % fprintf('left %d chars="%s',nChar,bufline(1:nChar)); 
%     fprintf('   left %d chars ="',nChar);
%     for i=1:nChar
%            fprintf(' %02H',bufline(i));
%     end;
%     fprintf('"\n');
% %     [n strline]=readLine(bufline,f);
% %     if (n<=0)
% %         y=-1;
% %         return;
% %     end;
% %     fprintf(' (%d left = "%s")\n',n, strline(1:n));
end;
    
% Close file
coder.ceval('fclose', f);
fprintf('reading file successes, %d lines, %d-%d steps. Close file and return\n',...
    nline,dataMS(1), dataMS(length(dataMS)));

% % data processing
 dataIR_mean=mean(dataIR,2);
 dataUV_mean=mean(dataUV,2);
%   % % plot mean data 
    figure('name',filename);
    fprintf('  dataIR_mean=%s\n',num2str(dataIR_mean'));
    fprintf('  dataUV_mean=%s\n',num2str(dataUV_mean'));
    plot(dataMS, dataIR_mean,'.-r');
    hold on;
    plot(dataMS, dataUV_mean,'o-b');
    title('IR/UV means vs motor steps'); 
    xlabel('Motor steps','fontsize',12); ylabel('IR/UV (mv)', 'fontsize',12);
    fprintf('plot UVIR data OK\n');
% % gaussian fitting over UV
    fprintf('Gaussian fit over dataUV');
    mu=-9999;
    [sigmaUV, muUV, AUV] = gfit(dataMS,dataUV_mean,0.2);
    % plot gaussian fitting results
    fprintf('... OK.\n optimal postion of UV(step) is %04d (mu=%f, sigma=%f, A=%f)\n',...
         round(muUV),muUV, sigmaUV, AUV);
    y_gf=AUV*exp(-(dataMS-muUV).^2/(2*sigmaUV^2));
    plot(dataMS,y_gf,'.-m');
    stem(round(muUV),AUV,'sk');
    
% % gaussian fitting over IR
    fprintf('Gaussian fit over dataIR');
    mu=-9999;
    [sigmaIR, muIR, AIR] = gfit(dataMS,dataIR_mean,0.2);
    % plot gaussian fitting results
    fprintf('... OK.\n optimal postion of IR(step) is %04d (mu=%f, sigma=%f, A=%f)\n',...
         round(muIR),muIR, sigmaIR, AIR);
    y_gf=AIR*exp(-(dataMS-muIR).^2/(2*sigmaIR^2));
    plot(dataMS,y_gf,'.-g');
    stem(round(muIR),AIR,'sg');
    % title(sprintf('IR/UV vs steps \n opt(UV)=%d, opt(IR)=%d',round(muUV), round(muIR)), 'fontsize', 14);
     title(sprintf('%s (MS: %d to %d) \n opt(UV)=%d, opt(IR)=%d ',filename,dataMS(1),dataMS(nStep), round(muUV), round(muIR)), ...
        'Interpreter','none','fontsize', 14);
    grid on;
    
% return the optimal step 
gfir=[round(muIR) AIR sigmaIR];
gfuv=[round(muUV) AUV sigmaUV];
% save('instData', 'dataIR', 'dataUV','dataIR_mean','dataUV_mean');
return;

% Create a NUL terminated C string given a MATLAB string
function y = c_string(s)
y = [s 0];

% Create a \NL\CR+NUL terminated C string given a MATLAB string
function y = c_stringCR(s)
y = [s 13 10 0];

function [sigma, mu, A] = gfit(x,y,h) %#codegen
% [sigma,mu,A]=gfit(x,y)
% [sigma,mu,A]=gfit(x,y,h)
%
% this function is doing fit to the function
% y=A * exp( -(x-mu)^2 / (2*sigma^2) )
%
% the fitting is been done by a polyfit
% the lan of the data.
%
% h is the threshold which is the fraction
% from the maximum y height that the data
% is been taken from.
% h should be a number between 0-1.
% if h have not been taken it is set to be 0.2
% as default.
%


%% threshold
if nargin==2, h=0.2; end

z=hist(x,10);
%% cutting
ymax=max(y);
xnew=[];
ynew=[];
for n=1:length(x)
    if y(n)>ymax*h;
        xnew=[xnew,x(n)];
        ynew=[ynew,y(n)];
    end
end

%% fitting
ylog=log(ynew);
xlog=xnew;
p=polyfit(xlog,ylog,2);
A2=p(1);
A1=p(2);
A0=p(3);
sigma=sqrt(-1/(2*A2));
mu=A1*sigma^2;
A=exp(A0+mu^2/(2*sigma^2));

return;