clc
send_theta=[20.53;30.32;52.45];
get_afa=[];
delete(instrfindall);
arduino=serial('COM4','BaudRate',9600);
fopen(arduino);
pause(1);
for i=1:1:3;
    fprintf(arduino,'%f',send_theta(i));
    pause(0.5);
    get_afa(i)=fscanf(arduino,'%f');
end
fclose(arduino);
delete(instrfindall);
get_afa(1)
get_afa(2)
get_afa(3)