> One idea on this: only expand the calls of patterns the first time we see 
> them. For instance, say
> A -> B, C (pattern A calls patterns B and C)
> B -> C, D
> C -> D
> and D -> E, F
> 
> Then we can show the tree as:
> A -> B -> C -> D -> E
>                  -> F
>        -> D (don't expand here)
>   -> C (don't expand here)

Nice idea.  I have a picture of pattern11 that fits nicely on a 
page, but it drops all references to patterns 32a, 32b, 9, 2ab, and 13.
It's attached.

Your idea should result in a similar tree to what I have, but even smaller.
Plus it's really easy to implement. 

I'll give it a go. 

-- 
Broderick
