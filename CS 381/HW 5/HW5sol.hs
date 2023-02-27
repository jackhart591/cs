module HW5sol where
    import HW5types
    --Header Comments
    --Ian Backus
    --backusi@oregonstate.edu
    --2/24/2023

    semCmd :: Cmd -> Stack -> Maybe Stack

    semCmd ADD ((I x):[]) = Nothing
    semCmd ADD ((I x):(I y):xs) = Just ((I(x+y)):xs) -- if two ints add
    semCmd ADD _ = Nothing -- else return nothing

    semCmd MULT ((I x):[]) = Nothing
    semCmd MULT ((I x):(I y):xs) = Just ((I(x*y)):xs) -- if two ints, mult
    semCmd MULT _ = Nothing -- else return nothing

    semCmd DUP (x:xs) = Just (x:x:xs) -- if there is a value to dup, dup it

    semCmd (IFELSE _ _) [] = Nothing
    semCmd (IFELSE p p1) ((B x):xs)
        | x == True = case run p xs of
                  A stack -> Just stack
                  _       -> Nothing
        | x == False = case run p1 xs of
                  A stack -> Just stack
                  _       -> Nothing

    semCmd (LDB b) s = Just ((B b):s) -- Loads a bool onto the stack
    semCmd (LDI i) s = Just ((I i):s) -- Loads an int onto the stack

    semCmd LEQ ((I x):[]) = Nothing
    semCmd LEQ ((I x):(I y):xs) = Just ((B (x<=y)):xs) -- Load the result of x<=y if there are two ints
    semCmd LEQ _ = Nothing

    semCmd DEC ((B x):xs) = Nothing
    semCmd DEC ((I x):xs) = Just ((I (x-1)):xs)

    semCmd SWAP (x:y:xs) = Just (y:x:xs)

    semCmd (POP k) [] = Nothing
    semCmd (POP 0) xs = Just xs
    semCmd (POP k) (x:xs) = semCmd (POP (k-1)) xs

    rankC :: Cmd -> CmdRank
    rankC (ADD) = (2,1)
    rankC (DEC) = (1,1)
    rankC (MULT) = (2,1)
    rankC (LDI a) = (0,1)
    rankC (LDB b) = (0,1)
    rankC (SWAP) = (2,2)
    rankC (POP k) = (k,0)
    rankC (LEQ) = (2,1)
    rankC (DUP) = (1,2)

    rankP :: Prog -> Rank -> Maybe Rank
    rankP [] a = Just a
    rankP ((IFELSE a b):xs) curRank = (rank a b curRank)
    rankP (x:xs) curRank = case compare (curRank + (snd(rankC x) - fst(rankC x))) 0 of 
                        LT -> Nothing
                        otherwise -> (rankP xs (curRank + (snd(rankC x) - fst(rankC x))))

    rank :: Prog -> Prog -> Rank -> Maybe Rank
    rank a b r  
        | (rankP a r) == Nothing || (rankP b r) == Nothing = Nothing
        | otherwise = (min (rankP a r) (rankP b r))

    run :: Prog -> Stack -> Result
    run [] [] = (A [])
    run [] s = (A s)
    run p s = case rankP p (length s) of 
        Nothing -> RankError
        Just l -> case runHelper p s of
            Nothing -> TypeError
            Just s' -> A s'

    runHelper :: Prog -> Stack -> Maybe Stack
    runHelper [] s = Just s
    runHelper (c:cs) s = case semCmd c s of
        Nothing -> Nothing
        Just s' -> runHelper cs s' -- if there is stuff to run, run it