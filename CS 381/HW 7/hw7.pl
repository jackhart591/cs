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

schedule(Sid,C,B,T) :- 
  student(Sid, _, _), % Checks to see if student exists
  enroll(Sid, Crn), % Gets CRN of course
  place(Crn, B, T), % Gets the building and time from CRN
  section(Crn, Num), % Gets course number from CRN
  course(Num, C, _). % Gets course name from CRN

schedule(Sid, Name, Course_name) :-
  student(Sid, Name, _), % Gets name from sid
  enroll(Sid, Crn), % Gets CRN from sid
  section(Crn, Num), % Gets course number from CRN
  course(Num, Course_name, _). % Gets course name from CRN

offer(Cnum, Name, Crn, Time) :-
  course(Cnum, Name, _),
  section(Crn, Cnum),
  place(Crn, _, Time).
