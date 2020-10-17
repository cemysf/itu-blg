-------------------------------------------------------------------------------
	       Software Tools for Discrete Mathematics
		   Cordelia Hall and John O'Donnell
-------------------------------------------------------------------------------

Last modified: June 2006

This software is intended to be used with the book "Discrete
Mathematics Using a Computer, Second Edition", by John O'Donnell,
Cordelia Hall, and Rex Page.  Published by Springer, 2006.

The software is written in Haskell 98, the standard functional
programming language.  It runs interactively under the Hugs 98 and the
ghci implementation.  Under Unix, you can start hugs with the command

  hugs -98

which tells it to use the standard Haskell 98 language, but not the
experimental language extensions.  Alternatively, you can use ghci.

Notice: the option -c may need to be modified so as this file be loaded.  -- *2
If there is problem when loading this file, use the command:              -- *2
                      :set "-c50"                                         -- *2

This software, and its documentation, can be downloaded from the book
web page:

	    www.dcs.gla.ac.uk/~jtod/discrete-mathematics/

It's a good idea to check the web page periodically to keep the
software up to date.

The program is a "literate script".  Each line that begins with "> "
is Haskell source code that can be executed; all other lines are
documentation which will be ignored by the compiler.


> module Stdm where

-------------------------------------------------------------------------------
			 Operator Precedence
-------------------------------------------------------------------------------

> infix 1 <=>
> infix 2 ==>
> infix 3 \/
> infix 4 /\
> infix 3 +++
> infix 4 ~~~
> infix 4 ***
> infix 5 !!!

-------------------------------------------------------------------------------
		   Chapter 2.  Propositional Logic
-------------------------------------------------------------------------------


> (<=>) :: Bool -> Bool -> Bool
> (<=>) a b = a == b

> (==>) :: Bool -> Bool -> Bool
> (==>) True False = False
> (==>) a b = True

> (\/) = (||)

> (/\) = (&&)

-------------------------------------------------------------------------------
  A Mini-tutorial on Using the Proof Checker for Propositional Logic
-------------------------------------------------------------------------------

And Introduction
~~~~~~~~~~~~~~~~

Here is a theorem and a valid proof using the And Introduction rule:

Theorem AI1.  q,r  |-  q&r

> thAI1 = Theorem [Q,R] (Q `And` R)
> prAI1 = AndI (Assume Q, Assume R) (And Q R)

To check that Proof prAI1 is a valid proof of Theorem thAI1, execute
the following expression interactively:

	check_proof thAI1 prAI1

The next theorem is similar, but it's incorrect because Q `And` S
doesn't follow from assuming Q and R.

Theorem AI2.  q,r  |-  q&s

Here are the theorem and an invalid proof of it, using the And
Introduction rule incorrectly.

> thAI2 = Theorem [Q,R] (Q `And` S)
> prAI2 =
>   AndI (Assume Q, Assume R)
>        (And Q S)

Try it out with the proof checker by evaluating the following
interactively:

	check_proof thAI2 prAI2

And Elimination (Left)
~~~~~~~~~~~~~~~~~~~~~~

Here is a theorem and a valid proofs using And Elimination (Left).
Test it by evaluating

	check_proof thAEL1 prAEL1

Theorem AEL1.  p&q |-  p

> thAEL1 = Theorem [P `And` Q] P
> prAEL1 = AndEL (Assume (And P Q)) P

This is a slightly more complex theorem, again with a valid proof
using And Elimination (Left).  Check it with

	check_proof thAEL2 prAEL2

Theorem AEL2.  (P|Q)&R |- (P|Q)

> thAEL2 = Theorem [(P `Or` Q) `And` R] (P `Or` Q)
> prAEL2 = AndEL (Assume (And (Or P Q) R)) (Or P Q)

Now we try some invalid proofs.  Consider the following theorem, the
theorem itself is valid but its proof is incorrect.  Check it by
evaluating the expression check_AEL3; the proof checker will tell you
exactly what is wrong with the proof.  Notice that we're moving to a
slightly more concise style, where we aren't naming both the theorem
and the proof separately.

Theorem AEL3.  p&q |-  p

> check_AEL3 =
>   check_proof
>     (Theorem [P `And` Q] P)
>    (AndEL (Assume (Or P Q)) P)

> p6 = -- p&q  |-  p
>   AndEL (Assume (And P Q)) Q
> p7 = -- P&Q  |-  R
>   AndEL (Assume (And P Q)) R

And Elimination (Right)
~~~~~~~~~~~~~~~~~~~~~~~

The following theorem and proof are correct; they are the mirror image
of the AEL1 example above.

> check_AER1 =
>   check_proof
>     (Theorem [P `And` Q] Q)
>     (AndER (Assume (P `And` Q)) Q)

This example is similar; the theorem is ok and the proof would be
valid if it used the AndEL rule, but the AndER rule does not justify
the conclusion, so the proof fails to establish the theorem.

> check_AER2 =
>   check_proof
>     (Theorem [P `And` Q] Q)
>     (AndER (Assume (P `And` Q)) P)

Imply Introduction
~~~~~~~~~~~~~~~~~~

Theorem II1.  Q |- P => P&Q

> check_II1 =
>   check_proof
>     (Theorem [Q] (P `Imp` (P `And` Q)))
>     (ImpI (AndI (Assume P, Assume Q)
>                 (And P Q))
>           (Imp P (And P Q)))


Theorem II2.  |- Q => (P => (P&Q))

> check_II2 =
>   check_proof
>     (Theorem [] (Q `Imp` (P `Imp` (P `And` Q))))
>     (ImpI (ImpI (AndI (Assume P, Assume Q)
>                       (And P Q))
>                 (Imp P (And P Q)))
>           (Imp Q (Imp P (And P Q))))

Imply Elimination
~~~~~~~~~~~~~~~~~

Theorem IE1.  P, P=>Q  |-  Q

> check_IE1 =
>   check_proof
>     (Theorem [P, P `Imp` Q] Q)
>     (ImpE (Assume P, Assume (Imp P Q))
>           Q)


Or Introduction (Left)
~~~~~~~~~~~~~~~~~~~~~~

Theorem OEL1.  P&Q |- P&Q \/ S&P

> check_OIL1 =
>   check_proof
>     (Theorem [P `And` Q, Q `And` R]
>              ((P `And` Q) `Or` (S `And` P)))
>     (OrIL (Assume (P `And` Q))
>           ((P `And` Q) `Or` (S `And` P)))

Or Introduction (Right)
~~~~~~~~~~~~~~~~~~~~~~~

Theorem OIR1.  ~S |- P \/ ~S

> check_OIR1 =
>   check_proof
>     (Theorem [Not S] (P `Or` (Not S)))
>     (OrIR (Assume (Not S))
>           (P `Or` (Not S)))

Identity
~~~~~~~~

> check_ID0 =
>   check_proof
>     (Theorem [P `And` Q] (P `And` Q))
>     (Assume (P `And` Q))

Now the same is proved using the ID inference rule.

Theorem ID1.  P&Q |- P&Q

> check_ID1 =
>   check_proof
>     (Theorem [P `And` Q] (P `And` Q))
>     (ID (Assume (P `And` Q)) (P `And` Q))
 

Contradiction
~~~~~~~~~~~~~

Theorem CTR1.  False |- P & ~P

> check_CTR1 =
>   check_proof
>     (Theorem [FALSE] (P `And` (Not P)))
>     (CTR (Assume FALSE) (P `And` (Not P)))

The next theorem isn't valid, because the premise P isn't enough to
establish P & ~P, and it isn't FALSE so the Contradiction inference
rule doesn't apply.

Theorem CTR2.  P |- P & ~P

> check_CTR2 =
>   check_proof
>     (Theorem [P] (P `And` (Not P)))
>     (CTR (Assume P) (P `And` (Not P)))

Reductio ab Absurdum
~~~~~~~~~~~~~~~~~~~~

Theorem RAA1.  ~~P |- P

> check_RAA1 =
>   check_proof
>     (Theorem [P `Imp` FALSE, (P `Imp` FALSE) `Imp` FALSE]
>              P)
>     (RAA (ImpE (Assume (P `Imp` FALSE),
>                Assume ((P `Imp` FALSE) `Imp` FALSE))
>                FALSE)
>          P)

Examples from the book
~~~~~~~~~~~~~~~~~~~~~~

