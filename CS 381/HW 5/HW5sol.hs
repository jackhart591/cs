module HW5sol where
    import HW5types

    --Header Comments
    --Ian Backus / Jackson Hart
    --backusi@oregonstate.edu
    --hartjack@oregonstate.edu
    --2/27/2023

    semCmd :: Cmd -> Stack -> Maybe Stack

    semCmd ADD ((I x):[]) = Nothing
    semCmd ADD ((I x):(I y):xs) = Just ((I(x+y)):xs) -- if two ints add
    semCmd ADD _ = Nothing -- else return nothing

    semCmd MULT ((I x):[]) = Nothing
    semCmd MULT ((I x):(I y):xs) = Just ((I(x*y)):xs) -- if two ints, mult
    semCmd MULT _ = Nothing -- else return nothing

    semCmd DUP (x:xs) = Just (x:x:xs) -- if there is a value to dup, dup it

    semCmd (IFELSE p p1) ((B x):xs)
        | x == True = case run p xs of -- If true run the program
                  A stack -> Just stack -- If returns a stack, return stack
                  _       -> Nothing -- Else, return Nothing to indicate Type Error
        | x == False = case run p1 xs of -- same but with P1
                  A stack -> Just stack
                  _       -> Nothing
    semCmd (IFELSE _ _) ((I x):xs) = Nothing

    semCmd (LDB b) s = Just ((B b):s) -- Loads a bool onto the stack
    semCmd (LDI i) s = Just ((I i):s) -- Loads an int onto the stack

    semCmd LEQ ((I x):[]) = Nothing -- Must have at least two elements
    semCmd LEQ ((I x):(I y):xs) = Just ((B (x<=y)):xs) -- Load the result of x<=y if there are two ints
    semCmd LEQ _ = Nothing -- Else, Type Error

    -- Doesn't require other cases due to being caught by Rank Error
    semCmd DEC ((B x):xs) = Nothing -- Can't decrement a boolean
    semCmd DEC ((I x):xs) = Just ((I (x-1)):xs) -- Return a new stack with x-1 and the remaining stack

    -- Swaps top two values
    -- Doesn't require other cases with less because this would
    -- result in a Rank Error
    semCmd SWAP (x:y:xs) = Just (y:x:xs)

    semCmd (POP 0) xs = Just xs -- Base case
    semCmd (POP _) [] = Nothing -- Can't pop an empty stack
    semCmd (POP k) (x:xs) = semCmd (POP (k-1)) xs -- Pop top val, and then do remaining pops

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
    rankP [] a = Just a -- base case
    rankP ((IFELSE a b):xs) curRank = (rank a b curRank) -- if cmd is IFELSE, run helper func
    rankP (x:xs) curRank = case compare (curRank - fst(rankC x)) 0 of
                        LT -> Nothing -- if rank is invalid, return nothing to indicate Rank Error
                        otherwise -> (rankP xs (curRank + (snd(rankC x) - fst(rankC x)))) -- if rank is valid, recurse to next cmd

    -- Helper function for IFELSE cmds
    rank :: Prog -> Prog -> Rank -> Maybe Rank
    rank a b r  
        | (rankP a (r-1)) == Nothing || (rankP b (r-1)) == Nothing = Nothing -- if either programs return Nothing, return Nothing to indicate RankError
        | otherwise = (min (rankP a (r-1)) (rankP b (r-1))) -- Otherwise, return rank

    -- Wrapper for run helper that checks for errors
    run :: Prog -> Stack -> Result
    run [] [] = (A [])
    run [] s = (A s) -- Base case 
    run p s = case rankP p (length s) of 
        Nothing -> RankError -- Check for rank error
        Just l -> case runHelper p s of -- if none, run
            Nothing -> TypeError -- if nothing, then type error
            Just s' -> A s' -- else return stack

    -- Runs semantic cmds
    runHelper :: Prog -> Stack -> Maybe Stack
    runHelper [] s = Just s -- Base case
    runHelper (c:cs) s = case semCmd c s of
        Nothing -> Nothing -- Type error
        Just s' -> runHelper cs s' -- if there is stuff to run, run it
