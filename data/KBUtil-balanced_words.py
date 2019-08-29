greatWords = list()
# Don't include tgb
# ,'t','g','b'
lhsSet = {'q','a','z','w','s','x','e','d','c','r','f','v'}
rhsSet = {'y','h','n','u','j','m','i','k','o','l','p'}

with open("words-8.txt", "r") as f:
    for line in f:
        lhsCharCount = 0
        rhsCharCount = 0
        for character in line:
            if character in lhsSet: lhsCharCount += 1
            elif character in rhsSet: rhsCharCount += 1
        # magnitude = abs(rhsCharCount - lhsCharCount)
        greatWords.append(line.strip() + (" %d" % (rhsCharCount - lhsCharCount)))
        # if difference < 4: greatWords.append(line.strip())
        # if difference < 2: greatWords.append(line.strip() + (" %d" % magnitude))
        
with open('words-8-out.txt', 'w') as outFile:
    for w in greatWords:
        print >> outFile, w
