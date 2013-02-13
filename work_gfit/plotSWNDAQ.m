% process scan (*scan.txt) and measurement data (*meas.txt)
% and plot figures

% sshfrommatlabinstall('DOWNLOAD')

clear all;
fnamescan='refscan.txt';
fnamemeas='refmeas.txt';

localFolder='E:\Beagle\Eclipseworkspace\MatlabCoder_1b\work_gfit';
remotefilename=strcat('/home/ubuntu/Loadmon_BeaglePlus/',fnamescan);
fprintf('Fetch remote file %s\n', remotefilename);
scptomatlab('ubuntu','10.2.1.239','temppwd',localFolder,remotefilename);

plotscandata(fnamescan);

%% plot measurement data *meas.txt
remotefilename=strcat('/home/ubuntu/Loadmon_BeaglePlus/',fnamemeas);
fprintf('Fetch remote file %s\n', remotefilename);
scptomatlab('ubuntu','10.2.1.239','temppwd',localFolder,remotefilename);

plotdaqdata(fnamemeas);
grid on;
%% process data collected via AccessPort
%  1. send 'swn pos1 pos1 nSam' in Accessport SENT Window
%  2. save the received data string to file data_ap.txt
%  3. open the file data_ap.txt and remove the firs line 'swn xx xx xx'
%  4. save the modified file
%  5. call plotdatadata('data_ap.txt') to plot the mean value
plotdaqdata('data_ap.txt');
grid on;
