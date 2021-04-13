%F-touch sensor

clear all;
delete(instrfindall);
arduino=serial('COM28','BAUD', 9600);

fopen(arduino);


data = [1,1,1,1,1;1,1,1,1,1;1,1,1,1,1;1,1,1,1,1;1,1,1,1,1;1,1,1,1,1];
row=[1 5];
col=[1 6];
im=imagesc(row,col,data);
hold on;
map = [0 0 1;1 1 1 ];
colormap(map)
titlename={
    'Fan ON',   'Light ON', 'Blinds Up',    'Aircon ON',    'Curtain Open';
    'Fan OFF',  'Light OFF','Blinds Down',  'Aircon OFF',   'Curtain Close';
    'Sprinkler ON', 'Hi Siri',  'Temp Up',  'ECG ON',   'Volume Up';
    'Sprinkler OFF',    'OK Google',    'Temp Down',    'ECG OFF',  'Volume Down';
    'Door Lock',    'Hey Cortana',  'TV ON',    'Camera ON',    'Screen Out';
    'Door Unlock',  'Hi Bixby', 'TV OFF',   'Camera OFF',   'Turn OFF ALL'
    };

axis off

while(1)
    
    matlabreading = fscanf(arduino);
    
    reading=char(matlabreading);
    reading=str2num(reading);
    maxrow=bitshift(reading,-4);
    maxcol=reading-bitshift(maxrow,4);
    disp(maxrow);
    disp(maxcol);
    
    title( 'No touch','FontSize', 24);
    
    data = [1,1,1,1,1;1,1,1,1,1;1,1,1,1,1;1,1,1,1,1;1,1,1,1,1;1,1,1,1,1];
    if maxrow~=0
        data(maxrow,6-maxcol)=[-1];
        
        title( [titlename(maxrow,6-maxcol)],'FontSize', 24);
        
    end
    
    
    set(im, 'CData', data);
    drawnow;
    
end
