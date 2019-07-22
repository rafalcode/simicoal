# simicoal

The essence of the coalescent is looking at a current population of living things and determining
their provenance from the previous generation.

The word provenance is somewhat vague on purpose, because the ultimate aim is to find a single common ancestor, yet surely in most cases, an individual has two parents? This is true, but at least for the beginning of the simulation, we unify them into a "parpair" or parent-pair. This is not so realistic, and in fact it's probably more realistic to consider just one the parent pair: i.e. in equine genetics the sireline, or the mareline.

# simitwo

## variables
Given a current population size, we can ask the question, where did each individual come from?
Well, it came from a pair of parents, right?
But ... different parents each time? No.
A pair of parents can be responsible for more than 1 individual, and the pa[] array
is a random realization of how many individuals a certain pair or parents is responsible for.
It doesn't say which individuals, but just how many.

Before that however, the ra[] records which parpair each individual selected. It's randomly generated.

The next concern is building a pai[] array which holds only the reproductively successful
parpairs. i.e. thos parpairs with zero offspring are discarded.

So when we then look at the provenance of the previous generation, we get another set of parpairs
that do not reproduce, so naturally as we continue, we would expect thqat finally, there would only be one left.

simitwo is still a very basic implementation, and i't spretty much just a stochastic process
applied to reproducing "agents".

In more detail, it's a stochastic process that empties out certain positions until there's only one left
with the interest being in the number of iterations it takes for that to happen.
