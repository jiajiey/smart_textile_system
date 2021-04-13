%F-photodetector 
clear all;
delete(instrfindall);
arduino=serial('COM36','BAUD', 9600);
 
fopen(arduino);
 
 
data = [0,0;0,0;0,0;0,0];
row=[1 4];
col=[1 2];
im=imagesc(row,col,data);
hold on;
map = [1 0 0 ;1 1 1 ];
colormap(map)
 
 
 
while(1)
    
    matlabreading = fscanf(arduino);
    
    reading=char(matlabreading);
    reading=str2num(reading);
    
   
    data(1,1)=1-bitget(reading,1);
    data(2,1)=1-bitget(reading,2);
    data(3,1)=1-bitget(reading,3);
    data(4,1)=1-bitget(reading,4);
    
    data(1,2)=1-bitget(reading,5);
    data(2,2)=1-bitget(reading,6);
    data(3,2)=1-bitget(reading,7);
    data(4,2)=1-bitget(reading,8);
  
    %disp(data);
    
    set(im, 'CData', data);
    drawnow;
    
    
    
end
