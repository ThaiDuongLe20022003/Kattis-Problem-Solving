program SimonSays;

var
  times, i: integer;
  s: string;

begin
  readln(times);
  
  for i := 1 to times do
  begin
    readln(s);
    
    if Pos('Simon says', s) = 1 then  // Check if it starts at position 1
    begin
      Delete(s, 1, 11);  // Delete first 11 characters
      writeln(s);
    end;
  end;
end.