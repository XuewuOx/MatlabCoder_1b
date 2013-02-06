function y = readfile(filename) %#codegen

% The 'fprintf' function will not be compiled and instead passed
% to the MATLAB runtime. If we choose to generate code for this example,
% all calls to extrinsic functions are automatically eliminated.
coder.extrinsic('fprintf');
coder.extrinsic('num2str');
coder.extrinsic('plot');
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
    y=-1;
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
buffer = zeros(1,bufSIZE,'uint8');
bufline=zeros(1,65536,'uint8');
strline=zeros(1,1024,'uint8');
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

for nline=1:2
   fprintf('line %d, ',nline);
   coder.ceval('fgets',coder.ref(bufline(1)), int32(1024),f);  
   nChar=coder.ceval('strlen',coder.ref(bufline(1)));
   fprintf('(%d)="%s',nChar,bufline(1:nChar)); 
%    [n strline]=readLine(bufline,f);   
%     fprintf('(%d)="%s"\n',nChar,strline(1:n)); 
end;

nline=nline+1; fprintf('line %d, ',nline);
nVar=coder.ceval('fscanf',f, ...
    ['%cSWN posA=%d, posB=%d, nSteps=%d, nSam=%d, Fs=%d' 13 10], ...
        coder.ref(char100), coder.ref(posA), coder.ref(posB), ...
        coder.ref(nStep), coder.ref(nSam),coder.ref(nFs));
 if (nVar~=6)
      fprintf('ERROR: fscanf cannot read formatted line %d. Inncorrect format\n', nline);
      coder.ceval('fclose', f);
      y=-1; 
      return;
 end;
 fprintf('nVar=%d, posA=%d, posB=%d, nStep=%d, nSam=%d, Fs=%d\n', ...
            nVar,posA, posB, nStep, nSam, nFs);

for nline=4:6
   fprintf('line %d, ',nline);
   coder.ceval('fgets',coder.ref(bufline(1)), int32(1024),f);  
   nChar=coder.ceval('strlen',coder.ref(bufline(1)));
   fprintf('(%d)="%s',nChar,bufline(1:nChar)); 
end;

% sscanf(bufline(1:nChar),'swing LED from A=%d',posA);
% fprintf('posA=%d\n',posA);


% read data from 7-th line now
dataMS=zeros(nStep,1,'int32');
% k=nStep;
dataIR=zeros(nStep,500,'uint32');
dataUV=zeros(nStep,500,'uint32');
xir=uint32(0);
xuv=uint32(0);
k=1;

% read data
for k=1:nStep
    nline=nline+1; fprintf('line %d, ',nline);
    % read motor step data
    nVar=coder.ceval('fscanf',f, ['%d '],coder.ref(k4step));
    fprintf('nVar=%d, nStep=%d \n', nVar,k4step);
    dataMS(k)=k4step;

    % read IR UV data
    for i=1:nSam
        nVar=coder.ceval('fscanf',f, [' %d %d'],coder.ref(xir), coder.ref(xuv));
        if (nVar~=2)
            fprintf('ERROR: fscanf cannot read formatted line %d. Inncorrect format\n', nline);
            coder.ceval('fclose', f);
            y=-1; 
            return;
        end;
        dataIR(k,i)=xir;
        dataUV(k,i)=xuv;
    end;
    
    % display the dataIR and dataUV
    fprintf('dataIR(%d,:)=%s\n',k,num2str(dataIR(k,1:nSam)));
    fprintf('dataUV(%d,:)=%s\n',k,num2str(dataUV(k,1:nSam)));

    % move to the end of line for next reading 
    % coder.ceval('fgets',coder.ref(bufline(1)), int32(1024),f); 
    
   coder.ceval('fgets',coder.ref(bufline(1)), int32(1024),f);  
   nChar=coder.ceval('strlen',coder.ref(bufline(1)));
   % fprintf('left %d chars="%s',nChar,bufline(1:nChar)); 
   fprintf('left %d chars="',nChar);
   for i=1:nChar
       fprintf(' %02H',bufline(i));
   end;
   fprintf('"\n');
