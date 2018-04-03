clear, clc % clears previous values
tic % starts time counter
G = 9.81; % acceleration due to gravity in m/s^2
SeaDensity = 1.225; % air density at sea level
TimeDelta = .01; % itteration time for flight path
CDBrake = 1.28; % coefficient of drag of the airbrakes
CDRocket = .42; % coefficient of drag of the rocket
AreaRocket = .0182414692; % drag area of the rocket
AreaBrake = .00692; % drag area of the airbrakes
StartAlt = 1219.2; % launch altitude
WeightF = 354.256; % weight after burnout
Mass = WeightF / G; % mass after burnout
Matrix = zeros(300,2449); % matrix of appogee heights
x = zeros(1,2449); % vector of brake heights
y = zeros(1,300); % vector of brake velocities
HeightGood = zeros(1,547); % vector of brake heights that are "good"
VelocityGood = zeros(1,547); % vector of brake velocitiess that are "good"
HeightVelocityGood = zeros(2,547); % matrix of both brake height and velocities that are "good"
HeightGood1 = zeros(1,333);
VelocityGood1 = zeros(1,333);
HeightVelocityGood1 = zeros(2,333);
HeightGood2 = zeros(1,200);
VelocityGood2 = zeros(1,200);
HeightVelocityGood2 = zeros(2,200);
c = 1; % its just a counter for later matrices
d = 1;
for i = 600:3048 % 2449 values for brake heights
    for j = 1:300 % 300 values for brake velocities
        Velocity = j; % brake velocity 
        Time = 0; % time since brake deployment
        Altitude = StartAlt + i; % altitude from sea level
        while Velocity >= 0 % loops until apogee
            Altitude = Altitude + (Velocity * TimeDelta); % calculates altitude based one velocity
            Height = Altitude - StartAlt; % calculates height from altitude
            Density = SeaDensity * (1 + (-.0065 * Altitude / 287))^(4.25363734); % calculates density at altitude
            Drag = .5 * Density * Velocity * Velocity * CDRocket * AreaRocket; % calculates rocket drag
            Brake = .5 * Density * Velocity * Velocity * CDBrake * AreaBrake; % calculates air brake drag
            if Time < 3 % if the airbrakes are still opening
                Brake = (Brake / 3) * Time; % the drag force of the airbrakes is a fraction of its full force
            end
            Force = -Drag - Brake - WeightF; % calculates force from the components
            Velocity = Velocity + (Force * TimeDelta / Mass); % calculates velocity due to force
            Time = Time + TimeDelta; % time since airbrake deployment
        end
        Matrix(j,i-599) = Height; % stores the apogee value 
        y(1,j) = j; % stores the velocity at time of airbrake deployment
        if (Height>3047) && (Height<3049) % if the apogee was within goal values
            HeightGood(1,c) = i; % stores the airbrake deployment value 
            VelocityGood(1,c) = j; % stores the airbrake deployment velocity
            HeightVelocityGood(1,c) = i; % stores the airbrake deployment value 
            HeightVelocityGood(2,c) = j; % stores the airbrake deployment velocity
            if (i<=2500)
                HeightGood1(1,c) = i;
                VelocityGood1(1,c) = j;
                HeightVelocityGood1(1,c) = i;
                HeightVelocityGood1(2,c) = j;
            end
            if (i>2500)
                HeightGood2(1,d) = i;
                VelocityGood2(1,d) = j;
                HeightVelocityGood2(1,d) = i;
                HeightVelocityGood2(2,d) = j;
                d = d + 1;
            end
            c = c + 1;
        end
    end
    x(1,i-599) = i; % stores the height at time of airbrake deployment
end
%HeightGood(250:581) = []; % Cuts the HeightGood Matrix down to 950 values to give a better linear fit for the data
%VelocityGood(250:581) = []; % Cuts the VelocityGood Matrix down to 950 values to give a better linear fit for the data
mesh(x,y,Matrix) % plots all of the apogee values
colorbar 
xlabel('brake height'); % labels the  axis
ylabel('velocity'); % labels the y axis
zlabel('end height'); % labels the z axis
title('end height as a function of brake height, and velocity'); % titles the graph
figure % makes a new figure
plot(HeightGood,VelocityGood) % plots the "good" pairs of deployment height and velocity
xlabel('Brake Height m'); % labels the x axis
ylabel('Brake Velocity m/s'); % labels the y axis
title('Height & Velocity Pairs That Get Us Close'); % titles the graph
figure % makes a new figure
plot(HeightGood1,VelocityGood1) % plots the "good" pairs of deployment height and velocity
xlabel('Brake Height m'); % labels the x axis
ylabel('Brake Velocity m/s'); % labels the y axis
title('Height & Velocity Pairs That Get Us Close section 1'); % titles the graph
figure % makes a new figure
plot(HeightGood2,VelocityGood2) % plots the "good" pairs of deployment height and velocity
xlabel('Brake Height m'); % labels the x axis
ylabel('Brake Velocity m/s'); % labels the y axis
title('Height & Velocity Pairs That Get Us Close section 2'); % titles the graph
toc % ends time counter
