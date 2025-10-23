main :-
    readln(N,end_of_file),
    findall(H:M,(between(0,11,H),between(0,59,M),
               HourAng is 300*H+5*M,
               MinuteAng is 60*M,
               (N =:= (MinuteAng - HourAng + 3600) mod 3600 ->
                   format('~|~`0t~d~2+:~|~`0t~d~2+~n',[H,M])
               ;
                   true
               )),
            _).