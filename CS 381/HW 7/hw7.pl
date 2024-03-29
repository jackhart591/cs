/* course(course_number, course_name, credits) */

course(cs101,python, 2).
course(mth210, calculusI, 5).
course(cs120, web_design, 3).
course(cs200, data_structures, 4).
course(cs210, algorithms, 4).
course(wrt101, basic_writing, 3).

/* section(CRN, course_number) */

section(1522,cs101).
section(1122,cs101).
section(2322,mth210).
section(2421,cs120).
section(8522,mth210).
section(1621,cs200).
section(7822,mth210).
section(2822,cs210).
section(3522,wrt101).

/* place( CRN, building, time) */

place(1522,owen102,10).
place(1122,dear118,11).
place(2322,with210,11).
place(2421,cov216,15).
place(8522,kec1001,13).
place(1621,cov216,14).
place(7822,kec1001,14).
place(2822,owen102,13).
place(3522,with210,15).

/* enroll(sid, CRN) */

enroll(122,1522).
enroll(122,8522).
enroll(150,1522).
enroll(150,2421).
enroll(212,7822).
enroll(300,2822).
enroll(300,8522).
enroll(310,3522).
enroll(310,8522).
enroll(310,1621).
enroll(175,2822).
enroll(175,7822).
enroll(175,3522).
enroll(410,1621).
enroll(410,7822).
enroll(113,3522).

/* student(sid, student_name, major) */

student(122, mary, cs).
student(150, john, math).
student(212, jim, ece).
student(300, lee, cs).
student(310, pat, cs).
student(175, amy, math).
student(410, john, cs).
student(113, zoe, ece).

/* schedule(Student ID, CRN, Building, Time) */
schedule(Sid,C,B,T) :- 
  enroll(Sid, Crn), % Gets CRN of course
  place(Crn, B, T), % Gets the building and time from CRN
  section(Crn, Num), % Gets course number from CRN
  course(Num, C, _). % Gets course name from CRN

/* schedule(Student ID, Student Name, Course Name) */
schedule(Sid, Name, Course_name) :-
  student(Sid, Name, _), % Gets name from sid
  enroll(Sid, Crn), % Gets CRN from sid
  section(Crn, Num), % Gets course number from CRN
  course(Num, Course_name, _). % Gets course name from CRN

/* offer(Course Number, Course Name, CRN, Time) */
offer(Cnum, Name, Crn, Time) :-
  course(Cnum, Name, _), % Gets Name or Cnum from the other
  section(Crn, Cnum), % Gets Crn or Cnum from the other
  place(Crn, _, Time). % Gets Time or Crn from the other

/* conflict(Student ID, CRN, CRN) */
conflict(Sid, Crn1, Crn2) :-
  enroll(Sid, Crn1), % Is this person enrolled in this Crn?
  enroll(Sid, Crn2), % Is this person enrolled in this Crn?
  Crn1\=Crn2, % Make sure the CRNs are different.
  place(Crn1, _, Time), 
  place(Crn2, _, Time). % If so, do the start times have equality?

/* meet(Student ID, Student ID) */
meet(Sid1, Sid2) :-
  enroll(Sid1, Crn1), % Checks to see if student 1 is enrolled
  enroll(Sid2, Crn2), % Checks to see if student 2 is enrolled
  place(Crn1, Bd, Time1), place(Crn2, Bd, Time2), % Checks to see if they'll be in the same building
  ((Time1 + 1) =:= Time2; (Time2 + 1) =:= Time1; Time1 =:= Time2), % Checks to see if they're back to back or at the same time
  Sid1 \= Sid2. % Ensures student 1 and 2 aren't the same student

/* roster(CRN, Student Name) */
roster(Crn, Sname) :-
  enroll(Sid, Crn), % Gets the Student ID from CRN
  student(Sid, Sname, _). % Gets the Sid from Sname

/* highCredits(Course Name) */
highCredits(Cname) :-
  course(_, Cname, Cred), % Gets the number of credits from course name
  Cred >= 4. % Checks to see if the credits are greater than or equal to 4
  
/* rdup(List, List) */
rdup([X], [_,X]). % Base case
rdup([H|T], [H|MT]) :- rdup(T, [H|MT]). % In the case that there is an element that needs to be removed
rdup([H|T], [MH|MT]) :- H \= MH, rdup(T, MT). % In the case there is a new element

/* flat(List, List) */
flat([], []) :- !. % Base case
flat([H|T], L) :-
  flat(H, NH), % Flattens the first element
  flat(T, NT), % Flattens the remainder of the list
  append(NH, NT, L). % Appends the new lists together
flat(X, [X]) :- !. % If there is one element left, return

/* project(List of Indices, List, List) */
project(IL, OL, L) :- project(0, IL, OL, L).

/* project(List of Indices, List, List) */
/* Helper function */
project(_, [], _, []) :- !. % Base case
project(_, _, [], []) :- !. % Base case
project(I, [K|IT], [OH|OT], [OH|L]) :- K is I + 1, project(K, IT, OT, L), !. % In the case that we're not taking this element
project(I, [IH|IT], [_|OT], L) :- K is I + 1, project(K, [IH|IT], OT, L), !. % In the case that we're taking this element
