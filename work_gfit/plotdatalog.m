% function plotdatalog()
%% install the ssh package

sshfrommatlabinstall();
%%  download datalog.txt file(s)

fdata='datalog_20130322.txt';
remotefilename=strcat('/home/ubuntu/Loadmon_BeaglePlus/data/',fdata);
localFolder='E:\Beagle\Eclipseworkspace\MatlabCoder_1b\work_gfit\datafile';
localfilename=strcat(strcat(localFolder,'\'),fdata);

fprintf('Fetch remote file %s\n', remotefilename);
scptomatlab('ubuntu','10.2.1.239','temppwd',localFolder,remotefilename);
fprintf('\n DONE!\n');



dlogDay=importdata(localfilename, '\t');
dlogDay.data(1:2,:)=[];

%% combine several datalog.txt files
% for 1st file
dlog=dlogDay;

% for 2nd file and so on
% dlog.data=[dlog.data; dlogDay.data];

%% Extract data from file structure
[nRow,nCol]=size(dlog);
% dlog.data(16,:)=[];
% [colx,rowx]=find(dlog.data==0);
% dlog.data(colx,rowx)=NaN;
% [colx,rowx]=find(dlog.data==-9999);
% dlog.data(colx,rowx)=NaN;

hh=dlog.data(:,1); mmin=dlog.data(:,2); ssec=dlog.data(:,3);
IRnorm=dlog.data(:,4);
UVnorm=dlog.data(:,5);
IRref=dlog.data(:,8);
UVref=dlog.data(:,9);
pkIRref=dlog.data(:,10);
pkUVref=dlog.data(:,11);

IRwtr=dlog.data(:,12);
UVwtr=dlog.data(:,13);
pkIRwtr=dlog.data(:,14);
pkUVwtr=dlog.data(:,15);

stdIRref=dlog.data(:,16);
stdUVref=dlog.data(:,17);
stdIRwtr=dlog.data(:,20);
stdUVwtr=dlog.data(:,21);




tempC=dlog.data(:,26);
apdbv=dlog.data(:,27);
aomv=dlog.data(:,28);

sInterval=60;% second
hhdiff=diff(hh);
hhdiffid=find(hhdiff);
hhid=hhdiffid+1;
hhsym=num2str(hh(hhid));
% hhid=linspace(startid,endid,nHour);
%% plot hour, minutes and seconds for tracking the data file
figure('name', 'Hour:Min:Sec');
subplot(3,1,1); plot(hh,'.-k'); set(gca,'XTick',hhid); set(gca,'XTickLabel',hhsym);
subplot(3,1,2); plot(mmin,'.-k'); set(gca,'XTick',hhid); set(gca,'XTickLabel',hhsym);
subplot(3,1,3); plot(ssec,'.-k'); set(gca,'XTick',hhid); set(gca,'XTickLabel',hhsym);
%% Plot temperature
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

%% plot IRref, pkIRref
% IRref & pkIRref
global fdata;
figure('name','IRref pkIRref');

subplot(3,1,1);
IRref=plotColumn(IRref,'IRref',hhid, hhsym, '.-r');
title(strcat(strcat('IRref & pkIRref',fdata),')'));
subplot(3,1,2);
pkIRef=plotColumn(pkIRref,'pkIRref',hhid, hhsym, '.-r');
subplot(3,1,3);
stdIRref=plotColumn(stdIRref,'stdIRref',hhid, hhsym, '.-g');

%% plot UVref & pkUVref
figure('name','UVref pkUVref')
subplot(3,1,1);
UVref=plotColumn(UVref,'UVref',hhid, hhsym, '.-b');
title(strcat(strcat('UVref & pkUVref',fdata),')'));
subplot(3,1,2);
pkUVref=plotColumn(pkUVref,'pkUVref',hhid, hhsym, '.-b');
subplot(3,1,3);
stdUVref=plotColumn(stdUVref,'stdUVref',hhid, hhsym, '.-g');


% plotyy IRref vs Tempc
figure('name', 'IRref vs TempC'); 
[hax, hplot1, hplot2]=plotyy([1:length(IRref)],IRref, [1:length(IRref)],tempC);
title('IRref vs TempC','Interpreter','none','fontsize', 14);
xlabel('Time (Hour)'); grid on;
set(hax(1),'XTick',hhid); set(hax(1),'XTickLabel',hhsym);
set(hax(2),'XTick',[]); set(hax(2),'XTickLabel',[]);
set(get(hax(1),'YLabel'),'String','IRref');
set(get(hax(2),'YLabel'),'String','TempC');

% plotyy UVref vs Tempc and APDbv
figure('name', 'IRref vs TempC'); 
subplot(2,1,1);
[hax, hplot1, hplot2]=plotyy([1:length(UVref)],UVref, [1:length(UVref)],tempC);
title('UVref vs TempC','Interpreter','none','fontsize', 14);
xlabel('Time (Hour)'); grid on;
set(hax(1),'XTick',hhid); set(hax(1),'XTickLabel',hhsym);
set(hax(2),'XTick',[]); set(hax(2),'XTickLabel',[]);
set(get(hax(1),'YLabel'),'String','UVref');
set(get(hax(2),'YLabel'),'String','TempC');
subplot(2,1,2);
plot(apdbv,'.-y');
xlabel('Time (Hour)'); ylabel('APDbv (V)');grid on;
set(gca,'XTick',hhid); set(gca,'XTickLabel',hhsym);

%% plot IRwtr, UVwtr, pkIRwtr, pkUVwtr
figure('name','IRwtr pkIRwtr')
subplot(3,1,1);
IRwtr=plotColumn(IRwtr,'IRwtr',hhid, hhsym, '.-r');
title(strcat(strcat('IRwtr & pkIRwtr',fdata),')'));
subplot(3,1,2);
pkIRwtr=plotColumn(pkIRwtr,'pkIRwtr',hhid, hhsym, '.-r');
subplot(3,1,3);
stdIRwtr=plotColumn(stdIRwtr,'stdIRwtr',hhid, hhsym, '.-r');


figure('name','UVwtr pkUVwtr')
subplot(3,1,1);
UVwtr=plotColumn(UVwtr,'UVwtr',hhid, hhsym, '.-b');
title(strcat(strcat('UVwtr & pkUVwtr',fdata),')'));
subplot(3,1,2);
pkUVwtr=plotColumn(pkUVwtr,'pkUVwtr',hhid, hhsym, '.-b');
subplot(3,1,3);
stdUVwtr=plotColumn(stdUVwtr,'stdUVwtr',hhid, hhsym, '.-r');

%% function UVnorm, IRnorm
figure('name','IRnorm UVnorm')

subplot(2,1,1);
IRnorm=plotColumn(IRnorm,'IRnorm',hhid, hhsym, '.-r');
title(strcat(strcat('IRnorm (',fdata),')'));

subplot(2,1,2);
UVnorm=plotColumn(UVnorm,'UVnorm',hhid, hhsym, '.-b');
title(strcat(strcat('UVnorm (',fdata),')'));


%% plot IRref, IRwtr, IRnorm
figure('name','IRref-wtr-norm')

subplot(3,1,1);
IRref=plotColumn(IRref,'IRref',hhid, hhsym, '.-r'); hold on;
plotColumn(IRref+stdIRref,'IRref',hhid, hhsym, '.-g');
plotColumn(IRref-stdIRref,'IRref',hhid, hhsym, '.-g');

title(strcat(strcat('IRref (',fdata),')'));

subplot(3,1,2);
IRwtr=plotColumn(IRwtr,'IRwtr',hhid, hhsym, '.-r'); hold on;
plotColumn(IRwtr+stdIRwtr,'IRwtr',hhid, hhsym, '.-g');
plotColumn(IRwtr-stdIRwtr,'IRwtr',hhid, hhsym, '.-g');
title(strcat(strcat('IRwtr (',fdata),')'));

subplot(3,1,3);
IRnorm=plotColumn(IRnorm,'IRnorm',hhid, hhsym, '.-r');
title(strcat(strcat('IRnorm (',fdata),')'));

%%
figure('name','UVref-wtr-norm')

subplot(3,1,1);
UVref=plotColumn(UVref,'UVref',hhid, hhsym, '.-b'); hold on;
title(strcat(strcat('UVref (',fdata),')'));
plotColumn(UVref+stdUVref,'UVref',hhid, hhsym, '.-g');
plotColumn(UVref-stdUVref,'UVref',hhid, hhsym, '.-g');

subplot(3,1,2);
UVwtr=plotColumn(UVwtr,'UVwtr',hhid, hhsym, '.-b'); hold on;
plotColumn(UVwtr+stdUVwtr,'UVwtr',hhid, hhsym, '.-g');
plotColumn(UVwtr-stdUVwtr,'UVwtr',hhid, hhsym, '.-g');
title(strcat(strcat('UVwtr (',fdata),')'));

subplot(3,1,3);
UVnorm=plotColumn(UVnorm,'UVnorm',hhid, hhsym, '.-b');
title(strcat(strcat('UVnorm (',fdata),')'));
%% plot x against time
% % x is a function of dlog.data
% figure;
% % x=pkUVref-pkIRref;
% strOP='pkUVref-pkUVwtr';
% x=eval(strOP);
% plotColumn(x,'strOP',hhid, hhsym, '.-r');
