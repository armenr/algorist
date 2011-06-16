/*
We close this chapter with a simulation program for the daughter-son prob-
lem from Chapter 1. This problem can lead to heated discussions over the right
answer. The right answer to the first question posed in this problem is 1/3, but
the probability in question changes to 1/2 in the second situation discussed in
the problem. 

In Chapter 6, we give a probabilistic derivation of these answers
based on the assumption that the probability of a newborn infant being a girl is
the same as the probability of its being a boy. In answering the second question,
we have also made an assumption that, randomly, one of the two children will
open the door. If it is assumed that when a family has one boy and one girl,
the girl always opens the door, the situation changes dramatically. We give,
here, a simulation program that is bound to convince mathematicians and non-
mathematicians alike of the correctness of the answer. 

Writing a simulation program forces you to make implicit assumptions explicit 
and, in every step, to indicate precisely what you mean, unambiguously. In this 
way, you fall into fewer mental traps than would be the case if you were giving 
a purely verbal account.

PROGRAM Family(Input, Output);

  CONST 
    number_runs = 10000; { total number of simulation runs}

  VAR 
    number_d : Integer; { total number of runs with 1 or 2 daughters }
    number_dd : Integer; { total number of runs with 2 daughters }
    number_d_opens : Integer; { total number of runs in which a daughter opens
    the door }
    k : integer; { index of the current run }

  PROCEDURE init;	
  BEGIN
    number_d := 0;
    number_dd := 0;
    number_d_opens := 0;
  END;

  PROCEDURE run;

  VAR composition: (DD, DS, SD, SS);
  { composition of the family, D=daughter, S=son }

  opens_door : (D, S}; { daughter or son opens the door}

  drawing : Integer; { random drawing from 1,2,3,4 }

  BEGIN

    { determine the composition of the family: draw from 1,2,3,4 }
    drawing := 1 + trunc(4*Random);

    CASE drawing OF
      1 : composition := DD;
      2 : composition := DS;
      3 : oomposition := SD;
      4 : composition := SS;
    END;

    { determine whether daughter or son opens the door }

  IF ( composition = DD) THEN
    opens_door := D

  ELSE IF ( composition = SS) THEN
    opens_door := S

  ELSE BEGIN { composition is DS of SD: additional random number is needed 
    to determine who opens the door, D or S; each possibility has a probability 
    of 0.5 }

    IF (Random < 0.5) THEN
      opens_door := D
    ELSE
      opens_door := S;
    END;

    { update counters }
    IF (composition <> SS) THEN
      number_d := number_d + 1;

    IF (composition = DD) THEN
      number_dd := number_dd + 1;

    IF (opens_door = D) then
      number_d_opens := number_d_opens + 1;

  END;

  BEGIN { main program }
    Randomize; { initialize the random-number generator of your computer }

    { execute the simulation }
    init;

    for k := 1 to number_runs do
      run;

    { results }
    Writeln('probability of two daughters given one daughter :', 
      number_dd/number_d);

    Writeln('probability of two daughters given a daughter opens:', 
      number_dd/number_d_opens);

  END.
*/

