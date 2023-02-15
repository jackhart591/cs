module Stacklang1 where

    -- Name: Jackson Hart
    -- Date: 2/15/23
    -- Email: hartjack@oregonstate.edu

    type Prog = [Cmd]
    data Cmd = 
        ADD
        | MULT
        | DUP
        | LD Int
        deriving Show

    type Stack = [Int]

    semCmd :: Cmd -> Stack -> Maybe Stack

    semCmd ADD (x:y:xs) = Just ((x+y):xs) -- if two elems, add them
    semCmd ADD (x) = Nothing

    semCmd DUP (x:xs) = Just (x:x:xs) -- if one elem, dup it
    semCmd DUP [] = Nothing

    semCmd MULT (x:y:xs) = Just (x*y:xs) -- if two elems, mult them
    semCmd MULT (x) = Nothing

    semCmd (LD n) s = Just (n:s) -- loads int onto stack

    run :: Prog -> Stack -> Maybe Stack
    run [] s = Just s

    run (c:cs) s = case semCmd c s of 
        Nothing -> Nothing
        Just s' -> run cs s' -- if there is stuff to run, run it