Here is the theorem and  proofs that are used in the book;
run them like this:
   check_proof example_theorem example_proof1     (should be valid)
   check_proof example_theorem example_proof2     (should give error message)

> example_theorem :: Theorem
> example_theorem =
>   Theorem
>     []
>     (Imp Q (Imp (And P R) (And R Q)))

> example_proof1 =
>   ImpI
>     (ImpI
>        (AndI
>           ((AndER
>               (Assume (And P R))
>               R),
>             Assume Q)
>           (And R Q))
>        (Imp (And P R) (And R Q)))
>     (Imp Q (Imp (And P R) (And R Q)))

The following proof is incorrect proof, because Q^R was inferred where
R^Q was needed.

> example_proof2 =
>   ImpI
>     (ImpI
>        (AndI
>           (Assume Q,
>            (AndER
>               (Assume (And P R))
>               R))
>           (And R Q))
>        (Imp (And P R) (And R Q)))
>     (Imp Q (Imp (And P R) (And R Q)))


-------------------------------------------------------------------------------
     Implementation of the Proof Checker for Propositional Logic
-------------------------------------------------------------------------------

> data Prop
>   = FALSE
>   | TRUE
>   | A | B | C | D | E | G | H | I | J | K | L | M
>   | N | O | P | Q | R | S | U | V | W | X | Y | Z
>   | Pvar String
>   | And Prop Prop
>   | Or Prop Prop
>   | Not Prop
>   | Imp Prop Prop
>   deriving Show      -- Eq is not derived anymore, but completly defined-- *1

> data Theorem
>   = Theorem [Prop] Prop
>   deriving (Eq,Show)

> type TheoremDB = [String]  -- a representation of all the known theorems-- *2

> data Proof
>   = Assume Prop
>   | AndI (Proof,Proof) Prop
>   | AndEL Proof Prop
>   | AndER Proof Prop
>   | OrIL Proof Prop
>   | OrIR Proof Prop
>   | OrE (Proof,Proof,Proof) Prop
>   | ImpI Proof Prop
>   | ImpE (Proof,Proof) Prop
>   | ID Proof Prop
>   | CTR Proof Prop
>   | RAA Proof Prop
>   | Use Theorem [Proof] Prop                                            -- *2
>   | UseTh (Theorem,Proof) [Proof] Prop                                  -- *2
>   | UseDB Theorem [Proof] Prop                                          -- *2
>   deriving (Eq,Show)

When a proof is checked, several pieces of information are gathered
together into a data structure called Status.

> type Status =
>   (Bool,       -- True iff the proof is valid
>    [String],   -- messages describing errors found in the proof
>    [Prop],     -- undischarged assumptions required by the proof
>    Prop)       -- conclusion

The following type is used for comparisons, with the ordering on the
propositions

> data Comparison = Lesser | Equal | Greater deriving Eq

-------------------- definition of the Eq for a Prop ------------------------ *1

> instance Eq Prop where                                                  -- *1
> -- the basic definitions for the equality:                              -- *1
>    (==) FALSE       FALSE             = True                            -- *1
>    (==) TRUE        TRUE              = True                            -- *1
>    (==) A           A                 = True                            -- *1
>    (==) B           B                 = True                            -- *1
>    (==) C           C                 = True                            -- *1
>    (==) D           D                 = True                            -- *1
>    (==) E           E                 = True                            -- *1
>    (==) G           G                 = True                            -- *1
>    (==) H           H                 = True                            -- *1
>    (==) I           I                 = True                            -- *1
>    (==) J           J                 = True                            -- *1
>    (==) K           K                 = True                            -- *1
>    (==) L           L                 = True                            -- *1
>    (==) M           M                 = True                            -- *1
>    (==) N           N                 = True                            -- *1
>    (==) O           O                 = True                            -- *1
>    (==) P           P                 = True                            -- *1
>    (==) Q           Q                 = True                            -- *1
>    (==) R           R                 = True                            -- *1
>    (==) S           S                 = True                            -- *1
>    (==) U           U                 = True                            -- *1
>    (==) V           V                 = True                            -- *1
>    (==) W           W                 = True                            -- *1
>    (==) X           X                 = True                            -- *1
>    (==) Y           Y                 = True                            -- *1
>    (==) Z           Z                 = True                            -- *1
>    (==) (Pvar x1)   (Pvar x2)         = x1 == x2                        -- *1
>    (==) (And x1 y1) (And x2 y2)       = (x1 == x2) && (y1 == y2)        -- *1
>    (==) (Or x1 y1)  (Or x2 y2)        = (x1 == x2) && (y1 == y2)        -- *1
>    (==) (Not x)     (Not y)           = (x == y)                        -- *1
>    (==) (Imp x1 y1) (Imp x2 y2)       = (x1 == x2) && (y1 == y2)        -- *1
>                                                                         -- *1
> -- the definitions of (Not A) and TRUE                                  -- *1
>    (==) TRUE        y                 = (Imp FALSE FALSE) == y          -- *1
>    (==) x           TRUE              = x == (Imp FALSE FALSE)          -- *1
>    (==) (Not x)     y                 = ((Imp x FALSE) == y)            -- *1
>    (==) x           (Not y)           = (x == (Imp y FALSE))            -- *1
>                                                                         -- *1
> -- all other cases: there is not equality:                              -- *1
>    (==) _           _                 = False                           -- *1
>                                                                         -- *1
> -- definition of inequality, very basic...                              -- *1
>    (/=) x y = not (x == y)                                              -- *1

----------------------------- auxilary functions ---------------------------- *
 
  'setelem' was deleted (use 'elem' instead)                              -- *
  'jsubset' was deleted, and it's not needed anymore                      -- *

> union :: Eq a => [a] -> [a] -> [a]                                       
> union xs ys = xs ++ [y | y <- ys, notElem y xs]                         -- *

> setdif :: Eq a => [a] -> [a] -> [a]
> setdif xs ys = [x | x <- xs, notElem x ys]                              -- *

> putmessages :: [String] -> IO ()                                        -- *
> putmessages []     = return ()                                          -- *
> putmessages (x:xs) = do putStr (" ." ++ x)                              -- *
>                         putmessages xs                                  -- *

> putassumptions :: [Prop] -> IO ()                                       -- *
> putassumptions []     = return ()                                       -- *
> putassumptions (x:[]) = do putStr (show x)                              -- *
>                            putassumptions []                            -- *
> putassumptions (x:xs) = do putStr (show x ++ ", ")                      -- *
>                            putassumptions xs                            -- *

------------------------------ the proof-checker ---------------------------- *

  the following 'check_proof' is equivalent to the 'check_proof' of the   -- *2
  previous versions.                                                      -- *2

> check_proof :: Theorem -> Proof -> IO ()                                -- *2
> check_proof t p =                                                       -- *2
>   do check_proof_with_db [] t p                                         -- *2
>      return ()                                                          -- *2

  'check_proof_with_db' allows to use theorems stored in a data-base      -- *2

> check_proof_with_db :: TheoremDB -> Theorem -> Proof -> IO (Bool)       -- *2
> check_proof_with_db db (Theorem thas thc) proof =                       -- *2
>   do let (valid, ms, uda, concl) = traverse db proof                    -- *2
>      let missingassum = setdif uda thas                                 -- *
>      let uselessassum = setdif thas uda                                 -- *
>      let allok = valid && (missingassum == []) && (concl == thc)        -- *
>      if allok                                                           -- *
>        then do putStr "The proof is valid\n"                            -- *
>                if (uselessassum == [])                                  -- *
>                  then putStr ""                                         -- *
>                  else do putStr "notice: these assumptions are useless: "-- *
>                          putassumptions uselessassum                    -- *
>                          putStr "\n"                                    -- *
>        else do putStr "*** The proof is NOT valid ***\n"                -- *
>                if valid                                                 -- *
>                  then do putStr "The proof does not match the sequent.\n"-- *
>                          putStr " .what is actually proved is:\n      " -- *
>                          putassumptions uda                             -- *
>                          putStr ("  |-  " ++ show concl ++ "\n")        -- *
>                          if (missingassum == [])                        -- *
>                            then putStr ""                               -- *
>                            else do putStr (" .these assumptions are used"-- *
>                                           ++ " but not part of the sequ"-- *
>                                           ++ "ent:\n      ")            -- *
>                                    putassumptions missingassum          -- *
>                                    putStr "\n"                          -- *
>                  else do if (ms == [])                                  -- *
>                            then putStr ""                               -- *
>                            else do putStr "Reported errors:\n"          -- *
>                                    putmessages ms                       -- *
>      return (allok)                                                     -- *2

