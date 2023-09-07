%voltage: T = 353, lambda = 13 -> yellow
%voltage1: T = 333, lambda = 11 -> light blue
%voltage2: T = 313, lambda = 11 -> purple
%voltage3: T = 302, lambda = 13 -> black
%voltage4: T = 344, lambda = 15 -> green
%voltage5: T = 361, lambda = 12 -> strong blue
%voltage6: T = 370, lambda = 14 -> red

yyaxis left;
plot(current,voltage,current,voltage1,current,voltage2,current,voltage3,current,voltage4,current,voltage5,current,voltage6);
colororder(["#fff200","#01ffff","#c720c7","#000000","#00ff00","#6e6eff","#ff1e1e"]);
yyaxis right;
plot(current,power,current,power1,current,power2,current,power3,current,power4,current,power5,current,power6);
colororder(["#fff200","#01ffff","#c720c7","#000000","#00ff00","#6e6eff","#ff1e1e"]);
