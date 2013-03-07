function plotdatalog()
%%  plot datalog.txt file
global fdata;
fdata='datalog_20130307.txt';
localFolder='E:\Beagle\Eclipseworkspace\MatlabCoder_1b\work_gfit\datafile';
remotefilename=strcat('/home/ubuntu/Loadmon_BeaglePlus/data/',fdata);

fprintf('Fetch remote file %s\n', remotefilename);
scptomatlab('ubuntu','10.2.1.239','temppwd',localFolder,remotefilename);
fprintf('\n');

localfile=strcat(strcat(localFolder,'\'),fdata);
dlog=importdata(localfile, '\t');
[nRow,nCol]=size(dlog);



hh=dlog.data(:,1); mmin=dlog.data(:,2); ssec=dlog.data(:,3);
IRref=dlog.data(:,8);
UVref=dlog.data(:,9);
pkIRref=dlog.data(:,10);
pkUVref=dlog.data(:,11);
tempC=dlog.data(:,26);
apdbv=dlog.data(:,27);
aomv=dlog.data(:,28);

sInterval=60;% second
hhdiff=diff(hh);
hhdiffid=find(hhdiff);
startid=hhdiffid(1)+1;
starthh=hh(startid);

nHour=length(hhdiffid);

hhlast = find(hhdiff,1,'last')
endid=hhlast+1;
endhh=hh(endid);
hhsym=num2str([starthh:endhh]');
hhid=linspace(startid,endid,nHour);

figure('name',strcat('TempC,APDbv, aomv_',fdata));
subplot(3,1,1);
plot(tempC,'.-r');
grid on;
xlabel('Time (Hour)');
ylabel('Temperature (degC)');
set(gca,'XTick',hhid)
set(gca,'XTickLabel',hhsym)
titleStr={'Temperature Measurement and Compensation',fdata};
title(titleStr,'Interpreter','none','fontsize', 14);

subplot(3,1,2);
plot(apdbv,'.-r');  title('Expected APD bias voltage');
xlabel('Time (Hour)'); ylabel('APD bias voltage (V)'); grid on;
set(gca,'XTick',hhid); set(gca,'XTickLabel',hhsym);

subplot(3,1,3);
plot(aomv,'.-b');  title('Analogue output to be set');
xlabel('Time (Hour)'); ylabel('analogue output (mV)'); grid on;
set(gca,'XTick',hhid); set(gca,'XTickLabel',hhsym);
% plotIRrefpkIRref(IRref, pkIRref,'IRref','pkIRref');

%% function plotIRrefpkIRref(IRref, pkIRref,sName1,sName2) 
% IRref & pkIRref
global fdata;
figure('name','RRref pkIRref');
idInvalidpkIRref=find(pkIRref==0);
idInvalidIRref=find(IRref==-9999);
IRref(idInvalidIRref)=NaN;

subplot(2,1,1);
plot(IRref,'.-r');
titleStr={'IRref and pkIRref',fdata};
title(titleStr,'Interpreter','none','fontsize', 14);
xlabel('Time (Hour)'); ylabel('IRref'); grid on;
set(gca,'XTick',hhid); set(gca,'XTickLabel',hhsym);

subplot(2,1,2);
plot(pkIRref,'.-r');
title('pkIRref');
xlabel('Time (Hour)'); ylabel('pkIRref'); grid on;
set(gca,'XTick',hhid); set(gca,'XTickLabel',hhsym);

% UVref & pkUVref
%% function plotUVrefpkUVref() 
figure('name','UVref pkUVref')
idInvalidpkUVref=find(pkUVref==0);
idInvalidUVref=find(UVref==-9999);
UVref(idInvalidUVref)=NaN;

subplot(2,1,1);
plot(UVref,'.-r');
titleStr={'UVref and pkUVref',fdata};
title(titleStr,'Interpreter','none','fontsize', 14);
xlabel('Time (Hour)'); ylabel('UVref'); grid on;
set(gca,'XTick',hhid); set(gca,'XTickLabel',hhsym);

subplot(2,1,2);
plot(pkUVref,'.-r');
title('pkUVref');
xlabel('Time (Hour)'); ylabel('pkUVref'); grid on;
set(gca,'XTick',hhid); set(gca,'XTickLabel',hhsym);