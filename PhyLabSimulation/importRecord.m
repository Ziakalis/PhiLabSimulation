function Record = importRecord(filename, dataLines)
%IMPORTFILE 从文本文件中导入数据
%  RECORD = IMPORTFILE(FILENAME)读取文本文件 FILENAME 中默认选定范围的数据。  以表形式返回数据。
%
%  RECORD = IMPORTFILE(FILE, DATALINES)按指定行间隔读取文本文件 FILENAME
%  中的数据。对于不连续的行间隔，请将 DATALINES 指定为正整数标量或 N×2 正整数标量数组。
%
%  示例:
%  Record = importfile("C:\Users\Ziaka\source\repos\PhyLabSimulation\PhyLabSimulation\Record.txt", [2, Inf]);
%
%  另请参阅 READTABLE。
%
% 由 MATLAB 于 2019-06-08 22:13:16 自动生成

%% 输入处理

% 如果不指定 dataLines，请定义默认范围
if nargin < 2
    dataLines = [2, Inf];
end

%% 设置导入选项
opts = delimitedTextImportOptions("NumVariables", 19);

% 指定范围和分隔符
opts.DataLines = dataLines;
opts.Delimiter = " ";

% 指定列名称和类型
opts.VariableNames = ["Time", "SX", "SY", "SZ", "SVx", "SVy", "SVz", "SAx", "SAy", "SAz", "EX", "EY", "EZ", "EVx", "EVy", "EVz", "EAx", "EAy", "EAz"];
opts.VariableTypes = ["double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double"];
opts.ExtraColumnsRule = "ignore";
opts.EmptyLineRule = "read";
opts.ConsecutiveDelimitersRule = "join";
opts.LeadingDelimitersRule = "ignore";

% 导入数据
Record = readtable(filename, opts);

end