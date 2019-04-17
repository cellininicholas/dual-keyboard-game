cat /usr/share/dict/words | egrep '^[qazwsxedcrfvtgb]{3,}$' > LHS.txt
cat /usr/share/dict/words | egrep '^[tgbyhnujmikolp]{3,}$' > RHS.txt
cat /usr/share/dict/words | egrep '^[yhnujmikolp]{3,}$' > RHS_ORIGINAL.txt