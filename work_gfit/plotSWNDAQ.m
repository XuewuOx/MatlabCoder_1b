% process scan (*scan.txt) and measurement data (*meas.txt)
% and plot figures

% sshfrommatlabinstall('DOWNLOAD')

clear all;
fnamebase='ref';
fnamescan=strcat(fnamebase,'scan.txt');
fnameir=strcat(fnamebase,'ir.txt');
fnameuv=strcat(fnamebase,'uv.txt');


fnamescan='dump/refscan_20130307_13h53m09s.txt';
fnameir='dump/refir_20130307_13h53m09s.txt';
fnameuv='dump/refuv_20130307_13h53m09s.txt';


localFolder='E:\Beagle\Eclipseworkspace\MatlabCoder_1b\work_gfit\datafile';
remotefilename=strcat('/home/ubuntu/Loadmon_BeaglePlus/',fnamescan);
fprintf('Fetch remote file %s\n', remotefilename);
scptomatlab('ubuntu','10.2.1.239','temppwd',localFolder,remotefilename);

plotscandata(fnamescan,'.\datafile');

%% plot measurement data *ir/*uv.txt

% fnameir=strcat(fnamebase,'ir3.txt');
% fnameuv=strcat(fnamebase,'uv.txt');
% fnameir='fname.txt';
% fnameuv='dump/refuv_20130307_00h25m04s.txt';
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

% plotdaqdata('data_ap.txt');
% grid on;



