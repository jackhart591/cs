module HW2sol where
import HW2types
sname = "Jackson Hart"

-- Name: Jackson Hart
-- Email: hartjack@oregonstate.edu
-- Date: January 30th, 2023

-- insert func takes in an "a" and a Bag where a is 
-- able to have == done on it, and returns a new bag

-- EXERCISE 1

-- If there is any of the value in the list, then
-- increment it, otherwise, add it on at the end
ins :: Eq a => a -> Bag a -> Bag a
ins a bag = 
    if any (\(val, _) -> val == a) bag
        then map (\(val, i) -> if a == val then (val, i+1) else (val, i)) bag
    else bag ++ [(a, 1)]
    
-- If exists and is > 1, then it will decrement
-- Else it will completely remove the entry
del :: Eq a => a -> Bag a -> Bag a
del _ []                                = []
del a ((val, i):xs) | a == val && i > 1 = (val, i-1) : del a xs
    | a == val && i == 1                = del a xs
    | otherwise                         = (val, i) : del a xs

-- Inserts every value into a new bag
bag :: Eq a => [a] -> Bag a
bag [] = []
bag (x:xs) = ins x (bag xs)

-- Checks to see if every value is less than or
-- equal to the value in the bag, and once it's
-- done traversing, if there's anything left in
-- first and not second, says false, otherwise true
subbag :: Eq a => Bag a -> Bag a -> Bool
subbag [] []                    = True
subbag _ []                     = False
subbag [] _                     = True
subbag ((val, i):xs) ((val1, i1):ys) 
    | val == val1 && i <= i1    = subbag xs ys
    | val /= val1               = subbag ((val,i):xs) ys
    | otherwise                 = False

-- Checks to see if every item in the bag has one
-- value, if it reaches the end of the list, then true
isSet :: Eq a => Bag a -> Bool
isSet [] = True
isSet ((val,i):xs) | i == 1 = isSet xs
    | otherwise             = False

-- Increments until it reaches the end of the list
size :: Bag a -> Int
size []             = 0
size ((val,i):xs)   = i + size xs

-- EXERCISE 2

-- Gets the normal of a list that has every node
-- seen tacked onto it
nodes :: Graph -> [Node]
nodes [] = []
nodes ((x,y):xs) = norm (x:y:nodes xs)

-- Finds the node and logs every node that it sees attached
-- to it
suc :: Node -> Graph -> [Node]
suc n [] = []
suc n ((x,y):xs)    | n == x = y:(suc n xs)
                    | n /= x = suc n xs

-- If it sees the values it looks for, then it
-- skips them, otherwise it tacks it onto the output
detach :: Node -> Graph -> Graph
detach n [] = []
detach n ((x,y):xs) | n == x || n == y  = detach n xs
                    | otherwise         = (x,y):(detach n xs)

-- creates a node for every (1,2), (2,3) ... (n-1, n)
innercyc :: Int -> Graph
innercyc x   | x > 0 = 
            if x /= 2
                then (innercyc (x-1)) ++ [(x-1, x)]
            else [(1,2)]

-- Calls innercyc and then tacks (n, 1) at the end
cyc :: Int -> Graph
cyc x   | x == 0 = []
        | x == 1 = [(1,1)]
        | otherwise = innercyc x ++ [(x,1)]

-- EXERCISE 3

-- Computes the width based on the type of shape
width :: Shape -> Length
width (Pt _)            = 0
width (Circle _ l)      = 2 * l
width ((Rect _ w _))    = w

-- Computes the bounding box based on the shape
bbox :: Shape -> BBox
bbox (Pt (x,y))         = ((x,y), (x,y))
bbox (Circle (x,y) l)   = ((x-l,y-l), (x+l,y+l))
bbox (Rect (x,y) w h)   = ((x,y), (x+w,y+h))

-- Gets the minimum x based on the shape
minX :: Shape -> Number
minX (Pt (x,_)) = x
minX (Circle (x,_) l) = x-l
minX (Rect (x,_) _ _) = x

-- Applies a vector to the shapes position
move :: Shape -> Point -> Shape
move (Pt (x,y)) (x1,y1) = Pt (x+x1,y+y1)
move (Circle (x,y) l) (x1,y1) = Circle (x+x1,y+y1) l
move (Rect (x,y) w h) (x1,y1) = Rect (x+x1,y+y1) w h
