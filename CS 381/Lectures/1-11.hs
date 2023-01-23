-- factorial
fact 0 = 1
fact n = n * fact (n-1)

-- maximum element in a list
maxList[a] = a
maxList (x:xs)
    | ( x > maxList (xs)) = x
    | otherwise = maxList xs