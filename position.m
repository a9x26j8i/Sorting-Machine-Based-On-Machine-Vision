function f=position(theta,position_x,position_y)
l1=117;
l2=140;
l3=160;
l4=50;
position_z=35;
f=[theta(1)-atan(position_y/position_x);
   sqrt(position_x^2+position_y^2)-l2*sin(theta(2))-l3*sin(theta(3)-theta(2))-l4;
   l1+l2*cos(theta(2))-l3*cos(theta(3)-theta(2))-position_z];
end