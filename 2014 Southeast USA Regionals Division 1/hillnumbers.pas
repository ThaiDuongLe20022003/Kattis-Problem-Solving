program HillNumbers;

type
  LongInt = Int64;
  BoolArray = array[0..19, 0..9, 0..1, 0..1] of LongInt;

var
  S: string;
  memo: BoolArray;

function dp(pos, prev_d: integer; is_less, is_started, is_falling: boolean): LongInt;
var
  d, upper_bound: integer;
  ans: LongInt;
begin
  if pos = Length(S) + 1 then
  begin
    if is_started then
      dp := 1
    else
      dp := 0;
    exit;
  end;
  
  if memo[pos, prev_d, Ord(is_less), Ord(is_falling)] <> -1 then
  begin
    dp := memo[pos, prev_d, Ord(is_less), Ord(is_falling)];
    exit;
  end;
  
  ans := 0;
  if is_less then
    upper_bound := 9
  else
    upper_bound := Ord(S[pos]) - Ord('0');
  
  for d := 0 to upper_bound do
  begin
    if not is_started then
    begin
      if d = 0 then
      begin
        ans := ans + dp(pos + 1, 0, true, false, false);
      end
      else
      begin
        ans := ans + dp(pos + 1, d, is_less or (d < upper_bound), true, false);
      end;
    end
    else
    begin
      if is_falling then
      begin
        if d <= prev_d then
        begin
          ans := ans + dp(pos + 1, d, is_less or (d < upper_bound), true, true);
        end;
      end
      else
      begin
        if d < prev_d then
        begin
          ans := ans + dp(pos + 1, d, is_less or (d < upper_bound), true, true);
        end
        else
        begin
          ans := ans + dp(pos + 1, d, is_less or (d < upper_bound), true, false);
        end;
      end;
    end;
  end;
  
  memo[pos, prev_d, Ord(is_less), Ord(is_falling)] := ans;
  dp := ans;
end;

function is_hill_number(s: string): boolean;
var
  i: integer;
  falling: boolean;
  has_non_zero: boolean;
begin
  if Length(s) = 0 then
  begin
    is_hill_number := false;
    exit;
  end;
  
  has_non_zero := false;
  for i := 1 to Length(s) do
  begin
    if s[i] <> '0' then
    begin
      has_non_zero := true;
      break;
    end;
  end;
  
  if not has_non_zero then
  begin
    is_hill_number := false;
    exit;
  end;
  
  falling := false;
  for i := 1 to Length(s) - 1 do
  begin
    if s[i] < s[i + 1] then
    begin
      if falling then
      begin
        is_hill_number := false;
        exit;
      end;
    end
    else if s[i] > s[i + 1] then
    begin
      falling := true;
    end;
  end;
  
  is_hill_number := true;
end;

function solve(n_str: string): LongInt;
var
  i, j, k, l: integer;
begin
  S := n_str;
  for i := 0 to 19 do
    for j := 0 to 9 do
      for k := 0 to 1 do
        for l := 0 to 1 do
          memo[i, j, k, l] := -1;
          
  solve := dp(1, 0, false, false, false);
end;

var
  n_str: string;
begin
  while not EOF do
  begin
    ReadLn(n_str);
    if n_str = '' then continue;
    
    if not is_hill_number(n_str) then
      WriteLn('-1')
    else
      WriteLn(solve(n_str));
  end;
end.