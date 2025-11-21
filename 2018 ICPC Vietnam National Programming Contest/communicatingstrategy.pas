program Main;

const
  MOD_VAL = 1000000007;
  INF = 1 shl 60;

type
  LongIntArray = array of int64;
  LongInt2DArray = array of array of int64;

function modinverse(a, b: int64): int64;
begin
  if 1 < a then
    modinverse := b - modinverse(b mod a, a) * b div a
  else
    modinverse := 1;
end;

procedure clean(var n: int64);
begin
  while n < MOD_VAL do
    n := n + MOD_VAL;
  n := n mod MOD_VAL;
end;

var
  n, i, j: int64;
  t1, t2, val: int64;
  memo: LongInt2DArray;
  ans: array of int64;
  ans_size: integer;

begin
  readln(n);
  
  SetLength(memo, n + 1);
  for i := 0 to n do
  begin
    SetLength(memo[i], n + 1);
    for j := 0 to n do
      memo[i][j] := 0;
  end;
  
  writeln('1 1 1');
  flush(output);
  readln(t1, t2);
  memo[1][1] := t2;
  
  SetLength(ans, n);
  ans_size := 0;
  ans[ans_size] := t2;
  ans_size := ans_size + 1;
  
  for i := 2 to n do
  begin
    writeln('1 1 ', i);
    flush(output);
    readln(t1, t2);
    
    if t1 = 1 then
    begin
      val := t2 - memo[i - 1][1];
      clean(val);
    end
    else if t1 = i then
    begin
      val := t2 * modinverse(memo[i - 1][i - 1], MOD_VAL);
      clean(val);
    end
    else
    begin
      val := (t2 - memo[i - 1][t1]);
      clean(val);
      val := val * modinverse(memo[i - 1][t1 - 1], MOD_VAL);
      clean(val);
    end;
    
    for j := 1 to i do
    begin
      if j = 1 then
      begin
        memo[i][j] := memo[i - 1][j] + val;
        clean(memo[i][j]);
      end
      else if j = i then
      begin
        memo[i][j] := memo[i - 1][j - 1] * val;
        clean(memo[i][j]);
      end
      else
      begin
        memo[i][j] := memo[i - 1][j] + memo[i - 1][j - 1] * val;
        clean(memo[i][j]);
      end;
    end;
    
    if ans_size < n then
    begin
      ans[ans_size] := val;
      ans_size := ans_size + 1;
    end;
  end;
  
  write('2 ');
  for i := 0 to ans_size - 1 do
    write(ans[i], ' ');
  writeln;
  flush(output);
end.