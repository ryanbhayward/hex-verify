Ok, I've got it, I think.  

An example for pattern1 is attached.  

Now, to make it readable (or even possible), I had to throw out
all the small patterns (32a, 32b, 2ab, 13).   I only expand a pattern
once, afterwards I just print its number and stop.  


The tricky part was showing the and/or relationship.  Most of the time,
it is an or relationship.  Occasionally there is an and relationship.
This is because the majority of the time a pattern is played with
other small patterns (like 2 or 32).   Also, if a dot node is used
for an OR node, then almost every level needs to be expanded to two levels --
and the tree is almost too large already.

The way I ended up doing it is as follows:

1) by default a node is an or node
2) and nodes are marked with a + sign

I think this is pretty easy to read and understand -- its unfortunate
that it differs slightly from the other trees we have in the paper. 
Grrrr....   
 
Despite this notational confusion, I think the graph does illustrate
how the patterns relate to each.  

Comments?

PS. If you guys think this is ok, this tree will need to be
massaged into something slightly more presentable.  But it's a start,
I think.

On Sat Jan 21, 2006 at 11:22:18PM -0700, Broderick Arneson wrote:
> > Not bad, but it doesn't show any of the AND/OR structure... for instance, 
> > do I "pick pattern 7 or pattern 8 or pattern 9", or is it instead "pick 
> > pattern (7 and 8) or pick pattern 9". This could be done with the AND/OR 
> > nodes as before...
> 
> Whoops, I totaly forgot about that.  I think I can get that info in as
> well. 
> 
> Btw, your idea works ok but we still need to ignore 2ab, 13, etc because
> they are so prevalent at all levels.  It does make a difference
> for a large pattern that is called at least 2 times, however. 
> 
> I have a tree for pattern 1 that we can use, but it doesn't have and/or
> information.  With the extra or nodes it might be too big... but
> maybe it'll work.  We'll see.
> 
> 
> -- 
> Broderick

-- 
Broderick
