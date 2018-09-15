clc
%Robot Arm Coordinate transformation Model
%Robot Arm Coordinate transformation Model
%Robot Arm Coordinate transformation Model
 cd  C:\Users\DELL\Desktop\OperateCamera\bin\Debug\PersonImg          %C:\Users\Dell\Desktop\matlab;
im=imread('1.jpg');
im=imresize(im,[640 852]);       %（*调试）
gray = rgb2gray(im);        %（改善）常规rgb2gray转换

s=size(gray);
figure(1),imshow(gray,'border','tight');

grayo = imopen(gray,strel('disk',20));         %开操作 去除亮点
grayoc=imclose(grayo,strel('disk',10));       %闭操作 去除暗点
figure(3),imshow(grayoc,'border','tight');

grayoco = imopen(gray,strel('disk',80));     %（*调试）开操作去掉工件留下背景
grayocosub=imsubtract(grayoc,grayoco);
%grayocosub=imadjust(grayocosub);            %（可去）提升对比度
%figure(4),imshow(grayocosub);             
figure(4),imshow(grayoco,'border','tight');
figure(6),imshow(grayocosub,'border','tight');

level = graythresh(grayocosub);%otsu法寻找阈值

bw=im2bw(grayocosub,level);                      %二值化
figure(5),imshow(bw,'border','tight');

[L,num]=bwlabel(bw,8);          %标记

for i=1:num
    
    label1=(ones(s)*i==L);              %(调试）得到物体1
    data=regionprops(label1,'basic');
    rec=data.BoundingBox;
    rectangle('Position',[rec(1,1),rec(1,2),rec(1,3),rec(1,4)],'EdgeColor','red');
    text(data.Centroid(1,1),data.Centroid(1,2),'*','color','red');
    data.Centroid(1,1)
    data.Centroid(1,2)
  
    px=(data.Centroid(1,1)/840*265-125)*0.99
    py=190-data.Centroid(1,2)/630*190
    position_orgin=[0;0;1];
    position_x=  180+py ; %180+(170-((data.Centroid(1,1)-38)/4.55))    ;             %positon_x=280;
    position_y= -px; %(data.Centroid(1,2)-41)/5.05;                       %positon_y=0;
    % position_x
    % position_y
    
    
    %data.Centroid
    arm_afa=fsolve(@(theta)position(theta,position_x,position_y),position_orgin);
    send_theta=[];
    send_theta(1)=arm_afa(1)*180/3.14;
    send_theta(2)=arm_afa(2)*180/3.14;
    send_theta(3)=arm_afa(3)*180/3.14-send_theta(2)-30;
    % send_theta(1)
    % send_theta(2)
    % send_theta(3)
    % The Communication Model
    % The Communication Model
    if i~=1   
        pause(7);
    end
        get_afa=[];
        delete(instrfindall);
        arduino=serial('COM3','BaudRate',9600);
        fopen(arduino);
        pause(1);
      
        for i=1:1:3;
            fprintf(arduino,'%f',send_theta(i));
            pause(0.5);
            get_afa(i)=fscanf(arduino,'%f');
        end
        fclose(arduino);
        delete(instrfindall);
        % get_afa(1)
        % get_afa(2)
        % get_afa(3)
    

end

 