The real work is performed in the traverse function, which has a
separate case for checking each inference rule.  Nearly all the
complexity in the following code results from an attempt to provide
meaningful error messages; if the aim were merely to decide whether a
proof is valid, then the implementation could rely much more on
Haskell's pattern matching mechanism, and everything would be much
more concise.

> traverse :: TheoremDB -> Proof -> Status                                -- *2

> traverse _ (Assume a) = (True, [], [a], a)                              -- *2

> traverse db (AndI (a,b) c) =                                            -- *2
>   let (avalid, amsgs, auda, aconcl) = traverse db a                     -- *2
>       (bvalid, bmsgs, buda, bconcl) = traverse db b                     -- *2
>       (ok, msg) =                                                       -- *
>         case c of                                                       -- *
>	    And p q -> if (p==aconcl) && (q==bconcl)                      -- *
>                        then (True, [])                                  -- *
>                        else (False, [err1])                             -- *
>           otherwise -> (False, [err2])                                  -- *
>       err1 = "AndI: the conclusion (" ++ show c ++ ") is not the "      -- *
>              ++ "logical And of the assumption (" ++ show aconcl        -- *
>              ++ ") with the assumption (" ++ show bconcl ++ ")\n"       -- *
>       err2 = "AndI: the conclusion (" ++ show c ++ ") is not an "       -- *
>              ++ "And expression\n"                                      -- *
>       valid = avalid && bvalid && ok
>       msgs = amsgs ++ bmsgs ++ msg                                      -- *
>       uda = auda `union` buda
>   in  (valid, msgs, uda, c)

> traverse db (AndEL a b) =                                               -- *2
>   let (avalid, amsgs, auda, aconcl) = traverse db a                     -- *2
>       (ok,msg) =
>         case aconcl of
>           And p q -> if p == b then (True,[])
>                                else (False, [err1])
>           otherwise -> (False, [err2])
>       err1 = "AndEL: the left term of And assumption (" ++ show aconcl  -- *
>              ++ ") doesn't match the conclusion (" ++ show b ++  ")\n"  -- *
>       err2 = "AndEL: the assumption (" ++ show aconcl ++ ") is not an " -- *
>              ++ "And expression\n"                                      -- *
>       valid = avalid && ok
>       msgs = amsgs ++ msg
>       uda = auda
>   in (valid, msgs, uda, b)

> traverse db (AndER a b) =                                               -- *2
>   let (avalid, amsgs, auda, aconcl) = traverse db a                     -- *2
>       (ok,msg) =
>         case aconcl of
>           And p q -> if q == b then (True,[])
>                                else (False, [err1])
>           otherwise -> (False, [err2])
>       err1 = "AndER: the right term of And assumption (" ++ show aconcl -- *
>              ++ ") doesn't match the conclusion (" ++ show b ++  ")\n"  -- *
>       err2 = "AndER: the assumption (" ++ show aconcl ++ ") is not an " -- *
>              ++ "And expression\n"                                      -- *
>       valid = avalid && ok
>       msgs = amsgs ++ msg
>       uda = auda
>   in (valid, msgs, uda, b)

> traverse db (OrIL a b) =                                                -- *2
>   let (avalid, amsgs, auda, aconcl) = traverse db a                     -- *2
>       (ok,msg) =                                                        -- *
>         case b of
>           Or p q -> if aconcl == p then (True,[])
>                                    else (False,[err1])
>           otherwise -> (False,[err2])
>       err1 = "OrIL: the left term of OR conclusion (" ++ show b         -- *
>              ++ ") doesn't match the assumption (" ++ show aconcl       -- *
>              ++ ")\n"                                                   -- *
>       err2 = "OrIL: the conclusion (" ++ show b ++ ") is not an Or "    -- *
>              ++ "expression\n"                                          -- *
>       valid = avalid && ok
>       msgs = amsgs ++ msg                                               -- *
>       uda = auda
>   in (valid, msgs, uda, b)

> traverse db (OrIR a b) =                                                -- *2
>   let (avalid, amsgs, auda, aconcl) = traverse db a                     -- *2
>       (ok,msg) =                                                        -- *
>         case b of
>           Or p q -> if aconcl == q then (True,[])
>                                    else (False,[err1])
>           otherwise -> (False,[err2])
>       err1 = "OrIL: the right term of OR conclusion (" ++ show b        -- *
>              ++ ") doesn't match the assumption (" ++ show aconcl       -- *
>              ++ ")\n"                                                   -- *
>       err2 = "OrIL: the conclusion (" ++ show b ++ ") is not an Or "    -- *
>              ++ "expression\n"                                          -- *
>       valid = avalid && ok
>       msgs = amsgs ++ msg                                               -- *
>       uda = auda
>   in (valid, msgs, uda, b)

> traverse db (OrE (a,b,c) d) =                                           -- *2
>   let (avalid, amsgs, auda, aconcl) = traverse db a                     -- *2
>       (bvalid, bmsgs, buda, bconcl) = traverse db b                     -- *2
>       (cvalid, cmsgs, cuda, cconcl) = traverse db c                     -- *2
>       (ok,msg,uda) =                                                    -- *
>         case aconcl of                                                  -- *
>           Or p q -> let ok2 = p `elem` buda                             -- *
>                         ok3 = q `elem` cuda                             -- *
>                         ok4 = bconcl == cconcl                          -- *
>                         ok5 = bconcl == d                               -- *
>                     in if ok2 && ok3 && ok4 && ok5                      -- *
>                          then (True,[], auda `union` (buda `setdif` [p])-- *
>                                              `union` (cuda `setdif` [q]))-- *
>                        else (False,                                     -- *
>                              (if ok2 then [] else [err2 p])             -- *
>                              ++ (if ok3 then [] else [err3 q])          -- *
>                              ++ (if ok4 then if ok5 then [] else [err5] -- *
>            			   else [err4]),                          -- *
>                              auda `union` buda `union` cuda)            -- *
>           otherwise -> (False, [err1],                                  -- *
>                         auda `union` buda `union` cuda)                 -- *
>       err1 = "OrE: the first term above line (" ++ show aconcl          -- *
>              ++ ") is not an Or expression\n"                           -- *
>       err2 x = "OrE: the left term (" ++ show x ++ ") of the first "    -- *
>                ++ "term above line (" ++ show aconcl ++ ") is not an "  -- *
>                ++ "undischarged assumption of the  proof of the second "-- *
>                ++ "term above line (" ++ show bconcl ++ ")\n"           -- *
>       err3 x = "OrE: the right term (" ++ show x ++ ") of the first "   -- *
>                ++ "term above line (" ++ show aconcl ++ ") is not an "  -- *
>                ++ "undischarged assumption of the proof of the third "  -- *
>                ++ "term above line (" ++ show bconcl ++ ")\n"           -- *
>       err4 = "OrE: the conclusion of the second term above line ("      -- *
>              ++ show bconcl ++ ") doesn't match the conclusion of the " -- *
>              ++ "third term above line (" ++ show cconcl ++ ")\n"       -- *
>       err5 = "OrE: the conclusion (" ++ show d ++ ") doesn't match the "-- *
>              ++ "conclusion of the second and third terms above line (" -- *
>              ++ show bconcl ++ ")\n"                                    -- *
>       valid = avalid && bvalid && cvalid && ok                          -- *
>       msgs = amsgs ++ bmsgs ++ cmsgs ++ msg                             -- *
>   in (valid, msgs, uda, d)                                              -- *

> traverse db (ImpI a b) =                                                -- *2
>   let (avalid, amsgs, auda, aconcl) = traverse db a                     -- *2
>       (ok,msg) = match b                                                -- *1
>       match x =                                                         -- *1
>         case x of                                                       -- *1
>           Imp p q -> if p `elem` auda && aconcl==q                      -- *
>                        then (True,[])
>                      else if not (p `elem` auda) && aconcl==q           -- *
>                        then (False,[err2])
>                      else if p `elem` auda && aconcl/=q                 -- *
>                        then (False,[err3])
>                      else (False,[err2,err3])
>           Not p -> match (Imp p FALSE)                                  -- *1
>           FALSE -> match (Imp TRUE TRUE)                                -- *1
>           otherwise -> (False,[err1])
>       err1 = "ImpI: the conclusion (" ++ show b ++ ") is not an "       -- *
>              ++ "implication\n"                                         -- *
>       err2 = "ImpI: the antecedent in (" ++ show b ++ ") is not an "    -- *
>              ++ "undischarged assumption above line\n"                  -- *
>       err3 = "ImpI: the conclusion in (" ++ show b ++ ") doesn't match "-- *
>              ++ "the conclusion above line (" ++ show aconcl ++ ")\n"   -- *
>       valid = avalid && ok
>       msgs = amsgs ++ msg                                               -- *
>       uda = case b of
>               Imp p q -> auda `setdif` [p]
>               Not p   -> auda `setdif` [p]                              -- *1
>               FALSE   -> auda `setdif` [TRUE]                           -- *1
>               otherwise -> auda
>   in (valid, msgs, uda, b)

