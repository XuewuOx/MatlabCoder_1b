% process scan (*scan.txt) and measurement data (*meas.txt)
% and plot figures

% sshfrommatlabinstall('DOWNLOAD')

clear all;
fnamebase='ref';
fnamescan=strcat(fnamebase,'scan.txt');
fnameir=strcat(fnamebase,'ir.txt');
fnameuv=strcat(fnamebase,'uv.txt');

localFolder='E:\Beagle\Eclipseworkspace\MatlabCoder_1b\work_gfit\datafile';
remotefilename=strcat('/home/ubuntu/Loadmon_BeaglePlus/',fnamescan);
fprintf('Fetch remote file %s\n', remotefilename);
scptomatlab('ubuntu','10.2.1.239','temppwd',localFolder,remotefilename);

plotscandata(fnamescan,'.\datafile');

%% plot measurement data *ir/*uv.txt

% fnameir=strcat(fnamebase,'ir3.txt');
% fnameuv=strcat(fnamebase,'uv.txt');
% fnameir='wtr100.txt';
% fnameuv='wtr140uv2.txt';
remotefilename=strcat('/home/ubuntu/Loadmon_BeaglePlus/',fnameir);
fprintf('Fetch remote file %s\n', remotefilename);
scptomatlab('ubuntu','10.2.1.239','temppwd',localFolder,remotefilename);

remotefilename=strcat('/home/ubuntu/Loadmon_BeaglePlus/',fnameuv);
fprintf('Fetch remote file %s\n', remotefilename);
scptomatlab('ubuntu','10.2.1.239','temppwd',localFolder,remotefilename);


plotdaqdata(fnameir, '.\datafile');
grid on;
plotdaqdata(fnameuv,'.\datafile');
grid on;

%% process data collected via AccessPort
%  1. send 'swn pos1 pos1 nSam' in Accessport SENT Window
%  2. save the received data string to file data_ap.txt
%  3. open the file data_ap.txt and remove the firs line 'swn xx xx xx'
%  4. save the modified file
%  5. call plotdatadata('data_ap.txt') to plot the mean value
plotdaqdata('data_ap.txt');
grid on;


%%  plot datalog.txt file
fdata='datalog_20130306.txt';
localFolder='E:\Beagle\Eclipseworkspace\MatlabCoder_1b\work_gfit\datafile';
remotefilename=strcat('/home/ubuntu/Loadmon_BeaglePlus/data/',fdata);

fprintf('Fetch remote file %s\n', remotefilename);
scptomatlab('ubuntu','10.2.1.239','temppwd',localFolder,remotefilename);
fprintf('\n');

localfile=strcat(strcat(localFolder,'\'),fdata);
dlog=importdata(localfile, '\t');
[nRow,nCol]=size(dlog);



hh=dlog.data(:,1); mmin=dlog.data(:,2); ssec=dlog.data(:,3);
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
