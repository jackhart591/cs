module Stacklang2 where

    -- Name: Jackson Hart
    -- Date: 2/15/23
    -- Email: hartjack@oregonstate.edu

    type Prog = [Cmd]

    type Stack = [Either Bool Int]
    data Cmd =
        ADD
        | MULT
        | DUP
        | IFELSE Prog Prog
        | LDB Bool
        | LEQ
        | LDI Int

    semCmd :: Cmd -> Stack -> Maybe Stack

    semCmd ADD [] = Nothing
    semCmd ADD ((Right x):[]) = Nothing
    semCmd ADD ((Right x):(Right y):xs) = Just ((Right(x+y)):xs) -- if two ints add
    semCmd ADD _ = Nothing -- else return nothing

    semCmd MULT [] = Nothing
    semCmd MULT ((Right x):[]) = Nothing
    semCmd MULT ((Right x):(Right y):xs) = Just ((Right(x*y)):xs) -- if two ints, mult
    semCmd MULT _ = Nothing -- else return nothing

    semCmd DUP [] = Nothing
    semCmd DUP (x:xs) = Just (x:x:xs) -- if there is a value to dup, dup it

    semCmd (IFELSE _ _) [] = Nothing
    semCmd (IFELSE p p1) ((Left x):xs)
        | x == True = (run p xs) -- if top of stack is true, run p on the rest of the stack
        | x == False = (run p1 xs) -- else run p1 on the rest of the stack

    semCmd (LDB b) s = Just ((Left b):s) -- Loads a bool onto the stack
    semCmd (LDI i) s = Just ((Right i):s) -- Loads an int onto the stack

    semCmd LEQ [] = Nothing
    semCmd LEQ ((Right x):[]) = Nothing
    semCmd LEQ ((Right x):(Right y):xs) = Just ((Left(x<=y)):xs) -- Load the result of x<=y if there are two ints
    semCmd LEQ _ = Nothing

    run :: Prog -> Stack -> Maybe Stack
    run [] s = Just s
    run (c:cs) s = case semCmd c s of
        Nothing -> Nothing
        Just s' -> run cs s' -- if there is stuff to run, run it

    -- stack1 :: Stack
    -- stack1 = [Right 1, Right 3, Right 5, Right 7, Right 9]
    -- stack2 :: Stack
    -- stack2 = [Left True, Right 3]
    -- test1 = [LDI 3, DUP, ADD, DUP, MULT]
    -- test2 = [LDB True, DUP, IFELSE [LDI 1][LDI 0]]
    -- test3 = [LEQ]
    -- test4 = [ADD, ADD, MULT, DUP]
    -- test5 = [LEQ, IFELSE [] [], LDI 9]
    -- test6 = [LDI 5, LDI 2, LEQ, IFELSE [LDI 10, DUP] [], ADD]
    -- test7 = [LDI 5, LDI 7, LEQ, IFELSE [LDI 10, DUP] [LDI 20, DUP], ADD]
    -- test8 = [LDI 1, LDI 2, LDI 3, LDI 4, LDI 5, ADD, ADD, ADD, ADD]