clear, clc
G = 9.81;
SeaDensity = 1.225;
TimeDelta = .1;
CDBrake = 1;
CDRocket = .4;
AreaRocket = .0182414692;
AreaBrake = .0174;
StartAlt = 1219.2;
WeightF = 306.927;
Mass = WeightF / G;
Matrix=zeros(300,2349);
x=zeros(1,2349);
y=zeros(1,300);
for i = 700:3048 % height 2349
    for j = 1:300 % velocity 300
        Velocity = j;
        Time = 0;
        Altitude = StartAlt + i;
        while Velocity >= 0
            Altitude = Altitude + (Velocity * TimeDelta);
            Height = Altitude - StartAlt;
            Density = SeaDensity * (1 + (-.0065 * Altitude / 287))^(4.25363734);
            Drag = .5 * Density * Velocity * Velocity * CDRocket * AreaRocket;
            Brake = .5 * Density * Velocity * Velocity * CDBrake * AreaBrake;
            if Time < 2
                Brake = (Brake / 2) * Time;
            end
            Force = -Drag - Brake - WeightF;
            Velocity = Velocity + (Force * TimeDelta / Mass);
            Time = Time + TimeDelta;
        end
        Matrix(j,i-699) = Height;
        y(1,j) = j;
    end
    x(1,i-699) = i;
end
figure
surf(x,y,Matrix)
colorbar
xlabel('brake height');
ylabel('velocity');
zlabel('end height');
title('end height as a function of brake height, and velocity');