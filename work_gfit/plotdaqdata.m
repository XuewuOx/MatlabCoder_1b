function [meanIR, meanUV]=plotdaqdata(fname,fdir)
% step 1. insert dataIRUV=[ into *.m file captured by accessport
% step 2. rung the *.m file to save the UVIR data into a matrix dataUVIR
if (nargin==2)
    ffullname=strcat(strcat(fdir,'\'),fname);
    dd=importdata(ffullname);
else
    ffullname=fname;
    dd=importdata(fname);
end;

dataIRUV=dd.data;
[nRow,nCol]=size(dataIRUV);
dataMS=dataIRUV(:,1);
dataIR=dataIRUV(:,2:2:nCol-1);
dataUV=dataIRUV(:,3:2:nCol);

fprintf('reading dataIRUV from %s successes, %d lines (%d-%d steps).\n',...
    ffullname, nRow,dataMS(1), dataMS(length(dataMS)));

% % data processing
 meanIR=mean(dataIR,2);
 meanUV=mean(dataUV,2);
 
%   % % plot raw data 
    figure('name',fname);
    fprintf('  dataIR_mean=%s\n',num2str(meanIR));
    fprintf('  dataUV_mean=%s\n',num2str(meanUV));
    plot(dataIR,'.-r');
    hold on;
    plot(dataUV,'o-b');
    title(fname); 
    title(sprintf('%s at MS=%d \n E(IR)=%4.1f, E(UV)=%4.1f ',fname,dataMS(1), meanIR, meanUV), ...
        'Interpreter','none','fontsize', 14);
    
    xlabel('time (ms)','fontsize',12); ylabel('IR/UV (mv)', 'fontsize',12);
    fprintf('plot UVIR data OK\n');