%     [n strline]=readLine(bufline,f);
%     if (n<=0)
%         y=-1;
%         return;
%     end;
%     fprintf(' (%d left = "%s")\n',n, strline(1:n));
end;
    
% Close file
coder.ceval('fclose', f);


y=1; 
return;

nChar=coder.ceval('strlen',coder.ref(buffer(1)));
fprintf('line %d (%d)="%s"\n',nline,nChar,buffer(1:nChar)); 



nline=nline+1;

[n strline]=readLine(bufline,f);
if (n<=0)
    y=0;
    return;
end;
fprintf('line %d (%d)="%s"',nline, n, strline(1:n));
y=1;
return;
while remaining > 0
   % nVar=coder.ceval('fscanf','%s\r\n',coder.ref(buffer(index)));
   % fprintf('%s \r\n',
    % Buffer overflow?
    if remaining + index > size(buffer,2)
        fprintf('Attempt to read file which is bigger than internal buffer.\n');
        fprintf('Current buffer size is %d bytes and file size is %d bytes.\n', size(buffer,2), filelen);
        break
    end
    
    % Read as much as possible from the file into internal buffer
    n = int32(0);
    intpchar=int32(0);
    nline=nline+1;
    % n = coder.ceval('fread', coder.ref(buffer(index)), int32(1), remaining, f);
    
  
    % Print out one line string 
    % fprintf('line %d (%d)= \n', nline, n); % by matlab fprintf
    %   % by calling ceval()
    % coder.ceval('printf', ['line %d (%d chars)="%s"' 13 10 00],nline, n, coder.ref(bufline(1)));
    %   % by converting into matlab int matrix
    
    x=int32(0);
    fprintf('%c%c%c',char(bufline(1:3)));
    x=coder.ceval('atoi',c_string(bufline(3:6)));
    % nStep=str2num(char(bufline(3:6)));
    fprintf('%d=',nStep);
    nCol=10; iCol=10;
    while(iCol<n)
       % fprintf(' %d',str2num(char(bufline(iCol:iCol+6))));
        iCol=iCol+6;
    end;
    
%     y = char(bufline(1:n));
%     for k=1:n
%         fprintf('%c',y(k));
%     end;
     
    % Update state variables
    remaining = remaining - n;
    index = index + n;
end
 


% Close file
coder.ceval('fclose', f);

y = char(buffer(1:index));

% Create a NUL terminated C string given a MATLAB string
function y = c_string(s)
y = [s 0];

% Create a \NL\CR+NUL terminated C string given a MATLAB string
function y = c_stringCR(s)
y = [s 13 10 0];

function [nChar strline]=readLine(bufline,f)

    coder.extrinsic('fprintf');
    nChar=int32(-1);
    
    pchar = coder.opaque('char *');
    intpchar=int32(0);
   % pchar=coder.ceval('fgets',coder.ref(buffer(index)), int32(1024),f);
   
   pchar=coder.ceval('fgets',coder.ref(bufline(1)), int32(1024),f);
   intpchar=coder.ceval('(int)',pchar);
  % fprintf('intpchar= pchar = %d \n',intpchar);
   
    if intpchar == 0
        % Nothing more to read
        fprintf('Nothing more to read.\n');
        nChar=intpchar;
        strline=[uint8(0) uint8(0)];
        return;
    end
    
    % Did something went wrong when reading?
    if intpchar < 0
        fprintf('Could not read from file.\n');
        nChar=intpchar;
        strline=[uint8(0) uint8(0)];
        return;
    end
    nChar=coder.ceval('strlen',coder.ref(bufline(1)));
    strline=[bufline(1:nChar) uint8(0)]; % terminate with 0
    % nChar=nChar+1;
return;
    
