%F-energy

clear all;

%Create the bar chart
y = [0 0 0 0 0 0 0 0; 0 0 0 0 0 0 0 0;10 5 5 5 5 5 5 12;0 0 0 0 0 0 0 0;0 0 0 0 0 0 0 0];
b=barh(y,'stacked');

%Make edges invisible
for i=1:1:8
    b(i).EdgeColor='none';
end

%Assigned the right color to the bar
b(1).FaceColor = [1 1 1];
b(7).FaceColor = [1 0 0];
b(6).FaceColor = [1 0.5 0];
b(5).FaceColor = [1 1 0];
b(4).FaceColor = [0.8 1 0];
b(3).FaceColor = [0.5 1 0];
b(2).FaceColor = [0 1 0];
b(8).FaceColor = [1 1 1];

%Hide all the bars, and show the suitable bars that is charged
for i=1:1:8
    alpha(b(i),0);
end
hold on


%Load background image
I =  flipud(imread('discharge.png'));
I2=flipud(imread('charge.png'));
%I = imread('battery.png');
h = image([0 60],[0 6],I);
h2=image([0 60],[0 6],I2);

axis tight;
uistack(b,'top');
drawnow;


arduino=serial('COM3','BAUD', 9600);
fopen(arduino);


while(1)
    matlabreading = fscanf(arduino);
    reading=char(matlabreading);
    reading=str2num(reading);
    
    if reading>=128
        
        reading=reading-128;
        uistack(h,'bottom');
    else
        
        uistack(h2,'bottom');
    end
    
    
    
    %Hide all the bars, and show the suitable bars that is charged
    for i=1:1:8
        alpha(b(i),0);
    end
    
    %Change the charging status
    for i=7:-1:9-reading
        alpha(b(i),1);
        
    end
    
    %for stability
    pause(0.01);
    drawnow;
    
    
end
