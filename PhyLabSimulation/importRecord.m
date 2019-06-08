function Record = importRecord(filename, dataLines)
%IMPORTFILE ���ı��ļ��е�������
%  RECORD = IMPORTFILE(FILENAME)��ȡ�ı��ļ� FILENAME ��Ĭ��ѡ����Χ�����ݡ�  �Ա���ʽ�������ݡ�
%
%  RECORD = IMPORTFILE(FILE, DATALINES)��ָ���м����ȡ�ı��ļ� FILENAME
%  �е����ݡ����ڲ��������м�����뽫 DATALINES ָ��Ϊ������������ N��2 �������������顣
%
%  ʾ��:
%  Record = importfile("C:\Users\Ziaka\source\repos\PhyLabSimulation\PhyLabSimulation\Record.txt", [2, Inf]);
%
%  ������� READTABLE��
%
% �� MATLAB �� 2019-06-08 22:13:16 �Զ�����

%% ���봦��

% �����ָ�� dataLines���붨��Ĭ�Ϸ�Χ
if nargin < 2
    dataLines = [2, Inf];
end

%% ���õ���ѡ��
opts = delimitedTextImportOptions("NumVariables", 19);

% ָ����Χ�ͷָ���
opts.DataLines = dataLines;
opts.Delimiter = " ";

% ָ�������ƺ�����
opts.VariableNames = ["Time", "SX", "SY", "SZ", "SVx", "SVy", "SVz", "SAx", "SAy", "SAz", "EX", "EY", "EZ", "EVx", "EVy", "EVz", "EAx", "EAy", "EAz"];
opts.VariableTypes = ["double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double"];
opts.ExtraColumnsRule = "ignore";
opts.EmptyLineRule = "read";
opts.ConsecutiveDelimitersRule = "join";
opts.LeadingDelimitersRule = "ignore";

% ��������
Record = readtable(filename, opts);

end