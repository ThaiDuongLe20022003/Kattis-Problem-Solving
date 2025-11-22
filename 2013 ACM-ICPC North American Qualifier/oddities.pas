program oddities;
var
  n, i, next: integer;
begin
  readln(n);
  
  for i := 1 to n do
  begin
    readln(next);
    
    if (next and 1) = 1 then
      writeln(next, ' is odd')
    else
      writeln(next, ' is even');
  end;
end.