> traverse db (ImpE (a,b) c) =                                            -- *2
>   let (avalid, amsgs, auda, aconcl) = traverse db a                     -- *2
>       (bvalid, bmsgs, buda, bconcl) = traverse db b                     -- *2
>       (ok,msg) = match bconcl                                           -- *1
>       match x =                                                         -- *1
>         case x of                                                       -- *1
>           Imp p q ->if aconcl==p && c==q
>                       then (True,[])
>                     else if aconcl/=p && c==q
>                       then (False,[err2])
>                     else if aconcl==p && c/=q
>                       then (False,[err3])
>                     else (False,[err2,err3])
>           Not p -> match (Imp p FALSE)                                  -- *1
>           FALSE -> match (Imp TRUE TRUE)                                -- *1
>           otherwise -> (False,[err1])
>       err1 = "ImpE: second term above line (" ++ show bconcl            -- *
>              ++ ") is not an implication\n"                             -- *
>       err2 = "ImpE: first term (" ++ show aconcl ++ ") doesn't match "  -- *
>              ++ " the antecedent of the second term (" ++ show bconcl   -- *
>              ++ ")\n"                                                   -- *
>       err3 = "ImpE: the conclusion (" ++ show c ++ ") doesn't match "   -- *
>              ++ "the conclusion of the second term (" ++ show bconcl    -- *
>              ++ ")\n"
>       valid = avalid && bvalid && ok
>       msgs = amsgs ++ bmsgs ++ msg                                      -- *
>       uda = auda `union` buda
>   in (valid, msgs, uda, c)

> traverse db (ID a c) =                                                  -- *2
>   let (avalid, amsgs, auda, aconcl) = traverse db a                     -- *2
>       (ok,msg) = if aconcl == c                                         -- *
>                    then (True,[])
>                    else (False,[err1])
>       err1 = "ID: the conclusion (" ++ show c ++ ") doesn't match "     -- *
>              ++ "the antecedent (" ++ show aconcl ++ ")\n"              -- *
>       valid = avalid && ok
>       msgs = amsgs ++ msg                                               -- *
>       uda = auda                                                        -- *
>   in (valid, msgs, uda, c)                                              -- *

> traverse db (CTR a c) =                                                 -- *2
>   let (avalid, amsgs, auda, aconcl) = traverse db a                     -- *2
>       (ok,msg) = if aconcl == FALSE                                     -- *
>                   then (True,[])
>                   else (False,[err1])
>       err1 = "CTR: the antecedent (" ++ show aconcl ++ ") is not "      -- *
>              ++ "FALSE\n"                                               -- *
>       valid = avalid && ok
>       msgs = amsgs ++ msg                                               -- *
>       uda = auda                                                        -- *
>   in (valid, msgs, uda, c)                                              -- *

> traverse db (RAA a c) =                                                 -- *2
>   let (avalid, amsgs, auda, aconcl) = traverse db a                     -- *2
>       (ok,msg) = if not ((c `Imp` FALSE) `elem` auda)                   -- *
>                    then (False, [err1])
>                    else if aconcl /= FALSE
>                         then (False, [err2])
>                         else (True, [])
>       err1 = "RAA: the negation of the conclusion (" ++ show c          -- *
>              ++ ") is not an undischarged assumption of the proof "     -- *
>              ++ "above the line\n"                                      -- *
>       err2 = "RAA: the conclusion (" ++ show aconcl ++ ") of the proof "-- *
>              ++ "above the line is not FALSE\n"                         -- *
>       valid = avalid && ok
>       msgs = amsgs ++ msg                                               -- *
>       uda = auda `setdif` [(c `Imp` FALSE)]                             -- *
>   in (valid, msgs, uda, c)                                              -- *


(everything of chapter 2 that follows has been added as 2nd extension, and-- *2
 every line should be marked with-- *2)                                   -- *2

----------------------- traverse function for 'USE' ------------------------- *2

Use assumes that the theorem is correct

> traverse db (Use theo assums concl) =
>   let (oks, msgs, udas, concls) = checkproofs db assums
>       err2 = "Use: the theorem " ++ show theo ++ " cannot be applied "
>              ++ "with the assumptions " ++ show concls
>              ++ " and the conclusion ("++ show concl ++")\n"
>   in if not oks then (False, msgs, udas, concl)
>      else if (usetheorem theo concls concl) then 
>             (True, msgs, udas, concl)
>      else (False, msgs++[err2], udas, concl)

UseTh needs the proof of a theorem to check if it's valid and then can be used.

> traverse db (UseTh (theo,proof) assums concl) =
>       -- check if the theorem is valid
>   let (proofvalid, _, proofuda, proofconcl) = traverse db proof
>       (Theorem thas thc) = theo
>       missingassum = setdif proofuda thas
>       theook = proofvalid && (missingassum == []) && (proofconcl == thc)
>       -- check if the assumptions of the theorems are valid
>       (oks, msgs, udas, concls) = checkproofs db assums
>       err1 = "UseTh: the proof of the theorem " ++ show theo
>              ++ " is not valid and then the theorem cannot be used\n"
>       err2 = "UseTh: the theorem " ++ show theo ++ " cannot be applied "
>              ++ "with the assumptions " ++ show concls
>              ++ " and the conclusion ("++ show concl ++")\n"
>   in if not theook
>        then (False, msgs++[err1], udas, concl)
>      else if not oks then (False, msgs, udas, concl)
>      else if (usetheorem theo concls concl) then 
>             (True, msgs, udas, concl)
>      else (False, msgs++[err2], udas, concl)

UseDB checks if a theorem can be used by looking for it in a data-base

> traverse db (UseDB theo assums concl) =
>   let (oks, msgs, udas, concls) = checkproofs db assums
>       err1 = "UseDB: there is no known theorem of which name is "
>              ++ show theo ++ "\n"
>       err2 = "UseDB: the theorem " ++ show theo ++ " cannot be applied "
>              ++ "with the assumptions " ++ show concls
>              ++ " and the conclusion ("++ show concl ++")\n"
>   in if not (findtheorem db theo)
>        then (False, msgs++[err1], udas, concl)
>      else if not oks then (False, msgs, udas, concl)
>      else if (usetheorem theo concls concl) then 
>             (True, msgs, udas, concl)
>      else (False, msgs++[err2], udas, concl)

----------------------- the functions to use a theorem ---------------------- *2

the function 'checkproof' check the proofs of every assumptions of the
theorem, and return the list of the conclusions of these proofs, with
their validity, the error messages and the undischarged assumptions

> checkproofs :: TheoremDB -> [Proof] -> (Bool, [String], [Prop], [Prop])
> checkproofs _ [] = (True, [], [], [])
> checkproofs db (x:xs) =
>   let (okx,  msgx,  udasx,  cclx)  = traverse db x
>       (okxs, msgxs, udasxs, cclxs) = checkproofs db xs
>   in (okx && okxs, msgx ++ msgxs, udasx `union` udasxs, cclx:cclxs)

the function 'usetheorem' checks if a theorem can be applied with the given
assumption to reach the given conclusion. Actually, the work is mainly
performed by the functions 'unification' and 'allunifications'

> usetheorem :: Theorem -> [Prop] -> Prop -> Bool
> usetheorem theo assums concl =
>   let (Theorem thassums thconcl) = theo
>       (okconcl, _, unifconcl) = unif thconcl concl
>   in (length thassums == length assums) &&      -- must be of same length
>      (okconcl) &&                               -- conclusions must match
>      ((unification unifconcl thassums assums)
>       || (allunifications unifconcl thassums assums))

