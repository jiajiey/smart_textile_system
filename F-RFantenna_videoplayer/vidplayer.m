%Video play control and F-RF antenna 


function vidplayer()
 
%Initialize arduino
clear all;
delete(instrfindall);
arduino=serial('COM19','BAUD', 9600);
fopen(arduino);
%}
 
reading=0;
 
%Initilize video player
set(0,'defaultfigurecolor',[0 0 0]);
figure( 'Position', [100 400 300 200]);
hvid= actxcontrol('WMPlayer.OCX.7', [0 0 300 200]) ;
hvid.currentMedia =hvid.newMedia('rfimage.mp4'); % Create Media object
 hvid.Controls.pause;
lastreading=0;
 
 
while 1
    checkreading();
    
%    check rf reading
 
    pause(0.01);
    switch reading
        
        case 32
            %rf antenna
            
            
            hvid.Controls.currentPosition = 0;
            hvid.Controls.play;
            hvid.Controls.pause;
            
        case 64
            
            hvid.Controls.currentPosition = 1.5;
            hvid.Controls.play;
            hvid.Controls.pause;
            
        case 96
            
            hvid.Controls.currentPosition=2.5;
            hvid.Controls.play;
            hvid.Controls.pause;
            
        case 128
            
            hvid.Controls.currentPosition = 3.5;
            hvid.Controls.play;
            hvid.Controls.pause;
            
        case 160
            
            hvid.Controls.currentPosition = 4.5;
            hvid.Controls.play;
            hvid.Controls.pause;
            
        case 192
            
            hvid.Controls.currentPosition = 5.5;
            hvid.Controls.play;
            hvid.Controls.pause;
            
        case 224
            
            hvid.Controls.currentPosition = 6.5;
            hvid.Controls.play;
            hvid.Controls.pause;
            
        otherwise
            
            
    end
    
    
end
 
 
    function checkreading()
      %  read data from arduino
         reading = fscanf(arduino);
          reading=char(reading);
          reading=str2num(reading)
        
        if isempty(reading)
            
            reading=0;
            
        end
        
        
        
    end
end
