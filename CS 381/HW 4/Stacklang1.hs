module Stacklang1 where

    type Prog = [Cmd]
    data Cmd = 
        ADD
        | MULT
        | DUP
        | LD Int
        deriving Show

    type Stack = [Int]

    semCmd :: Cmd -> Stack -> Maybe Stack

    semCmd ADD (x:y:xs) = Just ((x+y):xs) 
    semCmd ADD (x) = Nothing

    semCmd DUP (x:xs) = Just (x:x:xs)
    semCmd DUP [] = Nothing

    semCmd MULT (x:y:xs) = Just (x*y:xs)
    semCmd MULT (x) = Nothing

    semCmd (LD n) s = Just (n:s)

    run :: Prog -> Stack -> Maybe Stack
    run [] s = Just s

    run (c:cs) s = case semCmd c s of 
        Nothing -> Nothing
        Just s' -> run cs s'