the function 'unification' try to match the atoms of the first list of
proposition with sub-propositions of the second list. The propositions are
taken in the order they appear within the lists. The first argument is a
list of already matched pairs.
The 2 list are assumed to be of the same length.

> unification :: [(Prop, Prop)] -> [Prop] -> [Prop] -> Bool
> unification initialpairs l1 l2 =
>   let (ok, _) = unifrec l1 l2 in ok
>   where
>     unifrec :: [Prop] -> [Prop] -> (Bool, [(Prop, Prop)])
>     unifrec [] [] = (True, initialpairs)
>     unifrec (x:xs) (y:ys) = 
>       let (okxy, _, unifxy) = unif x y
>           (oks, unifs) = if okxy then (unifrec xs ys)
>                          else (False, [])
>           (oku,  unifu) = if oks then addunif unifxy unifs
>                           else (False, [])
>       in (oku, unifu)

the function 'allunifiactions' is a kind of extended version of 'unification':
now, the order of the propositions does not matter, since every permutation may
be considered. 

> allunifications :: [(Prop, Prop)] -> [Prop] -> [Prop] -> Bool
> allunifications initialpairs l1 l2 =
>   let (ok,_) = allunifrec (order l1) ([],(order l2)) initialpairs in ok
>   where
>     allunifrec :: [Prop] -> ([Prop],[Prop]) -> [(Prop,Prop)]
>                                             -> (Bool, [(Prop,Prop)])
>     allunifrec []    ([],[]) pairs = (True, pairs)
>     allunifrec (_:_) (_, []) _     = (False, [])
>
>     allunifrec (x:xs) (prev, (y:ys)) pairs = 
>           let (okxy, eqxy, unifxy) = unif x y
>           in if okxy then
>                let (oku, unifu) = addunif pairs unifxy
>                in if not oku then trynext
>                   else let (oks, unifs) = allunifrec xs ([], prev++ys) unifu
>                        in if not oks then trynext else (oks, unifs)
>              else
>                if eqxy == Greater then (False, [])
>                else trynext
>           where
>             trynext = allunifrec (x:xs) (prev++[y], ys) pairs
>    
>     allunifrec _ _ _ = (False, [])

unification of 2 propositions: the function 'unif'
. the Bool-value returned is True iff the unification succeeded
. the Comparison-value returned is the comparison between the 2 trees of the
  propositions (cf 'comparison')
. the list returned is the list of the matching pairs

> unif :: Prop -> Prop -> (Bool, Comparison, [(Prop, Prop)])
> unif x y =
>   case x of
>     TRUE    -> if y == TRUE  then (True, Equal, [])
>                else (False, comparison x y, [])
>     FALSE   -> if y == FALSE then (True, Equal, [])
>                else (False, comparison x y, [])
>     And a b -> case y of
>                  And c d -> unifacbd a c b d
>                  otherwise -> (False, comparison x y, [])
>     Or a b  -> case y of
>                  Or c d  -> unifacbd a c b d
>                  otherwise -> (False, comparison x y, [])
>     Not a   -> case y of
>                  Not b       -> unif a b
>                  Imp b FALSE -> unif a b
>                  otherwise -> (False, comparison x y, [])
>     Imp a b -> case y of
>                  Imp c d -> unifacbd a c b d
>                  Not c   -> if b == FALSE then unif a c
>                             else (False, comparison x y, [])
>                  otherwise -> (False, comparison x y, [])
>     _       -> (True, Equal, [(x,y)])
>  where
>      unifacbd a c b d =
>         let (okac, eqac, unifac) = unif a c
>             (okbd, eqbd, unifbd) = unif b d
>             (oku,  unifu)  = addunif unifac unifbd
>             eqacbd = if (eqac /= Equal) then eqac else eqbd
>         in if oku then (True, eqacbd, unifu) else (False, eqacbd, [])

'addunif' performs the union of 2 sets of matching pairs, and checks whether
there is a conflict

> addunif :: [(Prop,Prop)] -> [(Prop, Prop)] -> (Bool, [(Prop,Prop)])
> addunif xs [] = (True, xs)
> addunif xs (y:ys) =
>  let (exp,val) = y
>      setexp = [v | (y,v) <- xs, y == exp]
>  in if setexp == [] then addunif (y:xs) ys
>     else if val == head setexp then addunif xs ys
>     else (False, [])

comparison of 2 trees of proposition, with 3 possible values.
the order is:
    And > Or > Imp > FALSE > (variable)
when its the same operator, the left sub-tree is considered first.
for TRUE and Not, their definitions are used.

> comparison :: Prop -> Prop -> Comparison
> comparison a b =
>   case (a,b) of
>     -- definitions of Not and TRUE:
>     (Not x,     _)         -> comparison (x `Imp` FALSE) b
>     (_,         Not y)     -> comparison a (y `Imp` FALSE)
>     (TRUE,      _)         -> comparison (FALSE `Imp` FALSE) b
>     (_,         TRUE)      -> comparison a (FALSE `Imp` FALSE)
> 
>      -- equality:
>     (FALSE,     FALSE)     -> Equal
>     (Imp x1 x2, Imp y1 y2) -> comparison2 x1 y1 x2 y2
>     (Or x1 x2,  Or y1 y2)  -> comparison2 x1 y1 x2 y2
>     (And x1 x2, And y1 y2) -> comparison2 x1 y1 x2 y2
> 
>     -- inequality (from the greatest to the least):
>     (And _ _,   _)         -> Greater
>     (_,         And _ _)   -> Lesser
>     (Or _ _,    _)         -> Greater
>     (_,         Or _ _)    -> Lesser
>     (Imp _ _,   _)         -> Greater
>     (_,         Imp _ _)   -> Lesser
>     (FALSE,     _)         -> Greater
>     (_,         FALSE)     -> Lesser
> 
>     -- equality of tree (2 variables):
>     (_,         _)         -> Equal
>  where
>    comparison2 x1 y1 x2 y2 =
>       let comp1 = comparison x1 y1
>       in if (comp1 /= Equal) then comp1 else (comparison x2 y2)

the function 'order' sorts proposition from the greatest to the least,
according to the function 'comparison'
(note: the result depends on the initial list, since 2 differents propositions
may be considered equal as 'comparison' compares trees not values)

> order :: [Prop] -> [Prop]
> order [] = []
> order (x:xs) = (order greater_egal) ++ [x] ++ (order lesser)
>   where
>     (lesser, greater_egal) = split xs ([],[])
>     split []     (le,g) = (le,g)
>     split (y:ys) (le,g) =
>       split ys (if (comparison y x == Lesser)
>                    then (y:le,   g)
>                    else (  le, y:g))

----------------------- functions to use the data-base ---------------------- *2

the function 'findtheorem' looks if a theorem belongs to the data-base of known
theorems.

> findtheorem :: TheoremDB -> Theorem -> Bool
> findtheorem db t =
>   case db of
>     []     -> False
>     (x:xs) -> x == s || findtheorem xs t
>   where s = namefor t

the function 'namefor' give a name (String) to a theorem, which does not 
depend on the name given to the variables of the theorem. For example,
(Theorem [A,B] (B `And` A)) and (Theorem [C,D] (D `And` C)) will receive
the same name.

> namefor :: Theorem -> String
> namefor t =
>   let (Theorem assums concl) = t
>       names = name (concl:assums)
>   in write assums names ++ " |- " ++ write [concl] names
>   where
>     name :: [Prop] -> [(Prop,Int)]
>     name xs = zip (atoms xs) [1..]
>       where
>         atoms :: [Prop] -> [Prop]
>         atoms [] = []
>         atoms (x:xs) =
>           case x of
>               TRUE  -> atoms xs
>               FALSE -> atoms xs
>               And p q -> ((atoms [p]) `union` (atoms [q])) `union` (atoms xs)
>               Or  p q -> ((atoms [p]) `union` (atoms [q])) `union` (atoms xs)
>               Imp p q -> ((atoms [p]) `union` (atoms [q])) `union` (atoms xs)
>               Not p   -> (atoms [p]) `union` (atoms xs)
>               _       -> [x] `union` (atoms xs)
>
>     write :: [Prop] -> [(Prop,Int)] -> String
>     write [] _ = ""
>     write (x:[]) names = writeprop x names
>     write (x:xs) names = writeprop x names ++ ", " ++ write xs names
>     
>     writeprop :: Prop -> [(Prop,Int)] -> String
>     writeprop x names =
>       case x of
>           TRUE  -> "T"
>           FALSE -> "F"
>           And p q -> "(And " ++ writeprop p names ++ " "
>                              ++ writeprop q names ++ ")"
>           Or  p q -> "(Or "  ++ writeprop p names ++ " "
>                              ++ writeprop q names ++ ")"
>           Imp p FALSE -> writeprop (Not p) names
>           Imp p q -> "(Imp " ++ writeprop p names ++ " "
>                              ++ writeprop q names ++ ")"
>           Not p   -> "(Not " ++ writeprop p names ++ ")"
>           _       -> show (head [s | (a,s) <- names, a == x])


