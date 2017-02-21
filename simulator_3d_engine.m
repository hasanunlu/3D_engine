%Simple 3D rotations and 2D projection
close all;
clear;

%Cube Definition in 3D
%Thing object center is origin and cube size is 1 unit
%Point list
object(1,:)=[ 0.5  0.5  0.5];
object(2,:)=[ 0.5  0.5 -0.5];
object(3,:)=[ 0.5 -0.5  0.5];
object(4,:)=[ 0.5 -0.5 -0.5];
object(5,:)=[-0.5  0.5  0.5];
object(6,:)=[-0.5  0.5 -0.5];
object(7,:)=[-0.5 -0.5  0.5];
object(8,:)=[-0.5 -0.5 -0.5];

%Point connections
edges=zeros(8,8);

edges(1,2)=1;
edges(1,3)=1;
edges(1,5)=1;

edges(2,1)=1;
edges(2,6)=1;
edges(2,4)=1;

edges(3,1)=1;
edges(3,4)=1;
edges(3,7)=1;

edges(4,8)=1;
edges(4,3)=1;
edges(4,2)=1;
edges(5,1)=1;

edges(5,1)=1;
edges(5,6)=1;
edges(5,7)=1;

edges(6,5)=1;
edges(6,2)=1;
edges(6,8)=1;

edges(7,3)=1;
edges(7,5)=1;
edges(7,8)=1;

edges(8,4)=1;
edges(8,6)=1;
edges(8,7)=1;


tethaX=pi/4;
Rx=[1 0 0; 0 cos(tethaX) -sin(tethaX); 0 sin(tethaX) cos(tethaX)];

tethaY=pi/3;
Ry=[cos(tethaY) 0 sin(tethaY); 0 1 0; -sin(tethaY) 0 cos(tethaY)];

tethaZ=pi/8;
Rz=[cos(tethaZ) -sin(tethaZ) 0; sin(tethaZ) cos(tethaZ) 0; 0 0 1];

for i=1:8
   object(i,:)=(Rx*Ry*Rz*object(i,:)')'; 
end

figure;
for i=1:8
   for j=(i+1):8
       if i ~= j 
            if edges(i,j) == 1
               
               pts = [object(i,:); object(j,:)];
               line(pts(:,1), pts(:,2), pts(:,3));
               
            end
       end
   end 
end 
xlim([-2 2]);
ylim([-2 2]);
zlim([-2 2]);
xlabel('WORLD COORDS');


figure;
for i=1:8
   for j=(i+1):8
       if i ~= j 
            if edges(i,j) == 1
               
               %Projection pick x and y axis of world coordinates
               p1=[object(i,1), object(j,1)];
               p2=[object(i,2), object(j,2)];
               
               line(p1,p2);
               
            end
       end
   end 
end 

xlim([-2 2]);
ylim([-2 2]);
zlim([-2 2]);
xlabel('2D PROJECTED COORDS looking from Z');
