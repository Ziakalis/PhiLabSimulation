clearvars; clc; close all;
Record = importRecord('Record.txt');
figure;hold on;
plot3(Record.EX, Record.EY, Record.EZ, 'linewidth', 2);
plot3(Record.SX, Record.SY, Record.SZ, 'r', 'linewidth', 2);