the 2 following functions convert a String into a data-base, and vice-versa

> readtheorems :: String -> TheoremDB
> readtheorems = clear . lines
>   where clear [] = []
>         clear (x:xs) = if x=="" then clear xs else x:clear xs

> writetheorems :: TheoremDB -> String
> writetheorems [] = "\n"
> writetheorems (x:xs) = x ++ "\n" ++ writetheorems xs

-------------------- user's functions for the db ---------------------------- *2

> addNewTheorem :: String -> Theorem  -> Proof -> IO ()
> addNewTheorem filename theo proof =
>   do filedata <- (readFile filename) `catch` (\_ -> return "")
>      let db = readtheorems filedata
>        in do ok <- check_proof_with_db db theo proof
>              if ok && (db == db) -- to force the complete evaluation of 'db'
>                then do writeFile filename
>                                  (writetheorems
>                                     (db `union` [namefor theo]))
>                        return ()
>                else return ()

> checkProofUsingTheorems :: String -> Theorem -> Proof -> IO ()
> checkProofUsingTheorems filename theo proof =
>   do filedata <- (readFile filename) `catch` (\_ -> return "")
>      check_proof_with_db (readtheorems filedata) theo proof
>      return ()

-------------------------------------------------------------------------------
		     Chapter 3.  Predicate Logic
-------------------------------------------------------------------------------

> forall :: [Int] -> (Int -> Bool) -> Bool
> forall u p = all p u

> exists :: [Int] -> (Int -> Bool) -> Bool
> exists u p = any p u


-------------------------------------------------------------------------------
			Chapter 4.  Set Theory
-------------------------------------------------------------------------------

> type Set a = [a]

> errfun :: Show a => String -> a -> String -> b
> errfun f s msg = error (f ++ ": " ++ show s ++ " is not a " ++ msg)

note that subset does not reject non-sets

> subset :: (Eq a, Show a) => Set a -> Set a -> Bool
> subset set1 set2 
>      = foldr f True set1
>        where 
>        f x sofar = if elem x set2 then sofar else False

> -- note that properSubset does not reject non-sets
> properSubset :: (Eq a, Show a) => Set a -> Set a -> Bool
> properSubset set1 set2
>      = not (setEq set1 set2) /\ (subset set1 set2)

> -- note that setEq does not reject non-sets
> setEq :: (Eq a, Show a) => Set a -> Set a -> Bool
> setEq set1 set2 
>      = (set1 `subset` set2) /\ (set2 `subset` set1)

> normalForm :: (Eq a, Show a) => [a] -> Bool
> normalForm set = length (normalizeSet set) == length set

> normalizeSet :: Eq a => [a] -> Set a
> normalizeSet elts 
>      = foldr f [] elts
>        where
>        f x sofar 
>          = if x `elem` sofar then sofar else x:sofar

> (+++) :: (Eq a, Show a) => Set a -> Set a -> Set a
> (+++) set1 set2 
>      = if not (normalForm set1)
>           then errfun "+++" set1 "set"
>           else if not (normalForm set2)
>                then errfun "+++" set2 "set"
>                else normalizeSet (set1 ++ set2)

> (***) :: (Eq a, Show a) => Set a -> Set a -> Set a
> (***) set1 set2
>      = if not (normalForm set1)
>           then errfun "***" set1 "set"
>           else if not (normalForm set2)
>                then errfun "***" set2 "set"
>                else [x | x <- set1, (x `elem` set2)]

> (~~~) :: (Eq a, Show a) => Set a -> Set a -> Set a
> (~~~) set1 set2 
>      =  if not (normalForm set1)
>            then errfun "~~~" set1 "set"
>            else if not (normalForm set1)
>                 then errfun "~~~" set2 "set"
>                 else [x | x <- set1, not (x `elem` set2)]

> (!!!) :: (Eq a, Show a) => Set a -> Set a -> Set a
> (!!!) u a = if not (normalForm u)
>                then errfun "!!!" u "set"
>                else
>             if not (normalForm a)
>                then errfun "!!!" a "set"
>             else u ~~~ a

> powerset :: (Eq a, Show a) => Set a -> Set (Set a)
> powerset set
>  = if not (normalForm set)
>       then errfun "powerset" set "set"
>    else
>    powersetLoop set
>    where
>    powersetLoop [] = [[]]
>    powersetLoop (e:set)
>      = let setSoFar = powersetLoop set
>        in [e:s | s <- setSoFar] ++ setSoFar

> crossproduct :: (Eq a, Show a, Eq b, Show b) => Set a ->
>                   Set b -> Set (a,b)
> crossproduct set1 set2
>  = if not (normalForm set1)
>       then errfun "crossproduct" set1 "set"
>    else
>    if not (normalForm set2)
>       then errfun "crossproduct" set2 "set"
>    else [(a,b) | a <- set1, b <- set2]


-------------------------------------------------------------------------------
			Chapter 5.  Recursion
-------------------------------------------------------------------------------

> factorial :: Integer -> Integer
> factorial 0 = 1
> factorial n = n * factorial (n-1)

> quicksort :: Ord a => [a] -> [a]
> quicksort [] = []
> quicksort (splitter:xs) =
>   quicksort [y | y <- xs, y<=splitter]
>   ++ [splitter]
>   ++ quicksort [y | y <- xs, y>splitter]

> firsts1, firsts2 :: [(a,b)] -> [a]
> firsts1 [] = []
> firsts1 ((a,b):ps) = a : firsts1 ps

> firsts2 xs = map fst xs

> data Tree a
>   = Tip
>   | Node a (Tree a) (Tree a)
>   deriving Show

> t1, t2 :: Tree Int
> t1 = Node 6 Tip Tip
> t2 = Node 5
>        (Node 3 Tip Tip)
>        (Node 8 (Node 6 Tip Tip) (Node 12 Tip Tip))

> nodeCount :: Tree a -> Int
> nodeCount Tip = 0
> nodeCount (Node x t1 t2) = 1 + nodeCount t1 + nodeCount t2

> reflect :: Tree a -> Tree a
> reflect Tip = Tip
> reflect (Node a t1 t2) = Node a (reflect t2) (reflect t1)

> mapTree :: (a->b) -> Tree a -> Tree b
> mapTree f Tip = Tip
> mapTree f (Node a t1 t2) =
>   Node (f a) (mapTree f t1) (mapTree f t2)

> tree :: Tree (Int,Int)
> tree =
>   Node (5,10)
>     (Node (3,6)  (Node (1,1) Tip Tip)
>                  (Node (4,8) Tip Tip))
>     (Node (7,14) (Node (6,12) Tip Tip)
>                  (Node (8,16) Tip Tip))

> find :: Int -> Tree (Int,a) -> Maybe a
> find n Tip = Nothing
> find n (Node (m,d) t1 t2) =
>   if n==m then Just d
>   else if n<m then find n t1
>               else find n t2


> data Peano = Zero | Succ Peano deriving Show

> one   = Succ Zero
> two   = Succ one
> three = Succ two
> four  = Succ three
> five  = Succ four
> six   = Succ five

> data List a = Empty | Cons a (List a)

> decrement :: Peano -> Peano
> decrement Zero = Zero
> decrement (Succ a) = a

> add :: Peano -> Peano -> Peano
> add Zero     b = b
> add (Succ a) b = Succ (add a b)

> sub :: Peano -> Peano -> Peano
> sub a        Zero     = a
> sub Zero     b        = Zero
> sub (Succ a) (Succ b) = sub a b

> equals :: Peano -> Peano -> Bool
> equals Zero     Zero     = True
> equals Zero     b        = False
> equals a        Zero     = False
> equals (Succ a) (Succ b) = equals a b

> lt :: Peano -> Peano -> Bool
> lt a        Zero     = False
> lt Zero     (Succ b) = True
> lt (Succ a) (Succ b) = lt a b

