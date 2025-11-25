program SymmetryAxes;

type
  Tuple = record
    r1, c1, r2, c2: Integer;
  end;

  TupleArray = array of Tuple;

function CompareTuples(const a, b: Tuple): Integer;
begin
  if a.r1 <> b.r1 then
    CompareTuples := a.r1 - b.r1
  else if a.c1 <> b.c1 then
    CompareTuples := a.c1 - b.c1
  else if a.r2 <> b.r2 then
    CompareTuples := a.r2 - b.r2
  else
    CompareTuples := a.c2 - b.c2;
end;

procedure AddTuple(var arr: TupleArray; r1, c1, r2, c2: Integer);
var
  len: Integer;
begin
  len := Length(arr);
  SetLength(arr, len + 1);
  arr[len].r1 := r1;
  arr[len].c1 := c1;
  arr[len].r2 := r2;
  arr[len].c2 := c2;
end;

function ValidVert(r1, c1, r2, c2, n, m: Integer; grid: array of string): Boolean;
var
  i, j, i1, j1: Integer;
begin
  for i := 0 to n - 1 do
  begin
    for j := 0 to m - 1 do
    begin
      i1 := i;
      j1 := 2 * c1 - j + 1;
      if (i1 < 0) or (i1 >= n) or (j1 < 0) or (j1 >= m) then
      begin
        if grid[i][j+1] = '.' then
        begin
          ValidVert := False;
          Exit;
        end
        else
          Continue;
      end;
      if grid[i][j+1] = grid[i1][j1+1] then
      begin
        ValidVert := False;
        Exit;
      end;
    end;
  end;
  ValidVert := True;
end;

procedure GetVert(n, m: Integer; grid: array of string; var rv: TupleArray);
var
  i: Integer;
begin
  for i := 0 to m - 1 do
  begin
    if ValidVert(0, i, n-1, i, n, m, grid) then
    begin
      AddTuple(rv, 0, i, n-1, i);
      Exit;
    end;
  end;
end;

function ValidHor(r1, c1, r2, c2, n, m: Integer; grid: array of string): Boolean;
var
  i, j, i1, j1: Integer;
begin
  for i := 0 to n - 1 do
  begin
    for j := 0 to m - 1 do
    begin
      i1 := 2 * r1 - i + 1;
      j1 := j;
      if (i1 < 0) or (i1 >= n) or (j1 < 0) or (j1 >= m) then
      begin
        if grid[i][j+1] = '.' then
        begin
          ValidHor := False;
          Exit;
        end
        else
          Continue;
      end;
      if grid[i][j+1] = grid[i1][j1+1] then
      begin
        ValidHor := False;
        Exit;
      end;
    end;
  end;
  ValidHor := True;
end;

procedure GetHor(n, m: Integer; grid: array of string; var rv: TupleArray);
var
  i: Integer;
begin
  for i := 0 to n - 1 do
  begin
    if ValidHor(i, 0, i, m-1, n, m, grid) then
    begin
      AddTuple(rv, i, 0, i, m-1);
      Exit;
    end;
  end;
end;

function ValidDiag1(r1, c1, r2, c2, n, m: Integer; grid: array of string): Boolean;
var
  i, j, i1, j1, s: Integer;
begin
  s := r1 + c1;
  for i := 0 to n - 1 do
  begin
    for j := 0 to m - 1 do
    begin
      i1 := s - j;
      j1 := s - i;
      if (i1 < 0) or (i1 >= n) or (j1 < 0) or (j1 >= m) then
      begin
        if grid[i][j+1] = '.' then
        begin
          ValidDiag1 := False;
          Exit;
        end
        else
          Continue;
      end;
      if (i = i1) and (j = j1) then
      begin
        if grid[i][j+1] = '.' then
        begin
          ValidDiag1 := False;
          Exit;
        end
        else
          Continue;
      end;
      if grid[i][j+1] = grid[i1][j1+1] then
      begin
        ValidDiag1 := False;
        Exit;
      end;
    end;
  end;
  ValidDiag1 := True;
end;

procedure GetDiag1(n, m: Integer; grid: array of string; var rv: TupleArray);
var
  i, j, r1, c1, r2, c2: Integer;
begin
  for i := 0 to n - 1 do
  begin
    for j := 0 to m - 1 do
    begin
      if (j <> 0) and (i <> n - 1) then
        Continue;
      r1 := i; c1 := j;
      r2 := i; c2 := j;
      while (r2 >= 0) and (c2 < m) do
      begin
        Dec(r2); Inc(c2);
      end;
      Inc(r2); Dec(c2);
      if ValidDiag1(r1, c1, r2, c2, n, m, grid) then
      begin
        AddTuple(rv, r1, c1, r2, c2);
        Exit;
      end;
    end;
  end;
end;

function ValidDiag2(r1, c1, r2, c2, n, m: Integer; grid: array of string): Boolean;
var
  i, j, i1, j1, s: Integer;
begin
  s := r1 - c1;
  for i := 0 to n - 1 do
  begin
    for j := 0 to m - 1 do
    begin
      i1 := s + j;
      j1 := i - s;
      if (i1 < 0) or (i1 >= n) or (j1 < 0) or (j1 >= m) then
      begin
        if grid[i][j+1] = '.' then
        begin
          ValidDiag2 := False;
          Exit;
        end
        else
          Continue;
      end;
      if (i = i1) and (j = j1) then
      begin
        if grid[i][j+1] = '.' then
        begin
          ValidDiag2 := False;
          Exit;
        end
        else
          Continue;
      end;
      if grid[i][j+1] = grid[i1][j1+1] then
      begin
        ValidDiag2 := False;
        Exit;
      end;
    end;
  end;
  ValidDiag2 := True;
end;

procedure GetDiag2(n, m: Integer; grid: array of string; var rv: TupleArray);
var
  i, j, r1, c1, r2, c2: Integer;
begin
  for i := 0 to n - 1 do
  begin
    for j := 0 to m - 1 do
    begin
      if (j <> 0) and (i <> 0) then
        Continue;
      r1 := i; c1 := j;
      r2 := i; c2 := j;
      while (r2 < n) and (c2 < m) do
      begin
        Inc(r2); Inc(c2);
      end;
      Dec(r2); Dec(c2);
      if ValidDiag2(r1, c1, r2, c2, n, m, grid) then
      begin
        AddTuple(rv, r1, c1, r2, c2);
        Exit;
      end;
    end;
  end;
end;

procedure SortTuples(var arr: TupleArray);
var
  i, j: Integer;
  temp: Tuple;
begin
  for i := 0 to High(arr) - 1 do
  begin
    for j := i + 1 to High(arr) do
    begin
      if CompareTuples(arr[i], arr[j]) > 0 then
      begin
        temp := arr[i];
        arr[i] := arr[j];
        arr[j] := temp;
      end;
    end;
  end;
end;

var
  n, m, i: Integer;
  grid: array of string;
  rv: TupleArray;
begin
  ReadLn(n, m);
  SetLength(grid, n);
  for i := 0 to n - 1 do
    ReadLn(grid[i]);
  
  SetLength(rv, 0);
  GetVert(n, m, grid, rv);
  GetHor(n, m, grid, rv);
  GetDiag1(n, m, grid, rv);
  GetDiag2(n, m, grid, rv);
  
  if Length(rv) > 0 then
  begin
    SortTuples(rv);
    with rv[0] do
      WriteLn(r1 + 1, ' ', c1 + 1, ' ', r2 + 1, ' ', c2 + 1);
  end;
end.