#!/usr/bin/octave --persist
source("output.m");
hold on;
grid on;
title('execution time given matrix dimension');
xlabel('dimension');
ylabel('time');
plot(andreaticks, andreatimes);