> f_datarec :: a -> [a]
> f_datarec x = x : f_datarec x

> ones = f_datarec 1

> twos = 2 : twos

> object = let a = 1:b
>              b = 2:c
>              c = [3] ++ a
>          in a

-------------------------------------------------------------------------------
			Chapter 8.  Relations
-------------------------------------------------------------------------------


> type Relation a = Set (a,a)

> type Digraph a = (Set a, Relation a)

> domain :: (Eq a, Show a, Eq b, Show b) => Set (a,b) -> Set a
> domain set
>  = if not (normalForm set)
>       then errfun "domain" set "set"
>    else
>    map fst set

> codomain :: (Eq a, Show a, Eq b, Show b) => Set (a,b) -> Set b
> codomain set
>  = if not (normalForm set)
>       then errfun "codomain" set "set"
>    else
>    map snd set

> isDigraph :: (Eq a, Show a) => Digraph a -> Bool
> isDigraph (set, relation)
>  = normalForm set /\ normalForm relation

> digraphEq :: (Eq a, Show a) => Digraph a -> Digraph a -> Bool
> digraphEq digraph1 digraph2
>      = if not (isDigraph digraph1)
>           then errfun "digraphEq" digraph1 "digraph"
>        else
>        if not (isDigraph digraph2)
>           then errfun "digraphEq" digraph2 "digraph"
>        else
>        let (set1,relation1) = digraph1
>            (set2,relation2) = digraph2
>        in (setEq set1 set2) /\ (setEq relation1 relation2)

> isReflexive :: (Eq a, Show a) => Digraph a -> Bool
> isReflexive digraph
>         = if not (isDigraph digraph)
>              then errfun "isReflexive" digraph "digraph"
>           else
>           let (set, relation) = digraph
>           in and [elem (e,e) relation | e <- set]

> isIrreflexive :: (Eq a, Show a) => Digraph a -> Bool
> isIrreflexive digraph
>         = if not (isDigraph digraph)
>              then errfun "isIrreflexive" digraph "digraph"
>           else
>           let (set, relation) = digraph
>           in [a | (a,b) <- relation, a == b && elem a set] == []

> lessThan_N100 :: Digraph Int
> lessThan_N100 
>  = let set = [1..100]
>    in (set,[(a,b) | a <- set, b <- set, a < b])

> equals_N100 :: Digraph Int
> equals_N100
>  = let set = [1..100]
>    in (set,[(a,b) | a <- set, b <- set, a == b])

> greaterThan_N100 :: Digraph Int
> greaterThan_N100
>  = let set = [1..100]
>    in (set,[(a,b) | a <- set, b <- set, a > b])

> lessThanOrEq_N100 :: Digraph Int
> lessThanOrEq_N100
>  = let set = [1..100]
>    in (set,[(a,b) | a <- set, b <- set, a < b \/ a == b])

> greaterThanOrEq_N100 :: Digraph Int
> greaterThanOrEq_N100
>  = let set = [1..100]
>    in (set,[(a,b) | a <- set, b <- set, a > b \/ a == b])

> notEq_N100 :: Digraph Int
> notEq_N100 
>  = let set = [1..100]
>    in (set,[(a,b) | a <- set, b <- set, not (a == b)])

> isSymmetric ::  (Eq a, Show a) => Digraph a -> Bool
> isSymmetric digraph
>      = if not (isDigraph digraph)
>           then errfun "isSymmetric" digraph "digraph"
>        else
>        let (set, relation) = digraph
>        in
>        and [(elem (a,b) relation) ==> (elem (b,a) relation)         
>             | a <- set, b <- set]

> isAntisymmetric ::  (Eq a, Show a) => Digraph a -> Bool
> isAntisymmetric digraph
>      = if not (isDigraph digraph)
>           then errfun "isAntisymmetric" digraph "digraph"
>        else
>        let (set, relation) = digraph
>        in
>        and [((elem (x,y) relation) /\ (elem (y,x) relation))          
>             ==> (x == y) | x <- set, y <- set]

> isTransitive :: (Eq a, Show a) => Digraph a -> Bool
> isTransitive digraph
>      = if not (isDigraph digraph)
>           then errfun "isTransitive" digraph "digraph"
>        else
>        let (set, relation) = digraph
>        in
>        and [((elem (x,y) relation) /\ (elem (y,z) relation))          
>            ==> (elem (x,z) relation)                
>            | x <- set, y <- set, z <- set]

