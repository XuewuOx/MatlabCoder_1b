function [optIR, optUV]=plotscandata(fname,fdir,fighandle)
% step 1. insert dataIRUV=[ into *.m file captured by accessport
% step 2. rung the *.m file to save the UVIR data into a matrix dataUVIR
global datagfit
if (nargin>=2)
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
    ffullname,nRow,dataMS(1), dataMS(length(dataMS)));

% % data processing
 dataIR_mean=mean(dataIR,2);
 dataUV_mean=mean(dataUV,2);
 % %  plot raw data
 figure('name',strcat(fname, '(raw)'));
 if dataMS(1) <  dataMS(nRow)
    xid=[dataMS(1):2/(nCol-1):dataMS(nRow)+1-2/(nCol-1)];
 else
    xid=[dataMS(1):-2/(nCol-1):dataMS(nRow)-1+2/(nCol-1)];
 end
 dir=dataIR';
 plot(xid,dir(:),'.-r');
 duv=dataUV';
 hold on; plot(xid,duv(:),'o-b');
 
 title(sprintf('%s (raw), %d samples per step, \n scan from %d to %d', ...
    fname, (nCol-1)/2, dataMS(1), dataMS(nRow)), 'fontsize',12);
grid on;
xlabel('Step+samples');
ylabel('IR/UV');
 
%   % % plot mean data 
if (nargin==3)
    figure(fighandle);
else
    figure('name',fname);
end;
    
    % fprintf('  dataIR_mean=%s\n',num2str(dataIR_mean'));
    % fprintf('  dataUV_mean=%s\n',num2str(dataUV_mean'));
    plot(dataMS, dataIR_mean,'.-r');
    hold on;
    plot(dataMS, dataUV_mean,'o-b');
    title(fname); 
    xlabel('Motor steps','fontsize',12); ylabel('IR/UV (mv)', 'fontsize',12);
    fprintf('plot UVIR data OK\n');

    % % gaussian fitting over UV
    fprintf('Gaussian fit over dataUV');
    muUV=-9999;
    [sigmaUV, muUV, AUV] = gfit(dataMS,dataUV_mean,0.2);
    % plot gaussian fitting results
    muUV=round(muUV);
    fprintf('... OK.\n optimal postion of UV(step) is %04d (mu=%f, sigma=%f, A=%f)\n',...
         muUV,muUV, sigmaUV, AUV);
    y_gf=AUV*exp(-(dataMS-muUV).^2/(2*sigmaUV^2));
    plot(dataMS,y_gf,'.-m');
    stem(muUV,AUV,'sk');
    if (exist('datagfit.pkUV'))
        datagfit.pkUV=[datagfit.pkUV;  muUV];
        datagfit.UVg=[datagfit.UVg;  AUV];
    end;

    
% % gaussian fitting over IR
    fprintf('Gaussian fit over dataIR');
    muIR=-9999;
    [sigmaIR, muIR, AIR] = gfit(dataMS,dataIR_mean,0.2);
    muIR=round(muIR);
    % plot gaussian fitting results
    fprintf('... OK.\n optimal postion of IR(step) is %04d (mu=%f, sigma=%f, A=%f)\n',...
         muIR,muIR, sigmaIR, AIR);
    y_gf=AIR*exp(-(dataMS-muIR).^2/(2*sigmaIR^2));
    plot(dataMS,y_gf,'.-g');
    stem(round(muIR),AIR,'sg');
    title(sprintf('%s (MS: %d to %d) \n (IR)=[%d, %7.2f], (UV)=[%d,%7.2f] [pk,A]',...
        fname,dataMS(1),dataMS(nRow), round(muIR),AIR, round(muUV), AUV), ...
        'Interpreter','none','fontsize', 14);
    grid on;
    
    if(exist('datagfit.pkIR'))
        datagfit.pkIR=[datagfit.pkIR;  muIR];
        datagfit.IRg=[datagfit.IRg;  AIR];
    
        datagfit.file{length(datagfit.IRg)}=fname;
    end;
% return the optimal step 
fprintf('optimal step: (UV)%d, (IR) %d\n',round(muUV),round(muIR));
optUV=round(muUV);
optIR=round(muIR);



