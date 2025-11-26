program PangramChecker;

var
  n, i, j, used, temp: integer;
  s: string;
  letters: array[0..25] of boolean;
  c: char;

begin
  readln(n);
  
  for i := 1 to n do
  begin
    // Initialize letters array
    for j := 0 to 25 do
      letters[j] := false;
    
    readln(s);
    used := 0;
    
    for j := 1 to Length(s) do
    begin
      c := s[j];
      temp := Ord(LowerCase(c)) - Ord('a');
      if (temp < 26) and (temp >= 0) and (not letters[temp]) then
      begin
        letters[temp] := true;
        used := used + 1;
      end;
    end;
    
    if used = 26 then
      write('pangram')
    else
    begin
      write('missing ');
      for j := 0 to 25 do
      begin
        if not letters[j] then
          write(Chr(j + Ord('a')));
      end;
    end;
    
    writeln;
  end;
end.