> relationalComposition :: (Show a, Eq b, Show c, Show b, Eq c, Eq a) => 
>                              Set (a,b) -> Set (b,c) -> Set (a,c)
> relationalComposition set1 set2 
>  = if not (normalForm set1)
>       then errfun "relationalComposition" set1 "relation"
>    else
>    if not (normalForm set2)
>       then errfun "relationalComposition" set2 "relation"
>    else
>    normalizeSet [(a,c) | (a,b) <- set1, (b', c) <- set2, b == b']

> equalityRelation :: (Eq a, Show a) => Set a -> Relation a
> equalityRelation set 
>  = if not (normalForm set)
>       then errfun "equalityRelation" set "set"
>    else [(e,e) | e <- set]

> relationalPower :: (Eq a, Show a) => Digraph a -> Int -> Relation a
> relationalPower digraph power
>  = if not (isDigraph digraph)
>       then errfun "relationalPower" digraph "digraph"
>    else
>    relationalPowerLoop digraph power
>    where
>    relationalPowerLoop (set,relation) 0 
>      = equalityRelation set
>    relationalPowerLoop (set,relation) n 
>      = relationalComposition 
>         (relationalPowerLoop (set,relation) (n-1)) relation

> reflexiveClosure :: (Eq a, Show a) => Digraph a -> Digraph a
> reflexiveClosure digraph
>  = if not (isDigraph digraph)
>       then errfun "reflexiveClosure" digraph "digraph"
>    else
>    let (set, relation) = digraph
>    in
>    (set, relation +++ (equalityRelation set))

> inverse :: Set (a,b) -> Set (b,a)
> inverse set = [(b,a) | (a,b) <- set]

> symmetricClosure :: (Eq a, Show a) => Digraph a -> Digraph a
> symmetricClosure digraph
>  = if not (isDigraph digraph)
>       then errfun "symmetricClosure" digraph "digraph"
>    else
>    let (set, relation) = digraph
>    in (set, relation +++ (inverse relation))

> transitiveClosure :: (Eq a, Show a) => Digraph a -> Digraph a
> transitiveClosure digraph
>  = if not (isDigraph digraph)
>       then errfun "transitiveClosure" digraph "digraph"
>    else
>    let (set, relation) = digraph
>        len = length set   
>        loop n power     
>             = if (n > len) 
>                  then []          
>                  else power +++ (loop (n+1) 
>                                  (relationalComposition power relation))
>    in
>    (set, loop 1 relation)   

> isPartialOrder :: (Eq a, Show a) => Digraph a -> Bool
> isPartialOrder digraph
>      = if not (isDigraph digraph)
>           then errfun "isPartialOrder" digraph "digraph"
>        else
>        isReflexive digraph /\
>        (isAntisymmetric digraph /\
>        isTransitive digraph)

> remTransArcs :: (Eq a, Show a) => Relation a -> Relation a
> remTransArcs relation
>  = relation ~~~ [(x,z) | (x,y) <- relation, (y',z) <- relation, y == y']
> 
> remRelArcs ::  (Eq a, Show a) => Relation a -> Relation a
> remRelArcs relation = relation ~~~ [(x,y) | (x,y) <- relation, x == y]
> 
> remReflexTransArcs :: (Eq a, Show a) => Relation a -> Relation a
> remReflexTransArcs relation
>  = remTransArcs (remRelArcs relation)

> isWeakest :: (Eq a, Show a) => Relation a -> a -> Bool
> isWeakest relation a 
>        = if not (normalForm relation)
>             then errfun "isWeakest" relation "relation"
>          else
>          and [a /= c | (b,c) <- remReflexTransArcs relation]

> isGreatest :: (Eq a, Show a) => Relation a -> a -> Bool
> isGreatest set a 
>        = if not (normalForm set)
>             then errfun "isGreatest" set "relation"
>          else
>          and [a /= b | (b,c) <- remReflexTransArcs set]

> weakestSet :: (Eq a, Show a) => Digraph a -> Set a
> weakestSet digraph
>        = if not (isDigraph digraph)
>             then errfun "weakestSet" digraph "digraph"
>          else
>          let (set, relation) = digraph
>          in
>          filter (isWeakest relation) set

> greatestSet :: (Eq a, Show a) => Digraph a -> Set a
> greatestSet digraph
>        = if not (isDigraph digraph)
>             then errfun "greatestSet" digraph "digraph"
>          else
>          let (set,relation) = digraph
>          in
>          filter (isGreatest relation) set

> isQuasiOrder :: (Eq a, Show a) => Digraph a -> Bool
> isQuasiOrder digraph
>      = if not (isDigraph digraph)
>           then errfun "isQuasiOrder" digraph "digraph"
>        else
>        isTransitive digraph /\
>        isIrreflexive digraph

> isChain :: (Eq a, Show a) => Set (a,a) -> Bool
> isChain rel
>  = let loop [] = True
>        loop ((a,b):ps) 
>          = let new_rel = [pr | pr <- rel, not (pr == (a,b))]
>            in
>            if (elem a (codomain new_rel) || elem b (domain new_rel)) 
>               then loop ps
>               else False
>    in loop rel 

> isLinearOrder :: (Eq a, Show a) => Digraph a -> Bool
> isLinearOrder digraph
>      = if not (isDigraph digraph)
>           then errfun "isLinearOrder" digraph "digraph"
>        else if not (isPartialOrder digraph)
>        then errfun "isLinearOrder" digraph "partial order"
>        else
>        let (set,relation) = digraph
>        in
>        isChain (remReflexTransArcs relation)

> removeFromRelation :: (Eq a, Show a) => a -> Set (a,a) -> Set (a,a)
> removeFromRelation elt relation
>      = loop relation
>        where   loop [] = []   
>                loop ((a,b):relation) = if ((elt == a) || (elt == b))        
>                                           then loop relation
>                                           else (a,b) : loop relation

> removeElt :: (Eq a, Show a) => a -> Digraph a -> Digraph a
> removeElt elt (set, relation) 
>      = (set ~~~ [elt],    
>         removeFromRelation elt relation)

> topsort :: (Eq a, Show a) => Digraph a -> Set a
> topsort digraph
>  = if not (isPartialOrder digraph)
>       then errfun "topsort" digraph "partial order"
>    else
>    let topsortLoop ([], relation) = []
>        topsortLoop (set, []) = []
>        topsortLoop digraph
>         = min_elt : topsortLoop (removeElt min_elt digraph)   
>           where   
>           min_elt = head (weakestSet digraph)
>    in topsortLoop digraph

> isEquivalenceRelation :: (Eq a, Show a) => Digraph a -> Bool
> isEquivalenceRelation digraph
>    = if not (isDigraph digraph)
>         then errfun "isEquivalenceRelation" digraph "digraph"
>      else
>      let (set,relation) = digraph
>      in 
>      (isReflexive digraph /\
>        (isSymmetric digraph /\ isTransitive digraph))


-------------------------------------------------------------------------------
			Chapter 9.  Functions
-------------------------------------------------------------------------------

> isFun :: (Eq a, Eq b, Show a, Show b) => 
>              Set a -> Set b -> Set (a,FunVals b) -> Bool
> isFun f_domain f_codomain fun 
>       = let actual_domain = domain fun
>         in normalForm actual_domain /\
>            setEq actual_domain f_domain

> data FunVals a = Undefined | Value a
>                     deriving (Eq, Show)

> isPartialFunction :: (Eq a, Eq b, Show a, Show b) => Set a -> Set b
>                            -> Set (a,FunVals b) -> Bool
> isPartialFunction f_domain f_codomain fun
>      = isFun f_domain f_codomain fun /\
>           elem Undefined (codomain fun)

> imageValues :: (Eq a, Show a) => Set (FunVals a) -> Set a
> imageValues f_codomain
>      = [v | (Value v) <- f_codomain]

> isSurjective :: (Eq a, Eq b, Show a, Show b) => Set a -> 
>                      Set b -> Set (a,FunVals b) -> Bool
> isSurjective f_domain f_codomain fun
>       = isFun f_domain f_codomain fun /\ 
>         setEq f_codomain (normalizeSet (imageValues (codomain fun)))

> isInjective :: (Eq a, Eq b, Show a, Show b) => Set a -> 
>                   Set b -> Set (a,FunVals b) -> Bool
> isInjective f_domain f_codomain fun 
>       = let fun_image = imageValues (codomain fun)
>         in isFun f_domain f_codomain fun /\
>            normalForm fun_image

> functionalComposition :: (Eq a, Eq b, Eq c, Show a, Show b, Show c) => 
>                           Set (a,FunVals b) -> Set (b,FunVals c) -> 
>                              Set (a,FunVals c)
> functionalComposition f1 f2 
>  = normalizeSet [(a,c) | (a,Value b) <- f1, (b', c) <- f2, b == b']

> isBijective :: (Eq a, Eq b, Show a, Show b) => Set a -> Set b
>                     -> Set (a,FunVals b) -> Bool
> isBijective f_domain f_codomain fun 
>       = isSurjective f_domain f_codomain fun /\ 
>         isInjective f_domain f_codomain fun 

> isPermutation
>   :: (Eq a, Show a) => Set a -> Set a -> Set (a,FunVals a) -> Bool
> isPermutation f_domain f_codomain fun 
>       = isBijective f_domain f_codomain fun /\
>         setEq f_domain f_codomain

> diagonal :: Int -> [(Int,Int)] -> [(Int,Int)]
> diagonal stop rest = let interval = [1 .. stop]
>                          in zip interval (reverse interval) ++ rest

> rationals :: [(Int, Int)]
> rationals = foldr diagonal [] [1..]


-------------------------------------------------------------------------------
	 Chapter 10.  Discrete Mathematics in Circuit Design
-------------------------------------------------------------------------------

> class Signal a where
>   inv :: a -> a
>   and2, or2, xor :: a -> a -> a

> instance Signal Bool where
>   inv False = True
>   inv True = False
>   and2 = (&&)
>   or2 = (||)
>   xor False False = False
>   xor False True  = True
>   xor True  False = True
>   xor True  True  = False


> -- halfAdd :: Signal a => a -> a -> (a,a)
> halfAdd a b = (and2 a b, xor a b)

> fullAdd :: Signal a => (a,a) -> a -> (a,a)
> fullAdd (a,b) c = (or2 w y, z)
>   where (w,x) = halfAdd a b
>         (y,z) = halfAdd x c


halfAdd False False
halfAdd False True
halfAdd True  False
halfAdd True  True

fullAdd (False, False) False
fullAdd (False, False) True
fullAdd (False, True)  False
fullAdd (False, True)  True
fullAdd (True,  False) False
fullAdd (True,  False) True
fullAdd (True,  True)  False
fullAdd (True,  True)  True


> add4 :: Signal a => a -> [(a,a)] -> (a,[a])

> add4 c [(x0,y0),(x1,y1),(x2,y2),(x3,y3)] =
>        (c0, [s0,s1,s2,s3])
>   where (c0,s0) = fullAdd (x0,y0) c1
>         (c1,s1) = fullAdd (x1,y1) c2
>         (c2,s2) = fullAdd (x2,y2) c3
>         (c3,s3) = fullAdd (x3,y3) c


    Example: addition of 3 + 8
       3 + 8
       =   0011   (  2+1 =  3)
         + 1000   (    8 =  8)
       =   1011   (8+2+1 = 11)
    Calculate this by evaluating
       add4 False [(False,True),(False,False),(True,False),(True,False)]
    The expected result is
       (False, [True,False,True,True])

> mscanr :: (b->a->(a,c)) -> a -> [b] -> (a,[c])
> mscanr f a [] = (a,[])
> mscanr f a (x:xs) =
>   let (a',ys) = mscanr f a xs
>       (a'',y) = f x a'
>   in (a'', y:ys)

> rippleAdd :: Signal a => a -> [(a,a)] -> (a, [a])
> rippleAdd c zs = mscanr fullAdd c zs

    Example: addition of 23+11
       23 + 11
       =   010111   (16+4+2+1 = 23)
         + 001011   (   8+2+1 = 11) with carry input = 0
       =   100010   (    32+2 = 34) with carry output = 0
    Calculate with the circuit by evaluating
       rippleAdd False [(False,False),(True,False),(False,True),
                      (True,False),(True,True),(True,True)]
    The expected result is
       (False, [True,False,False,False,True,False])










