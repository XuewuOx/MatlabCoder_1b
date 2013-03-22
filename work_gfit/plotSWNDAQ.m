% process scan (*scan.txt) and measurement data (*meas.txt)
% and plot figures

sshfrommatlabinstall(); 
% clear all;
% global    datagfit
% datagfit.pkIR=[];
% datagfit.IRg=[];
% datagfit.pkUV=[];
% datagfit.UVg=[];
% datagfit.file=[];
% hfig=figure('name','Gfit');
%%
fnamebase='ref';

% for the data of latest test
fext='.txt';
remoteFolder='/home/ubuntu/Loadmon_BeaglePlus/';

  % for history data
%   remoteFolder='/home/ubuntu/Loadmon_BeaglePlus/dump/';
%   fext='_20130316_00h02m05s.txt';
 
fnamescan=strcat(strcat(fnamebase,'scan'),fext);
fnameir=strcat(strcat(fnamebase,'ir'),fext);
fnameuv=strcat(strcat(fnamebase,'uv'),fext);
localFolder='E:\Beagle\Eclipseworkspace\MatlabCoder_1b\work_gfit\datafile\dump';
 
%% get ???scan.txt and plot
remotefilename=strcat(remoteFolder,fnamescan);
fprintf('Fetch remote file %s\n', remotefilename);
scptomatlab('ubuntu','10.2.1.239','temppwd',localFolder,remotefilename);

 plotscandata(fnamescan,'.\datafile\dump');
%  plotscandata(fnamescan,'.\datafile\dump', hfig);

%% get ???ir.txt and plot
remotefilename=strcat(remoteFolder,fnameir);
fprintf('Fetch remote file %s\n', remotefilename);
scptomatlab('ubuntu','10.2.1.239','temppwd',localFolder,remotefilename);

plotdaqdata(fnameir, '.\datafile\dump');
grid on;

%% get ???uv.txt and plot
remotefilename=strcat(remoteFolder,fnameuv);
fprintf('Fetch remote file %s\n', remotefilename);
scptomatlab('ubuntu','10.2.1.239','temppwd',localFolder,remotefilename);
disp('File transfer Done!');

plotdaqdata(fnameuv,'.\datafile\dump');
grid on;

%% process data collected via AccessPort
%  1. send 'swn pos1 pos1 nSam' in Accessport SENT Window
%  2. save the received data string to file data_ap.txt
%  3. open the file data_ap.txt and remove the firs line 'swn xx xx xx'
%  4. save the modified file
%  5. call plotdatadata('data_ap.txt') to plot the mean value

% plotscandata('data_ap.txt','.\');
% grid on;
%% manual plot a data file

% localFolder='E:\Beagle\Eclipseworkspace\MatlabCoder_1b\work_gfit\datafile\dump';
% %remoteFolder='/home/ubuntu/Loadmon_BeaglePlus/';
% remoteFolder='/home/ubuntu/Loadmon_BeaglePlus/dump/';
% remotefilename='refS200H000ascan_20130317_19h07m03s.txt';
% fprintf('Fetch remote file %s\n', remotefilename);
% scptomatlab('ubuntu','10.2.1.239','temppwd',localFolder,remotefilename);
% disp('Done'); 
% plotscandata(fnamescan,'.\datafile\dump');
%  %%
% fnameir='wtrS025H000air_20130317_18h49m39s.txt';






