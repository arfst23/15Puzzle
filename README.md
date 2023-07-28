# 15 Puzzle

The [15 Puzzle](https://en.wikipedia.org/wiki/15_puzzle)
is a sliding puzzle having 15 square tiles numbered 1 to 15 in a
frame that is 4 tiles high and 4 tiles wide, leaving one unoccupied tile
position.

Mis a sliding puzzle having 15 square tiles numbered 1 to 15 in a
frame that is 4 tiles high and 4 tiles wide, leaving one unoccupied tile
position.

## Mathematical Analysis

This table shows the number of permutations by the number of moves
required to solve the puzzle:

| moves | positions |
| 00 |            1 |
| 01 |            2 |
| 02 |            4 |
| 03 |           10 |
| 04 |           24 |
| 05 |           54 |
| 06 |          107 |
| 07 |          212 |
| 08 |          446 |
| 09 |          946 |
| 10 |         1948 |
| 11 |         3938 |
| 12 |         7808 |
| 13 |        15544 |
| 14 |        30821 |
| 15 |        60842 |
| 16 |       119000 |
| 17 |       231844 |
| 18 |       447342 |
| 19 |       859744 |
| 20 |      1637383 |
| 21 |      3098270 |
| 22 |      5802411 |
| 23 |     10783780 |
| 24 |     19826318 |
| 25 |     36142146 |
| 26 |     65135623 |
| 27 |    116238056 |
| 28 |    204900019 |
| 29 |    357071928 |
| 30 |    613926161 |
| 31 |   1042022040 |
| 32 |   1742855397 |
| 33 |   2873077198 |
| 34 |   4660800459 |
| 35 |   7439530828 |
| 36 |  11668443776 |
| 37 |  17976412262 |
| 38 |  27171347953 |
| 39 |  40271406380 |
| 40 |  58469060820 |
| 41 |  83099401368 |
| 42 | 115516106664 |
| 43 | 156935291234 |
| 44 | 208207973510 |
| 45 | 269527755972 |
| 46 | 340163141928 |
| 47 | 418170132006 |
| 48 | 500252508256 |
| 49 | 581813416256 |
| 50 | 657076739307 |
| 51 | 719872287190 |
| 52 | 763865196269 |
| 53 | 784195801886 |
| 54 | 777302007562 |
| 55 | 742946121222 |
| 56 | 683025093505 |
| 57 | 603043436904 |
| 58 | 509897148964 |
| 59 | 412039723036 |
| 60 | 317373604363 |
| 61 | 232306415924 |
| 62 | 161303043901 |
| 63 | 105730020222 |
| 64 |  65450375310 |
| 65 |  37942606582 |
| 66 |  20696691144 |
| 67 |  10460286822 |
| 68 |   4961671731 |
| 69 |   2144789574 |
| 70 |    868923831 |
| 71 |    311901840 |
| 72 |    104859366 |
| 73 |     29592634 |
| 74 |      7766947 |
| 75 |      1508596 |
| 76 |       272198 |
| 77 |        26638 |
| 78 |         3406 |
| 79 |           70 |
| 80 |           17 |

On average 52.59 moves are needed

Here are the 17 permutations that need 80 moves, written row by row:
```
-- 11 09 13 12 15 10 14 03 07 06 02 04 08 05 01
-- 12 09 13 15 08 10 14 11 07 06 02 04 03 05 01
-- 12 09 13 15 11 10 14 03 07 02 05 04 08 06 01
-- 12 09 13 15 11 10 14 03 07 05 06 04 08 02 01
-- 12 09 13 15 11 10 14 03 07 06 02 04 08 05 01
-- 12 09 13 15 11 10 14 07 08 05 06 04 03 02 01
-- 12 09 13 15 11 10 14 07 08 06 02 04 03 05 01
-- 12 09 13 15 11 10 14 08 03 06 02 04 07 05 01
-- 12 09 13 15 11 14 10 03 08 06 02 04 07 05 01
-- 12 10 13 15 11 09 14 07 03 06 02 04 08 05 01
-- 12 10 13 15 11 14 09 03 07 02 05 04 08 06 01
-- 12 10 13 15 11 14 09 03 07 06 02 04 08 05 01
-- 12 10 13 15 11 14 09 07 08 06 02 04 03 05 01
-- 12 11 13 15 14 10 09 03 07 06 02 04 08 05 01
-- 12 14 13 15 11 09 10 03 07 06 02 04 08 05 01
-- 12 14 13 15 11 09 10 08 03 06 02 04 07 05 01
-- 15 09 13 11 12 10 14 03 07 06 02 04 08 05 01
```

## Algorithmic Idea

The code implements the paper /Additive Pattern Database Heuristics/ by
Ariel Felner, Richard E. Korf, and Sarit Hanan from 2004.
The database was improve takin the empty field into consideration.

## Computational Result

The solver can be build via `make`.

On an Intel Core i7-9700K the build (calculating the database) takes 45min.
While the average puzzle is solved in 0.23s, the above 17 permutations
take 15s on average, the 2 worst require 30s to be solved.