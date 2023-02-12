-- Homework 3 template

module Sentence where

-- Grammar for the animal sentence language:
--
--   <sentence> ->  <noun> <verb> [<noun>]  
--               	|  <sentence> `and` <sentence>
--				 	
--   <noun> 	-> <adj> <noun> | <noun> `and` <noun>
--					| `cats` | `dogs` | `ducks` | `bunnies`

--   <verb>		->  `chase` | `cuddle` | `hug` | `scare`
--   <adj>		->	`silly` | `small` | `old` | `happy`

data Sentence
   = NVN Noun Verb Noun
   | NV Noun Verb 
   | And Sentence Sentence
   | End
  deriving (Eq,Show)

data Adj = Silly | Small | Old | Happy
  deriving (Eq,Show)

data Noun
    = NP Adj Noun  -- Noun phrase
    | NAnd Noun Noun  -- Finish noun and noun
	| Cats | Dogs | Ducks | Bunnies
  deriving (Eq,Show)

data Verb = Chase | Cuddle | Hug | Scare
  deriving (Eq,Show)


-- | The sentence: cats cuddle ducks and dogs cuddle ducks
ex1 :: Sentence
ex1 = NVN Cats Hug Dogs

ex2 :: Sentence
ex2 = NVN (NP Silly Cats) Hug Dogs

ex3 :: Sentence
ex3 = NVN (NAnd Dogs Cats) Chase Ducks

ex4 :: Sentence
ex4 = NVN (NAnd (NP Silly Dogs) Cats) Chase Ducks


-- | Build a sentence from a noun verb noun.
-- | buildS2 Cats Hug Cats
-- | NVN Cats Hug Cats

buildS2 :: Noun -> Verb -> Noun -> Sentence
buildS2 n v n1 = NVN n v n1

-- | Build a sentence from a noun verb 
-- | buildS1 Cats Hug 
-- | NV Cats Hug 

buildS1 :: Noun -> Verb ->Sentence
buildS1 n v = NV n v


-- | Build a noun phrase from an adjective and noun
-- | buildNP Silly Dogs
-- | NP Silly Dogs

buildNP :: Adj -> Noun -> Noun
buildNP a n = NP a n

-- | Build a noun conjunction from two nouns
-- | buildNAnd Dogs Cats
-- | NAnd Dogs Cats

buildNAnd :: Noun -> Noun -> Noun
buildNAnd n n1 = NAnd n n1

-- | Build a sentence that is a conjunction of a list of other sentences.
-- | conjunction [ex1, ex2]
-- | And (NVN Cats Hug Dogs) (NVN (NP Silly Cats) Hug Dogs)
--  
conjunction :: [Sentence] -> Sentence
conjunction []      = End
conjunction [x]     = x
conjunction (x:xs)  = And x (conjunction xs)

-- | Pretty print a sentence.
pretty :: Sentence -> String
pretty (NVN s v o) = prettyNoun s ++ " " ++ prettyVerb v ++ " " ++ prettyNoun o
pretty (And l r)   = pretty l ++ " and " ++ pretty r
pretty (NV s v)     = prettyNoun s ++ " " ++ prettyVerb v
pretty (End) = "."

-- | Pretty print a noun.
prettyNoun :: Noun -> String
prettyNoun Cats         = "cats"
prettyNoun Dogs         = "dogs"
prettyNoun Ducks        = "ducks"
prettyNoun Bunnies      = "bunnies"
prettyNoun (NP a n)     = prettyAdj a ++ " " ++ prettyNoun n
prettyNoun (NAnd m n)   = prettyNoun m ++ " and " ++prettyNoun n

-- | Pretty print a verb.
prettyVerb :: Verb -> String
prettyVerb Chase    = "chase"
prettyVerb Cuddle   = "cuddle"
prettyVerb Hug      = "hug"
prettyVerb Scare    = "scare"

-- | Pretty print an adjective.
prettyAdj :: Adj -> String
prettyAdj Silly     = "silly"
prettyAdj Small     = "small"
prettyAdj Old       = "old"
prettyAdj Happy     = "happy"

-- | Does the sentence contain only cuddling and hugs?
-- | isNice ex2
-- |   True
isNice :: Sentence -> Bool
isNice (NVN _ Chase _)  = False
isNice (NVN _ Cuddle _) = True
isNice (NVN _ Hug _)    = True
isNice (NVN _ Scare _)  = False
isNice (NV _ Chase)  = False
isNice (NV _ Cuddle) = True
isNice (NV _ Hug)    = True
isNice (NV _ Scare)  = False
isNice (And s1 s2) = (isNice s1) && (isNice s2)
isNice End = True

-- |Count the number of words in a sentence
-- | wordCount ex4
--    6

wordCount :: Sentence -> Int
wordCount ( And l r ) = (wordCount l) + (wordCount r) + 1
wordCount ( NVN n1 _ n2 ) = (wordCountP n1) + (wordCountP n2) + 1
wordCount ( NV n1 _ ) = (wordCountP n1) + 1
wordCount End = 0

wordCountP :: Noun -> Int
wordCountP ( NP _ n ) =  (wordCountP n) + 1
wordCountP ( NAnd n1 n2 ) = (wordCountP n1) + (wordCountP n2) + 1
wordCountP Cats = 1
wordCountP Dogs = 1
wordCountP Ducks = 1
wordCountP Bunnies = 1